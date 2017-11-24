//
//  testSSNSet.cpp
//  Homework 1
//
//  Created by 杨博超 on 16/4/11.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#include "SSNSet.h"
#include <iostream>
#include <cassert>
int main(int argc, const char * argv[]) {
    SSNSet ssnset1;
    assert(ssnset1.size()==0);
    assert(ssnset1.add(880322));
    assert(ssnset1.add(880323));
    assert(!ssnset1.add(880322));
    assert(ssnset1.size()==2);
    ssnset1.print();
    
    return 0;
}
