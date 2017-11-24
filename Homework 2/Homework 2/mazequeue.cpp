//
//  mazequeue.cpp
//  2
//
//  Created by 杨博超 on 16/4/25.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#include <iostream>
#include <queue>

using namespace std;

//////////////////////////////-----------FUNCTION PROTOTYPES----------///////////////////////////////


bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// return false otherwise

//////////////////////////////-----------COORDINATE CLASS----------///////////////////////////////

class Coord     //Copied from Spec
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

//////////////////////////////-----------PATHEXISTS FUNCTION IMPLEMENTATION----------///////////////////////////////

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    queue<Coord> coordOfQueue;        // Create a queue of coordinates
    Coord startPoint(sr,sc);
    coordOfQueue.push(startPoint);    // Enqueue the coordinates of the startpoint
    maze[sr][sc] = '*';             // Visited, so mark it
    
    int row = sr;
    int col = sc;
    
    while (!coordOfQueue.empty()) // While the stack is not empty
    {
        startPoint = coordOfQueue.front();  // Update coordinates of the front item and then pop them
        row = startPoint.r();
        col = startPoint.c();
        coordOfQueue.pop();
        
        if (row == er && col == ec)     // Check if it is done
        {
            return true;
        }
        
        if (maze[row - 1][col] == '.')  // Check whether can move North
        {
            Coord next(row-1,col);
            coordOfQueue.push(next);      // Enqueue the North next Coordinates
            maze[row-1][col] = '*';     // Visited, so mark it
        }
        if (maze[row][col + 1] ==  '.') // Check whether can move East
        {
            Coord next(row, col+1);
            coordOfQueue.push(next);      // Enqueue the East next Coordinates
            maze[row][col+1] = '*';     // Visited, so mark it
        }
        if (maze[row + 1][col] ==  '.') // Check whether can move South
        {
            Coord next(row +1, col);
            coordOfQueue.push(next);      // Enqueue the South next Coordinates
            maze[row+1][col] = '*';     // Visited, so mark it
        }
        if (maze[row][col - 1] ==  '.') // Check whether can move West
        {
            Coord next(row, col-1);
            coordOfQueue.push(next);      // Enqueue the West next Coordinates
            maze[row][col-1] = '*';     // Visited, so mark it
        }
    }
    return false;
}

//////////////////////////////-----------MAIN----------///////////////////////////////

int main()  // Test case
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','.','.','.','.','.','.','.','.','X'},
        { 'X','X','.','X','.','X','X','X','X','X'},
        { 'X','.','.','X','.','X','.','.','.','X'},
        { 'X','.','.','X','.','.','.','X','.','X'},
        { 'X','X','X','X','.','X','X','X','.','X'},
        { 'X','.','X','.','.','.','.','X','X','X'},
        { 'X','.','.','X','X','.','X','X','.','X'},
        { 'X','.','.','.','X','.','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };
    
    if (pathExists(maze, 6,4, 1,1))
        cout << "Solved!" << endl;
    else
        cout << "Unsolved!" << endl;
    return 0;
}