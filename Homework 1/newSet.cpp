//
//  newSet.cpp
//  Homework 1
//
//  Created by 杨博超 on 16/4/11.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#include "newSet.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Set::Set()
{
    lastindex=-1;
    m_max=DEFAULT_MAX_ITEMS;
    m_a=new ItemType[DEFAULT_MAX_ITEMS];
}
Set::Set(int max)
{
    if(max<0){
        cout<<"The size shouldn't be negative"<<endl;
        exit(1);
    }else{
        
        lastindex=-1;
        m_max=max;
        m_a=new ItemType[max];
    }
}
Set::~Set(){
    
    delete [] m_a;
    
}
Set& Set::operator=(const Set&k){
    if(&k==this){
        
        return (*this);
    }
    delete [] m_a;
    m_max=k.m_max;
    m_a=new ItemType[m_max];
    lastindex = k.lastindex;
    for(int i=0;i<m_max;i++){
        m_a[i]=k.m_a[i];
    }
    return (*this);
    
}

Set::Set(const Set&k)
{
    m_max=k.m_max;
    m_a=new ItemType[m_max];
    lastindex = k.lastindex;
    for(int i=0;i<m_max;i++){
        m_a[i]=k.m_a[i];
    }
}

bool Set::empty() const{
    
    if(size()==0){
        return true;
    }else{
        return false;
    }
    
}
int Set::size() const{
    
    return (lastindex+1);
    
}
bool Set::insert(const ItemType& value){
    
    if(size()>=m_max){
        return false;
    }else{
        
        for(int i=0;i<m_max;i++){
            if(m_a[i]==value){
                return false;
            }
        }
        m_a[lastindex+1]=value;
        lastindex=lastindex+1;
    }
    return true;
    
    
    
}
bool Set::erase(const ItemType& value){
    
    if(size()<=1){
        if(m_a[0]==value&&!empty()){
            lastindex--;
            return true;
        }
    }
    
    for(int i=0;i<size();i++){
        if(m_a[i]==value){
            m_a[i]=m_a[size()-1];
            lastindex--;
            return true;
            
        }
        
    }
    return false;
}


bool Set::contains(const ItemType& value) const{
    
    if(empty())
        return false;
    
    for(int i=0;i<=lastindex;i++){
        
        if(m_a[i]==value){
            
            return true;
        }
        
    }
    
    return false;
    
    
}

bool Set::get(int i, ItemType& value) const{
    
    if(i>=0&&i<size()){
        
        value=m_a[i];
        return true;
    }
    
    return false;
    
    
}

void Set::swap(Set& other)
{
    Set temp = other;
    other = *this;
    *this = temp;
    
}
