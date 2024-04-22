//
//  Testop.cpp
//  TestCpp
//
//  Created by 刘东旭 on 2024/4/20.
//

#include "Testop.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include "THThread.hpp"
#include "THMainHandler.hpp"

void Testop::Exec(THEvent *event) {
    switch (event->type) {
        case 100:
        {
            std::cout << event->type << std::endl;
            std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));
            THObject::PostEvent(mainHandler, new THEvent(111));
        }
            break;
        case 1000:
        {
            this->m_thread->Exit();
        }
            break;
        default:
            break;
    }
    
}
