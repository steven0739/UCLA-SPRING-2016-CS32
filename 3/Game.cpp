// Game.cpp

#include "provided.h"
#include "support.h"
#include <iostream>
using namespace std;

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black); 
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play(); 
    int checkerAt(int c, int r) const;
  private:
    int m_winner;
    int toWin;
    int turn;
    Scaffold* sf;
    Player* odd;
    Player* even;
    int startRow;
    int startCol;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    sf = new Scaffold(nColumns, nLevels);
    odd = red;
    even = black;
    toWin = N;
    turn = 1;
}

bool GameImpl::completed(int& winner) const
{
    int countInRow = 1;
    int status = 2;
    
    // defnitely not complete
    if (turn == 1)
    {
        return false;
    }
    
    if (toWin == 1)
    {
        status = RED;
    }
    
    //changePlayer
    if (turn % 2 == 0) //red just took turn
    {
        // check downward
        if (status ==2)
        {
            if (sf->checkerAt(startCol, startRow - countInRow) == RED)
            {
                while (sf->checkerAt(startCol, startRow - countInRow) == RED)
                {
                    countInRow++;
                    if (countInRow == toWin)
                    {
                        status = RED;
                        break;
                    }
                }
                if (countInRow != toWin)
                {
                    countInRow = 1;
                }
            }
        }
        
        // check horizontally
        if (status == 2)
        {
            if (sf->checkerAt(startCol + countInRow, startRow) == RED || sf->checkerAt(startCol - countInRow, startRow) == RED)
            {
                int left = 0;
            
                while (sf->checkerAt(startCol - countInRow, startRow) == RED)
                {
                    countInRow++;
                    if (countInRow == toWin)
                    {
                        status = RED;
                        break;
                    }
                }
            
                if (countInRow != toWin)
                {
                    left = countInRow;
                    countInRow = 1;
            
                    while (sf->checkerAt(startCol + countInRow, startRow) == RED)
                    {
                        countInRow++;
                        if (left + countInRow - 1 == toWin)
                        {
                            status = RED;
                            break;
                        }
                    }
                }
                countInRow = 1;
            }
        }
        
        // check upper left to lower right diagonally, in two parts, and eventually sum up
        if (status == 2)
        {
            if (sf->checkerAt(startCol - countInRow, startRow + countInRow) == RED || sf->checkerAt(startCol + countInRow, startRow - countInRow) == RED)
            {
                int leftUp = 0;
            
                while (sf->checkerAt(startCol - countInRow, startRow + countInRow) == RED)
                {
                    countInRow++;
                    if (countInRow == toWin)
                    {
                        status = RED;
                        break;
                    }
                }
                if (countInRow != toWin)
                {
                    leftUp = countInRow;
                    countInRow = 1;
            
                    while (sf->checkerAt(startCol + countInRow, startRow - countInRow) == RED)
                    {
                        countInRow++;
                        if (leftUp + countInRow - 1 == toWin)
                        {
                            status = RED;
                            break;
                        }
                    }
                }
                countInRow = 1;
            }
        }
        
        // check lower left to upper right diagonally, in two parts, and eventually sum up
        if (status == 2)
        {
            if (sf->checkerAt(startCol - countInRow, startRow - countInRow) == RED || sf->checkerAt(startCol + countInRow, startRow + countInRow) == RED)
            {
                int leftDown = 0;
            
                while (sf->checkerAt(startCol - countInRow, startRow - countInRow) == RED)
                {
                    countInRow++;
                    if (countInRow == toWin)
                    {
                        status = RED;
                        break;
                    }
                }
                if (countInRow != toWin)
                {
                    leftDown = countInRow;
                    countInRow = 1;
            
                    while (sf->checkerAt(startCol + countInRow, startRow + countInRow) == RED)
                    {
                        countInRow++;
                        if (leftDown + countInRow - 1 == toWin)
                        {
                            status = RED;
                            break;
                        }
                    }
                }
                countInRow = 1;
            }
        }
    }
    
    if (turn % 2 == 1) //black just took turn
    {
        // check downward
        if (sf->checkerAt(startCol, startRow - countInRow) == BLACK)
        {
            while (sf->checkerAt(startCol, startRow - countInRow) == BLACK)
            {
                countInRow++;
                if (countInRow == toWin)
                {
                    status = BLACK;
                    break;
                }
            }
            if (countInRow != toWin)
            {
                countInRow = 1;
            }
        }
        
        // check horizontally
        if (status == 2)
        {
            if (sf->checkerAt(startCol - countInRow, startRow) == BLACK || sf->checkerAt(startCol + countInRow, startRow) == BLACK)
            {
                int left = 0;
            
                while (sf->checkerAt(startCol - countInRow, startRow) == BLACK)
                {
                    countInRow++;
                    if (countInRow == toWin)
                    {
                        status = BLACK;
                        break;
                    }
                }
                if (countInRow != toWin)
                {
                    left = countInRow;
                    countInRow = 1;
            
                    while (sf->checkerAt(startCol + countInRow, startRow) == BLACK)
                    {
                        countInRow++;
                        if (left + countInRow - 1 == toWin)
                        {
                            status = BLACK;
                            break;
                        }
                    }
                }
                countInRow = 1;
            }
        }
        
        // check upper left to lower right diagonally, in two parts, and eventually sum up
        if (status == 2)
        {
            if (sf->checkerAt(startCol - countInRow, startRow + countInRow) == BLACK || sf->checkerAt(startCol + countInRow, startRow - countInRow) == BLACK)
            {
                int leftUp = 0;
            
                while (sf->checkerAt(startCol - countInRow, startRow + countInRow) == BLACK)
                {
                    countInRow++;
                    if (countInRow == toWin)
                    {
                        status = BLACK;
                        break;
                    }
                }
                if (countInRow != toWin)
                {
                    leftUp = countInRow;
                    countInRow = 1;
            
                    while (sf->checkerAt(startCol + countInRow, startRow - countInRow) == BLACK)
                    {
                        countInRow++;
                        if (leftUp + countInRow - 1 == toWin)
                        {
                            status = BLACK;
                            break;
                        }
                    }
                }
                countInRow = 1;
            }
        }
        
        // check lower left to upper right diagonally, in two parts, and eventually sum up
        if (status == 2)
        {
            if (sf->checkerAt(startCol - countInRow, startRow - countInRow) == BLACK || sf->checkerAt(startCol + countInRow, startRow + countInRow) == BLACK)
            {
                int leftDown = 0;
            
                while (sf->checkerAt(startCol - countInRow, startRow - countInRow) == BLACK)
                {
                    countInRow++;
                    if (countInRow == toWin)
                    {
                        status = BLACK;
                        break;
                    }
                }
                if (countInRow != toWin)
                {
                    leftDown = countInRow;
                    countInRow = 1;
            
                    while (sf->checkerAt(startCol + countInRow, startRow + countInRow) == BLACK)
                    {
                        countInRow++;
                        if (leftDown + countInRow - 1 == toWin)
                        {
                            status = BLACK;
                            break;
                        }
                    }
                }
                countInRow = 1;
            }
        }
    }

    if(status != 2) //over
    {
        winner = status;
        return true;
    }
    else if(sf->numberEmpty() == 0) //isn't over, no space
    {
        winner = TIE_GAME;
        return true;
    }
    else //isn't over, do nothing, return false
        return false;
}

