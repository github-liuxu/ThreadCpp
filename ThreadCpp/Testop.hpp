//
//  Testop.hpp
//  TestCpp
//
//  Created by 刘东旭 on 2024/4/20.
//

#ifndef TestThread_hpp
#define TestThread_hpp

#include <stdio.h>
#include "THThread.hpp"

class THMainHandler;
class Testop: public THObject {
public:
    THMainHandler *mainHandler;
private:
    void Exec(THEvent *event);
};

#endif /* TestThread_hpp */
