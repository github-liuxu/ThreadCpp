//
//  THMainHandler.hpp
//  TestCpp
//
//  Created by 刘东旭 on 2024/4/20.
//

#ifndef THMainHandler_hpp
#define THMainHandler_hpp

#include <stdio.h>
#include "THThread.hpp"
#include "Testop.hpp"

class THMainHandler: public THObject {
public:
    void SetTest(Testop* test);
private:
    void Exec(THEvent *event);
    Testop* test = nullptr;
};

#endif /* THMainHandler_hpp */