bool GameImpl::takeTurn()
{
    //checkIsEnd;
    if (completed(m_winner))
    {
        return false;
    }
    
    //changePlayer
    if (turn % 2 == 1) //red turn
    {
        int columnChoosen = odd->chooseMove(*sf, toWin, RED);
        startCol = columnChoosen;
        sf->makeMove(columnChoosen, RED); //update grid
        for (int i = 2; i < sf->levels() + 2; i++)
        {
            if (sf->checkerAt(columnChoosen, i) == VACANT)
            {
                startRow = i - 1; //mark the starting position
                break;
            }
        }
    }
    
    if (turn % 2 == 0) //black turn
    {
        int columnChoosen = even->chooseMove(*sf, toWin, BLACK);
        startCol = columnChoosen;
        sf->makeMove(columnChoosen, BLACK); //update grid
        for (int i = 2; i < sf->levels() + 2; i++)
        {
            if (sf->checkerAt(columnChoosen, i) == VACANT)
            {
                startRow = i - 1; //mark the starting position
                break;
            }
        }
    }
    
    turn++;
    return true;
}

void GameImpl::play()
{
    // both player not interactive
    while (!completed(m_winner))
    {
        if (!odd->isInteractive() && !even->isInteractive())
        {
            cout << "Please press enter to continue: " << endl;
            cin.ignore(10000, '\n');
            takeTurn();
            sf->display();
            cout << endl;
        }
        else
        {
            takeTurn();
            sf->display();
            cout << endl;
        }
    }
    
    // check the result
    if (m_winner == -1)
    {
        cout << "It's a tie game!" << endl;
    }
    if (m_winner == 0)
    {
        cout << "The winner is: " << odd->name() << endl;
    }
    if (m_winner == 1)
    {
        cout << "The winner is: " << even->name() << endl;
    }
}

int GameImpl::checkerAt(int c, int r) const
{
    return sf->checkerAt(c, r);
} 

//******************** Game functions *******************************

// These functions simply delegate to GameImpl's functions.
// You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
