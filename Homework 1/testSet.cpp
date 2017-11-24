//
//  testSet.cpp
//  Homework 1
//
//  Created by 杨博超 on 16/4/11.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    Set s;
    assert(s.empty());
    ItemType x = 12345;
    assert( !s.get(42, x)  &&  x == 12345); // x unchanged by get failure
    s.insert(123456);
    assert(s.size() == 1);
    assert(s.get(0, x)  &&  x == 123456);
    cout << "Passed all tests" << endl;
}