//
//  SSNSet.cpp
//  Homework 1
//
//  Created by 杨博超 on 16/4/11.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet()
{
    Set m_a;
}

bool SSNSet::add(unsigned long ssn)
{
    if(m_a.contains(ssn)|| size() >= DEFAULT_MAX_ITEMS)
    {
        return false;
    }
            
    m_a.insert(ssn);
    return true;
}

int SSNSet::size() const
{
    return m_a.size();
}

void SSNSet::print() const
{
    ItemType v;
    for (int i = 0; i <size(); i++)
    {
        m_a.get(i, v);
        cout << v << endl;
    }
}