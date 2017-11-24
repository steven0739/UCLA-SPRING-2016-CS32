//
//  maze.cpp
//  3
//
//  Created by 杨博超 on 16/5/2.
//  Copyright © 2016年 杨博超. All rights reserved.
//

/*
#include <iostream>
#include <string>
using namespace std;
*/

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    int row = sr;
    int col = sc;
    
    maze[sr][sc] = '*';

    if (row == er && col == ec)
    {
        return true;
    }
    
    if (maze[row - 1][col] == '.')
    {
        if (pathExists(maze, row-1, col, er, ec))
        {
            return true;
        }
    }
    if (maze[row][col + 1] ==  '.')
    {
        if (pathExists(maze, row, col+1, er, ec))
        {
            return true;
        }
    }
    if (maze[row + 1][col] ==  '.')
    {
        if (pathExists(maze, row+1, col, er, ec))
        {
            return true;
        }
    }
    if (maze[row][col - 1] ==  '.')
    {
        if (pathExists(maze, row, col-1, er, ec))
        {
            return true;
        }
    }
    return false;
}

/*
 int main()
 {
	char maze[10][10] = {
 { 'X','X','X','X','X','X','X','X','X','X'},
 { 'X','.','.','.','.','X','.','.','.','X'},
 { 'X','.','X','X','.','X','X','.','.','X'},
 { 'X','.','X','.','.','.','X','.','.','X'},
 { 'X','X','X','X','X','.','X','.','.','X'},
 { 'X','.','X','.','.','.','X','.','.','X'},
 { 'X','.','.','.','X','.','X','.','.','X'},
 { 'X','X','X','X','X','.','X','X','X','X'},
 { 'X','.','.','.','.','.','.','.','.','X'},
 { 'X','X','X','X','X','X','X','X','X','X'}
	};
	
	if (pathExists(maze,1,1,8,8))
 cout << "Solvable!" << endl;
	else
 cout << "Out of luck!" << endl;
 }
*/