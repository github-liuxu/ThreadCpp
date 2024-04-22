//
//  THMainHandler.cpp
//  TestCpp
//
//  Created by 刘东旭 on 2024/4/20.
//

#include "THMainHandler.hpp"

void THMainHandler::SetTest(Testop* test) {
    this->test = test;
}

void THMainHandler::Exec(THEvent *event) {
    printf("Main Thread!");
    THObject::PostEvent(this->test, new THEvent(1000));
}
