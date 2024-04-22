//
//  THThread.hpp
//  TestCpp
//
//  Created by 刘东旭 on 2024/4/18.
//

#ifndef THThread_hpp
#define THThread_hpp

#include <stdio.h>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>

class THEvent;
class THObject;
class THPostEvent {
    
public:
    THPostEvent(THObject *receiver, THEvent *event) {
        this->receiver = receiver;
        this->event = event;
    }
public:
    THEvent *event;
    THObject *receiver;
};
class THThread {
public:
    THThread();
    THThread(std::string name);
    ~THThread();
    void Start();
    void PostEvent(THObject *receiver, THEvent *event);
    void Run();
    void Exit();
private:
    std::deque<THPostEvent *> postEventList;
    std::thread *currentThread;
    std::mutex mutex;
    std::condition_variable condition;
    std::unique_lock<std::mutex> lock;
    bool isExit = false;
    std::thread::id thread_id;
};


class THEvent {
public:
    THEvent(int type) {
        this->type = type;
    }
    int type = 0;
};

class THObject {
public:
    void BindThread(THThread* thread) {
        m_thread = thread;
    }
    
    void static PostEvent(THObject *receiver, THEvent *event) {
        receiver->m_thread->PostEvent(receiver, event);
    }
    
    virtual void Exec(THEvent *event) = 0;
protected:
    THThread* m_thread;
};


#endif /* THThread_hpp */
