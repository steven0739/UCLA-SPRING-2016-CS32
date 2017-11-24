//
//  History.cpp
//  Project 1
//
//  Created by 杨博超 on 16/4/4.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#include "globals.h"
#include "History.h"
#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  History implementations
///////////////////////////////////////////////////////////////////////////

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    int r, c;
    for (r = 1; r <= m_rows; r++)
        for (c = 1; c <= m_cols; c++)
            m_historyGrid[r-1][c-1] = 0;
}

bool History::record(int r, int c)
{
    if(r>m_rows || c>m_cols) //if out of bounds, return false
        return false;
    
    m_historyGrid[r-1][c-1]++; //otherwise, increment the number of times player has been at that spot
    
    return true;
}

void History::display() const
{
    char displayHistory[MAXROWS][MAXCOLS];
    int r, c;
    
    for (r = 1; r <= m_rows; r++)
        for (c = 1; c <= m_cols; c++)
        {
            int numTimes = m_historyGrid[r-1][c-1];
            
            if(numTimes==0)
                displayHistory[r-1][c-1]='.';
            else if(numTimes>26)
                displayHistory[r-1][c-1]='Z';
            else
                displayHistory[r-1][c-1]=numTimes+64;
        }
    
    // Draw the grid
    clearScreen();
    
    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
            cout << displayHistory[r-1][c-1];
        cout << endl;
    }
    cout << endl;
}
