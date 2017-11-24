//
//  tree.cpp
//  4
//
//  Created by 杨博超 on 16/5/2.
//  Copyright © 2016年 杨博超. All rights reserved.
//

/*
#include <iostream>
#include <string>
using namespace std;
*/

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then for this value of a2            the function must return
//    "stan" "kenny" "cartman"                      1
//    "stan" "cartman" "butters"                    2
//    "kenny" "stan" "cartman"                      0
//    "kyle" "cartman" "butters"                    3
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 == 0)
    {
        return 1;
    }
    if (n1 < n2)
    {
        return 0;
    }
    int result = 0;
    if (a1[0] == a2[0])
    {
        result += countIncludes(a1+1,n1-1,a2+1,n2-1);
    }
    
    result += countIncludes(a1+1,n1-1,a2,n2);
    return result;
}

void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

void divide(string a[], int n, string divider, int& firstNotLess, int& firstGreater)
{
    if (n < 0)
    {
        n = 0;
    }
    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > divider)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < divider)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}

void order(string a[], int n)
{
    if (n <= 1)
    {
        return;
    }
    int firstNotLess;
    int firstGreater;
    divide(a, n, a[n/2], firstNotLess, firstGreater);
    order(a, firstNotLess);
    order(a+firstGreater, n-firstGreater);
}

/*
int main()
{
    int a[11] = {0, 100, 10, 0, 15, -5, 7, 78, 8, 7, 0};
    order(a, 11);
    cout << a[0] << endl;
    cout << a[1] << endl;
    cout << a[2] << endl;
    cout << a[3] << endl;
    cout << a[4] << endl;
    cout << a[5] << endl;
    cout << a[6] << endl;
    cout << a[7] << endl;
    cout << a[8] << endl;
    cout << a[9] << endl;
    cout << a[10] << endl;
}

int main()
{
    string a[8] = {"steven", "tony", "stepenie", "tom", "blake", "black", "shawn", "shadow"};
    order(a,8);
    cout << a[0] << endl;
    cout << a[1] << endl;
    cout << a[2] << endl;
    cout << a[3] << endl;
    cout << a[4] << endl;
    cout << a[5] << endl;
    cout << a[6] << endl;
    cout << a[7] << endl;
}

int main()
{
    const string a1[7] = { "steven", "steven", "tony", "shawn", "blake", "tony", "vivian"};
    const string a2[3] = { "steven", "shawn", "vivian"};
    const string a3[3] = { "steven", "tony", "vivian"};
    cout << countIncludes(a1, 7, a2, 3) << endl;
    cout << countIncludes(a1, 7, a3, 3) << endl;
}
*/