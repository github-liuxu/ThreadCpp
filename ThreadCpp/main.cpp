//
//  main.cpp
//  TestCpp
//
//  Created by 刘东旭 on 2024/4/13.
//

#include <iostream>
#include "THThread.hpp"
#include "Testop.hpp"
#include "THMainHandler.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Testop *test1 = new Testop();
    THThread *thread1 = new THThread();
    test1->BindThread(thread1);
    thread1->Start();
    THObject::PostEvent(test1, new THEvent(100));
    
    THThread *t = new THThread("__main__");
    THMainHandler *mainHandler = new THMainHandler();
    mainHandler->BindThread(t);
    test1->mainHandler = mainHandler;
    mainHandler->SetTest(test1);
    t->Run();
    
    return 0;
}
