//
//  support.cpp
//  Game
//
//  Created by 杨博超 on 16/5/13.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <utility>
#include "support.h"
#include "provided.h"
using namespace std;

// rate the point of the move just been made
int rate(Scaffold s, int N, int color, int Col, int Row, int depth, bool sequence)
{
    int countInRow = 1;
    int point = -10000; // junk number initialized
    
    // check downward
    if (sequence)
    {
        if (s.checkerAt(Col, Row - countInRow) == color)
        {
            while (s.checkerAt(Col, Row - countInRow) == color)
            {
                countInRow++;
                if (countInRow == N)
                {
                    point = (999 - depth); // big number minus depth
                    break;
                }
            }
            if (countInRow != N)
            {
                countInRow = 1;
            }
        }
        
        // check horizontally
        if (point == -10000)
        {
            if (s.checkerAt(Col - countInRow, Row) == color || s.checkerAt(Col + countInRow, Row) == color)
            {
                int left = 0;
                
                while (s.checkerAt(Col - countInRow, Row) == color)
                {
                    countInRow++;
                    if (countInRow == N)
                    {
                        point = (999 - depth);
                        break;
                    }
                }
                if (countInRow != N)
                {
                    left = countInRow;
                    countInRow = 1;
                    
                    while (s.checkerAt(Col + countInRow, Row) == color)
                    {
                        countInRow++;
                        if (left + countInRow - 1 == N)
                        {
                            point = (999 - depth);
                            break;
                        }
                    }
                }
                countInRow = 1;
            }
        }
        
        // check upper left to lower right diagonally, in two parts, and eventually sum up
        if (point == -10000)
        {
            if (s.checkerAt(Col - countInRow, Row + countInRow) == color || s.checkerAt(Col + countInRow, Row - countInRow) == color)
            {
                int leftUp = 0;
                
                while (s.checkerAt(Col - countInRow, Row + countInRow) == color)
                {
                    countInRow++;
                    if (countInRow == N)
                    {
                        point = (999 - depth);
                        break;
                    }
                }
                if (countInRow != N)
                {
                    leftUp = countInRow;
                    countInRow = 1;
                    
                    while (s.checkerAt(Col + countInRow, Row - countInRow) == color)
                    {
                        countInRow++;
                        if (leftUp + countInRow -1 == N)
                        {
                            point = (999 - depth);
                            break;
                        }
                    }
                }
                countInRow = 1;
            }
        }
        
        // check lower left to upper right diagonally, in two parts, and eventually sum up
        if (point == -10000)
        {
            if (s.checkerAt(Col - countInRow, Row - countInRow) == color || s.checkerAt(Col + countInRow, Row + countInRow) == color)
            {
                int leftDown = 0;
                
                while (s.checkerAt(Col - countInRow, Row - countInRow) == color)
                {
                    countInRow++;
                    if (countInRow == N)
                    {
                        point = (999 - depth);
                        break;
                    }
                }
                if (countInRow != N)
                {
                    leftDown = countInRow;
                    countInRow = 1;
                    
                    while (s.checkerAt(Col + countInRow, Row + countInRow) == color)
                    {
                        countInRow++;
                        if (leftDown + countInRow - 1 == N)
                        {
                            point = (999 - depth);
                            break;
                        }
                    }
                }
                countInRow = 1;
            }
        }
        
        // special case
        // not over, but scaffold full
        if(point == -10000 && s.numberEmpty() == 0)
        {
            point = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    else if (!sequence)
    {
        // check downward
        if (s.checkerAt(Col, Row - countInRow) == color)
        {
            while (s.checkerAt(Col, Row - countInRow) == color)
            {
                countInRow++;
                if (countInRow == N)
                {
                    point = depth - 999; // -(999 - depth)
                    break;
                }
            }
            if (countInRow != N)
            {
                countInRow = 1;
            }
        }
        
        // check horizontally
        if (point == -10000)
        {
            if (s.checkerAt(Col - countInRow, Row) == color || s.checkerAt(Col + countInRow, Row) == color)
            {
                int left = 0;
                
                while (s.checkerAt(Col - countInRow, Row) == color)
                {
                    countInRow++;
                    if (countInRow == N)
                    {
                        point = depth - 999;
                        break;
                    }
                }
                if (countInRow != N)
                {
                    left = countInRow;
                    countInRow = 1;
                    
                    while (s.checkerAt(Col + countInRow, Row) == color)
                    {
                        countInRow++;
                        if (left + countInRow - 1 == N)
                        {
                            point = depth - 999;
                            break;
                        }
                    }
                }
                countInRow = 1;
            }
        }
        
        // check upper left to lower right diagonally, in two parts, and eventually sum up
        if (point == -10000)
        {
            if (s.checkerAt(Col - countInRow, Row + countInRow) == color || s.checkerAt(Col + countInRow, Row - countInRow) == color)
            {
                int leftUp = 0;
                
                while (s.checkerAt(Col - countInRow, Row + countInRow) == color)
                {
                    countInRow++;
                    if (countInRow == N)
                    {
                        point = depth - 999;
                        break;
                    }
                }
                if (countInRow != N)
                {
                    leftUp = countInRow;
                    countInRow = 1;
                    
                    while (s.checkerAt(Col + countInRow, Row - countInRow) == color)
                    {
                        countInRow++;
                        if (leftUp + countInRow -1 == N)
                        {
                            point = depth - 999;
                            break;
                        }
                    }
                }
                countInRow = 1;
            }
        }
        
        // check lower left to upper right diagonally, in two parts, and eventually sum up
        if (point == -10000)
        {
            if (s.checkerAt(Col - countInRow, Row - countInRow) == color || s.checkerAt(Col + countInRow, Row + countInRow) == color)
            {
                int leftDown = 0;
                
                while (s.checkerAt(Col - countInRow, Row - countInRow) == color)
                {
                    countInRow++;
                    if (countInRow == N)
                    {
                        point = depth - 999;
                        break;
                    }
                }
                if (countInRow != N)
                {
                    leftDown = countInRow;
                    countInRow = 1;
                    
                    while (s.checkerAt(Col + countInRow, Row + countInRow) == color)
                    {
                        countInRow++;
                        if (leftDown + countInRow - 1 == N)
                        {
                            point = depth - 999;
                            break;
                        }
                    }
                }
                countInRow = 1;
            }
        }
        
        // special case
        // not over because of who wins, but scaffold is full, so
        if (point == -10000 && s.numberEmpty() == 0)
        {
            point = 0;
        }
    }
    
    return point;
}

// check whether the specific col is full
bool validCol(Scaffold s, int col)
{
    for (int k = 1; k < s.levels() + 1; k ++)
    {
        if (s.checkerAt(col, k) == VACANT)
        {
            return true;
        }
    }
    return false;
}

// the recursive function, which returns a pair of two int, the first one is the choosen col, the second is the best score of the move to that col
std::pair<int, int> determineBestMove(Scaffold& s, int N, int color, int& depth, bool sequence)
{
    std::pair<int, int> twoValues; // initialize a pair
    Scaffold testS = s;
    int best = 0;
    int columnChoosen = 0;
    int storage[testS.cols()]; // an array of points, size equals to the number of cols
    
    // the most special case
    // the first move
    // cut the number of cols need to be considered to half
    // to speed up
    if (s.numberEmpty() == s.cols()*s.levels())
    {
        int specialStorage[(s.cols() + 1)/2];
        for (int k = (s.cols() + 1)/2 ; k > 0; k--)
        {
            s.makeMove(k, color);
            depth++;
            color = 1 - color;
            sequence = !sequence;
            specialStorage[k - 1] = determineBestMove(s, N, color, depth, sequence).second;
            s.undoMove();
            color = 1 - color;
            sequence = !sequence;
            depth--;
        }
        
        // decide whether use max or min
        if (sequence)
        {
            best = -5000;
        }
        else if (!sequence)
        {
            best = 5000;
        }
        
        // iterate the storage
        // find the max or min
        // update
        for (int k = (s.cols() + 1)/2 - 1; k >= 0; k--)
        {
            if (sequence)
            {
                if (specialStorage[k] > best)
                {
                    best = specialStorage[k];
                    columnChoosen = k + 1;
                }
            }
            if (!sequence)
            {
                if (specialStorage[k] < best)
                {
                    best = specialStorage[k];
                    columnChoosen = k + 1;
                }
            }
        }
        
        // update the two ints of the pair
        // return them
        twoValues.first = columnChoosen;
        twoValues.second = best;
        return twoValues;
    }
    
    for (int i = 1; i < testS.cols() + 1; i ++)
    {
        // check every col
        //if valid
        if (validCol(s, i))
        {
            s.makeMove(i, color); // make move
            depth++;
            int row = 0;
            // locate the move exactly
            for (int k = 1; k < s.levels() + 1; k++)
            {
                if (s.checkerAt(i, k) != VACANT && s.checkerAt(i, k + 1) == VACANT)
                {
                    row = k;
                    break;
                }
            }
            
//            cerr << "(" << i << "," << row << ")" << endl;
//            cerr << rate(s, N, color, i, row, depth, sequence) << endl;
//            s.display();
            
            if (rate(s, N, color, i, row, depth, sequence) != -10000) // means over
            {
                //storage[i - 1] = rate(s, N, color, i, row, depth, sequence);
                twoValues.first = i;
                twoValues.second = rate(s, N, color, i, row, depth, sequence); // update the pair
                s.undoMove();
                depth--;
                return twoValues; // return them
            }
            else
            {
                // restrict the searching depth to accelerate
                if (s.cols() > 8) // for huge problem, restrict again
                {
                    if (depth <= 5)
                    {
                        color = 1 - color; // change the color
                        sequence = !sequence; // change max or min choice
                        storage[i - 1] = determineBestMove(s, N, color, depth, sequence).second; // store the point returned
                    }
                }
                else
                {
                    if (depth <= 8)
                    {
                        color = 1 - color;
                        sequence = !sequence;
                        storage[i - 1] = determineBestMove(s, N, color, depth, sequence).second;
                    }
                }
            }
            
            s.undoMove();
            color = 1 - color;
            sequence = !sequence;
            depth--;
        }
        if (!validCol(s, i)) // invalid col, store a junk number
        {
            if (sequence)
            {
                storage[i - 1] = -99999;
            }
            
            if (!sequence)
            {
                storage[i - 1] = 99999;
            }
        }
    }
    
    // decide whether use max or min
    if (sequence)
    {
        best = -5000;
    }
    else if (!sequence)
    {
        best = 5000;
    }
    
    // iterate the storage
    // find the max or min
    // update
    for (int k = 0; k < testS.cols(); k++)
    {
        if (sequence)
        {
            if (storage[k] > best)
            {
                best = storage[k];
                columnChoosen = k + 1;
            }
        }
        if (!sequence)
        {
            if (storage[k] < best)
            {
                best = storage[k];
                columnChoosen = k + 1;
            }
        }
    }
    
    // update the two ints of the pair
    // return them
    twoValues.first = columnChoosen;
    twoValues.second = best;
    return twoValues;
}
