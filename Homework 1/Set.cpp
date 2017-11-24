//
//  Set.cpp
//  Homework 1
//
//  Created by 杨博超 on 16/4/11.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#include "Set.h"

Set::Set()
{
    lastIndex = -1;
}

bool Set::empty() const
{
    return size() == 0;
}

int Set::size() const{
    
    return lastIndex+1;
}

bool Set::insert(const ItemType& value)
{
    if(size() >= DEFAULT_MAX_ITEMS)
    {
        return false;
    }
    
 
        
    for(int i = 0;i <= lastIndex;i++)
    {
        if(m_a[i] == value)
        {
            return false;
        }
    }
    
    m_a[lastIndex+1]=value;
    lastIndex=lastIndex+1;
    return true;
}

bool Set::erase(const ItemType& value)
{
    if(size() <= 1)
    {
        if(m_a[0] == value && !empty())
        {
            lastIndex--;
            return true;
        }
        return false;
    }
        
    for(int i = 0;i < size();i++)
    {
        if(m_a[i] == value)
        {
            m_a[i]=m_a[size()-1];
            lastIndex--;
            return true;
        }
    }
    return false;
}


bool Set::contains(const ItemType& value) const
{
    if(empty())
        return false;
    for(int i = 0;i <= lastIndex;i++)
    {
        if(m_a[i] == value)
        {
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    if(i >= 0 && i < size())
    {
        value = m_a[i];
        return true;
    }
    return false;
}

void Set::swap(Set& other){
    
    ItemType temp[DEFAULT_MAX_ITEMS];
    int osize = other.size();
    int msize = size();
    
    for(int i = 0;i < osize;i++)
    {
        temp[i] = other.m_a[i];
    }
    
    while(!other.empty())
    {
        int i = 0;
        ItemType v;
        other.get(i, v);
        other.erase(v);
    }
    
    for(int i = 0;i < msize;i++)
    {
        other.insert(m_a[i]);
    }
    
    while(!empty())
    {
        int i = 0;
        ItemType v;
        get(i, v);
        erase(v);
    }
    
    for(int i = 0;i < osize; i++)
    {
        insert(temp[i]);
    }
}



