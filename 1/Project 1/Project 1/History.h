//
//  History.h
//  Project 1
//
//  Created by 杨博超 on 16/4/4.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    int m_rows;
    int m_cols;
    int	m_historyGrid[MAXROWS][MAXCOLS];
};
#endif /* History_h */
