// Scaffold.cpp

#include "provided.h"
#include <stack>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels); 
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const; 
    void display() const; 
    bool makeMove(int column, int color); 
    int undoMove();
  private:
    vector<vector<char> > grid;
    int m_col;
    int m_lev;
    stack<int> m;
    stack<int> n;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    // check validity
    if (nLevels <= 0 || nColumns <= 0)
    {
        cerr << "This is an ERROR message!" << endl;
    }
    m_col = nColumns;
    m_lev = nLevels;
    
    // set grid size
    grid.resize(m_lev + 1);
    for (int i = 0; i < m_lev + 1; i++)
    {
        grid[i].resize(2*m_col + 1);
    }
    
    // make scaffold
    for (int p = 0; p < 2*m_col + 1; p++)
    {
        if (p % 2 == 0)
        {
            grid[0][p] = '+';
        }
        if (p % 2 == 1)
        {
            grid[0][p] = '-';
        }
    }
    
    for (int m = 1; m < m_lev + 1; m++)
    {
        for (int n = 0; n < m_col + 1; n++)
        {
            grid[m][2*n] = '|';
        }
    }

    for (int m = 1; m < m_lev + 1; m++)
    {
        for (int n = 0; n < m_col; n++)
        {
            grid[m][2*n + 1] = ' ';
        }
    }
}

int ScaffoldImpl::cols() const
{
    return m_col;
}

int ScaffoldImpl::levels() const
{
    return m_lev;
}

int ScaffoldImpl::numberEmpty() const
{
    // do the increment if found vacant
    int checkEmpty = 0;
    for (int i = 0; i < m_lev + 1; i++)
    {
        for (int k = 0; k < 2*m_col + 1; k++)
        {
            if (grid[i][k] == ' ')
            {
                checkEmpty++;
            }
        }
    }
    return checkEmpty;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    // directly check that spot
    if (level < 1 || level > m_lev || column < 1 || column > m_col)
    {
        return VACANT;
    };
    if (grid[level][2*column - 1] == 'B')
    {
        return BLACK;
    };
    if (grid[level][2*column - 1] == 'R')
    {
        return RED;
    };
    return VACANT;
}

void ScaffoldImpl::display() const
{
    // do two iteration, col and row
    // cout every char in the spot
    for (int m = m_lev; m != -1; m--)
    {
        for (int n = 0; n < 2*m_col + 1; n++)
        {
            cout << grid[m][n];
        }
        cout << endl;
    }
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    // check validaty
    if (column > 0 && column < m_col + 1)
    {
        if (color == 0 || color == 1)
        {
            for (int i = 1; i < m_lev + 1; i++)
            {
                if (checkerAt(column, i) == -1)
                {
                    // set color
                    if (color == 0)
                    {
                        grid[i][2*column - 1] = 'R';
                    }
                    else
                    {
                        grid[i][2*column - 1] = 'B';
                    }
                    m.push(column); // stack of col to record last move's col
                    n.push(color); // stack of color to record last move's color
                    return true;
                }
            }
        }
    }
    return false;
}

int ScaffoldImpl::undoMove()
{
    // no move been made
    if (numberEmpty() == m_lev*m_col)
    {
        return 0;
    }
    // given last move's col, make the uppest spot vacant
    for (int p = m_lev; p != 0; p--)
    {
        if (n.top() == 0)
        {
            if (grid[p][2*m.top() - 1] == 'R')
            {
                grid[p][2*m.top() - 1] = ' ';
                break;
            }
        }
        if (n.top() == 1)
        {
            if (grid[p][2*m.top() - 1] == 'B')
            {
                grid[p][2*m.top() - 1] = ' ';
                break;
            }
        }
    }
    int k = m.top(); // update the record
    m.pop();
    n.pop();
    return k;
}

//******************** Scaffold functions *******************************

// These functions simply delegate to ScaffoldImpl's functions.
// You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
