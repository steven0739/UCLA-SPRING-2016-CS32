//
//  support.h
//  Game
//
//  Created by 杨博超 on 16/5/13.
//  Copyright © 2016年 杨博超. All rights reserved.
//
#include "provided.h"
#ifndef support_h
#define support_h

// rate the point of the move just been made
int rate(Scaffold s, int N, int color, int Col, int Row, int depth, bool sequence);
// check whether the specific col is full
bool validCol(Scaffold s, int col);
// the recursive function, which returns a pair of two int, the first one is the choosen col, the second is the best score of the move to that col
std::pair<int, int> determineBestMove(Scaffold& s, int N, int color, int& depth, bool sequence);

#endif /* support_h */
