//
//  Set.h
//  project 2
//
//  Created by 杨博超 on 16/4/17.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#ifndef Set_h
#define Set_h
#include <iostream>
using namespace std;

typedef std::string ItemType;

class Set
{
public:
    Set();
    ~Set();
    Set(const Set& other);
    Set& operator=(const Set& rhs);
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int position, ItemType& value) const;
    void swap(Set& other);
    
private:
    struct Node
    {
        ItemType m_data;
        Node* m_next;
        Node* m_prev;
    };
    
    int m_size;
    Node* head;
    Node* tail;
};

void unite(const Set& s1, const Set& s2, Set& result);

void subtract(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */
