//
//  main.cpp
//  project 2
//
//  Created by 杨博超 on 16/4/17.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#include "Set.h"
#include <cassert>
#include <iostream>
int main()
{
    Set a;
    assert(a.empty()); //test empty
    assert(a.insert("a")); //test insert
    assert(!a.empty()); //test empty
    assert(!a.insert("a"));
    assert(a.insert("b"));
    assert(!a.insert("b"));
    assert(a.contains("b"));
    
    
    
    assert(a.erase("b"));
    assert(!a.contains("b"));
    assert(!a.erase("b"));
    
    //test get
    a.insert("b");
    a.insert("c");
    ItemType value;
    assert(a.get(-1, value) == false); //the number is negative
    assert(a.get(9999999, value) == false); //the number is bigger than size
    assert(a.get(0, value) == true);
    assert(value == "a");
    
    //test swap
    //both are not empty
    Set a1;
    Set a2;
    assert(a1.insert("abc"));
    assert(a1.insert("bcd"));
    assert(a1.insert("cde"));
    assert(a2.insert("def"));
    assert(a2.insert("efg"));
    
    a1.swap(a2);
    assert(a1.contains("def"));
    assert(a1.contains("efg"));
    assert(!a1.contains("abc"));
    assert(!a1.contains("bcd"));
    assert(!a1.contains("cde"));
    assert(a2.contains("abc"));
    assert(a2.contains("bcd"));
    assert(a2.contains("cde"));
    assert(a1.size() == 2);
    assert(a2.size() == 3);
    
    //ff one of is empty
    Set a3;
    a1.swap(a3);
    assert(a1.empty());
    assert(!a3.empty());
    assert(a3.contains("def"));
    assert(a3.contains("efg"));
    assert(a1.size() == 0);
    assert(a3.size() == 2);
    
    //test copy constructor
    Set a4;
    a4.insert("ace");
    a4.insert("bdf");
    a4.insert("cfg");
    Set a5 = a4;
    assert(a5.contains("ace"));
    assert(a5.contains("bdf"));
    assert(a5.contains("cfg"));
    assert(a5.size() == 3);
    
    //test assignment operator
    Set a6;
    a6.insert("steven");
    a6.insert("tony");
    a5 = a6;
    assert(a5.contains("steven"));
    assert(a5.contains("tony"));
    assert(!a5.contains("ace"));
    assert(!a5.contains("bdf"));
    assert(!a5.contains("cfg"));
    assert(a5.size() == 2);
    
    
    
    //test unite
    Set b1, b2, b3;
    
    b1.insert("steven");
    b1.insert("tony");
    b2.insert("blake");
    b2.insert("steven");
    
    unite(b1, b2, b3);
    assert(b3.contains("steven"));
    assert(b3.contains("tony"));
    assert(b3.contains("blake"));
    assert(!b3.empty());
    assert(b3.size() == 3);
    
    b3.insert("shawn");      //object set isn't empty
    unite(b1, b2, b3);
    assert(b3.contains("steven"));
    assert(b3.contains("tony"));
    assert(b3.contains("blake"));
    assert(!b3.empty());
    assert(b3.size() != 4);
    assert(!b3.contains("shawn"));
    
    //test subtract
    Set b4;
    subtract(b1, b2, b4);
    assert(!b4.contains("steven")); //should not contain the duplicate one
    assert(b4.contains("tony"));
    assert(!b4.contains("blake")); //should not contain strings in b2
    
    cout << "passed" << endl;
    
}