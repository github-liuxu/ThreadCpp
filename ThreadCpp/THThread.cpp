//
//  THThread.cpp
//  TestCpp
//
//  Created by 刘东旭 on 2024/4/18.
//

#include "THThread.hpp"
#include <unistd.h>
#include <pthread.h>
#include "THMainHandler.hpp"

THThread::THThread() {
    this->currentThread = new std::thread([this]{
        this->thread_id = std::this_thread::get_id();
        this->Run();
    });
}

THThread::THThread(std::string name) {
    if (name.compare("__main__") != 0) {
        this->currentThread = new std::thread([this, name]{
            this->thread_id = std::this_thread::get_id();
            pthread_setname_np(name.c_str());
            this->Run();
        });
    }
}

THThread::~THThread() {
    std::unique_lock<std::mutex>lk(mutex);
    if (!postEventList.empty()) {
        size_t size = postEventList.size();
        for (int i = 0; i < size; i++) {
            THPostEvent *e = postEventList[i];
            delete e->event;
            delete e;
        }
        postEventList.clear();
    }
}

void THThread::Exit() {
    if (std::this_thread::get_id() == this->thread_id) {
        std::thread postThread([&]{
            {
                std::unique_lock<std::mutex>lk(mutex);
                isExit = true;
                postEventList.push_back(new THPostEvent(nullptr, new THEvent(0)));
                condition.notify_one();
            }
            delete this->currentThread;
            this->currentThread = nullptr;
        });
        postThread.detach();
    } else {
        {
            std::unique_lock<std::mutex>lk(mutex);
            isExit = true;
            postEventList.push_back(new THPostEvent(nullptr, new THEvent(0)));
            condition.notify_one();
        }
        delete this->currentThread;
        this->currentThread = nullptr;
    }
}

void THThread::Start() {
    this->currentThread->detach();
}

void THThread::PostEvent(THObject *receiver, THEvent *event) {
    if (std::this_thread::get_id() == this->thread_id) {
        std::thread postThread([&]{
            std::unique_lock<std::mutex>lk(mutex);
            postEventList.push_back(new THPostEvent(receiver, event));
            condition.notify_one();
        });
        postThread.detach();
    } else {
        std::unique_lock<std::mutex>lk(mutex);
        postEventList.push_back(new THPostEvent(receiver, event));
        condition.notify_one();
    }
}

void THThread::Run() {
    while (true) {
        std::unique_lock<std::mutex>lk(mutex);
        if (postEventList.empty()) {
            condition.wait(lk);
        } else {
            if (isExit) {
                break;
            }
            THPostEvent *e = postEventList.front();
            postEventList.pop_front();
            lk.unlock();
            if (e->receiver && e->event) {
                e->receiver->Exec(e->event);
                delete e->event;
            }
            delete e;
        }
    }
    std::unique_lock<std::mutex>lk(mutex);
    size_t size = postEventList.size();
    for (int i = 0; i < size; i++) {
        THPostEvent *e = postEventList[i];
        delete e->event;
        delete e;
    }
    postEventList.clear();
    condition.notify_one();
}
