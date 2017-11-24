//
//  Set.h
//  Homework 1
//
//  Created by 杨博超 on 16/4/11.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#ifndef Set_h
#define Set_h

#include <string>
using namespace std;

typedef unsigned long ItemType;

const int DEFAULT_MAX_ITEMS = 100;

class Set
{
public:
    Set();
    // Create an empty set.
    
    bool empty() const;
    // Return true if the set is empty, otherwise false.
    
    int size() const;
    // Return the number of items in the set.
    
    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // is already in the set or because the set has a fixed capacity and
    // is full).
    
    bool erase(const ItemType& value);
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the set, otherwise false.
    
    bool get(int i, ItemType& value) const;
    // If 0 <= i < size(), copy into value an item in the set and
    // return true.  Otherwise, leave value unchanged and return false.
    // (See below for details about this function.)
    
    void swap(Set& other);
    // Exchange the contents of this set with the other one.
    
private:
    ItemType m_a[DEFAULT_MAX_ITEMS];
    int lastIndex;
    int m_value;
};

#endif /* Set_h */
