//
//  Set.cpp
//  project 2
//
//  Created by 杨博超 on 16/4/17.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#include "Set.h"
#include <string>
using namespace std;

Set::Set() //Create an empty set.
{
    m_size = 0;
    head = nullptr; //Set head and tail point to nullptr
    tail = nullptr;
}

Set::~Set() //Destructor
{
    if (!empty()) //Check empty
    {
        if (head == tail) //Only one node
        {
            delete head;
        }
        else //Multiple nodes
        {
            Node* p; //Create a temp node
            p = head;
            while (p->m_next != nullptr) //Delete one by one
            {
                p = p->m_next;
                delete p->m_prev;
            }
            delete tail;
        }
    }
}

Set::Set(const Set& other) //Copy constructor
{
    m_size = 0;
    head = nullptr;
    tail = nullptr;
    
    for (int i = 0; i != other.size(); i++)
    {
        ItemType k;
        other.get(i, k);
        insert(k);
    }
}

Set& Set::operator=(const Set& rhs) //Assignment constructor
{
    if(this != &rhs) //Check if this is already equals to rhs
    {
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}

bool Set::empty() const //Return true if the set is empty, otherwise false

{
    return head == nullptr;
}

int Set::size() const //Return the number of items in the set
{
    return m_size;
}

bool Set::insert(const ItemType& value)
//Insert value into the set if it is not already present.  Return
// true if the value was actually inserted.  Leave the set unchanged
// and return false if the value was not inserted (perhaps because it
// is already in the set or because the set has a fixed capacity and
// is full)

{
    if (contains(value)) //Return false if the value is in
    {
        return false;
    }

    Node* _new = new Node; //Dynamically allocate a new node
    _new->m_data = value; //Initialize the new node
    _new->m_next = nullptr;
    _new->m_prev = nullptr;
    if (empty()) //If is an empty set
    {
        head = tail = _new;
    }
    else //Insert after the last node
    {
        _new->m_prev = tail;
        tail->m_next = _new;
        tail = _new;
    }
    m_size++;
    return true;
}

bool Set::erase(const ItemType& value)
// Remove the value from the set if present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false
{
    if (!contains(value)) //Already there, return false
    {
        return false;
    }
    
    if(m_size == 1) //Only one node
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        m_size--;
        return true;
    }

    Node* temp = head;
    
    while(temp->m_data != value) //Get to the specific node
    {
        temp = temp->m_next;
    }
    
    if(temp == head) //If it is the first node in the set
    {
        head = temp->m_next;
        delete temp;
        head->m_prev = nullptr;
    }
    
    else if(temp == tail) // If it is the last node in the set
    {
        tail = tail->m_prev;
        delete temp;
        tail->m_next = nullptr;
    }
    
    else //If it is inserted in the middle
    {
        Node* tempPrev = temp->m_prev;
        Node* tempNext = temp->m_next;
        delete temp;
        tempPrev->m_next = tempNext;
        tempNext->m_prev = tempPrev;
    }
    m_size--; //Size decreases by one
    return true;
}
        
bool Set::contains(const ItemType& value) const
// Return true if the value is in the set, otherwise false
{
    Node* temp = head;
    if(head == nullptr) //Empty list
    {
        return false;
    }
    while(temp != nullptr) //Try to find it
    {
        if(temp->m_data == value)
        {
            return true;
        }
        temp = temp->m_next;
    }
    return false;
}
        
bool Set::get(int position, ItemType& value) const
// If 0 <= i < size(), copy into value an item in the set and
// return true.  Otherwise, leave value unchanged and return false

{
    if(position < 0 || position >= size()) //Wrong initial situation
    {
        return false;
    }
    
    if (position == 0) //Value equals to the first node when the set is empty before
    {
        value = head->m_data;
        return true;
    }
    
    Node* temp = head;
    
    for(int i = 0; i < position; i++) //Get each node one time
    {
        temp = temp->m_next;
    }
    value = temp->m_data;
    
    return true;
}
        
void Set::swap(Set& other)
// Exchange the contents of this set with the other one
{
    Node* tempHead = head; //Prevent aliasing
    Node* tempTail = tail;
    
    head = other.head;
    tail = other.tail;
    
    other.head = tempHead; //set the other head and tail pointers to those originally of this set
    other.tail = tempTail;
    
    int thisSize = size();
    m_size = other.size();
    other.m_size = thisSize;
}
        
void unite(const Set& s1, const Set& s2, Set& result)
//When this function returns, result must contain a copy of all the values that appear in s1 or s2 or both, and must not contain any other values. (You must not assume result is empty when it is passed in to this function; it might not be.) Since result is a Set, it must, of course, not have any duplicates
{
    Set s1Temp = s1;
    Set s2Temp = s2;
    
    while(!result.empty()) //Make result set empty first
    {
        ItemType k;
        
        result.get(0, k);
        result.erase(k);
    }
    
    for(int i = 0; i < s1Temp.size(); i++) //Get every value in s1
    {
        ItemType k;
        s1Temp.get(i,k);
        result.insert(k);
    }
    
    for(int i = 0; i < s2Temp.size(); i++) //Get every value in s2 except that has already shown in s1
    {
        ItemType k;
        s2Temp.get(i, k);
        if(!s1Temp.contains(k))
        {
            result.insert(k);
        }
    }
}
        
void subtract(const Set& s1, const Set& s2, Set& result)
//When this function returns, result must contain a copy of all the elements that appear in s1 but not s2, and must not contain any other values. (You must not assume result is empty when it is passed in to this function; it might not be.)
{
    Set s1Temp = s1;
    Set s2Temp = s2;
    
    while(!result.empty()) //Make result set empty first
    {
        ItemType k;
        
        result.get(0, k);
        result.erase(k);
    }
    
    for(int i = 0; i < s1Temp.size(); i++) //Get every value which appears in s1, but not in s2
    {
        ItemType k;
        s1Temp.get(i,k);
        if(!s2Temp.contains(k))
        {
            result.insert(k);
        }
    }
}
        

    




















