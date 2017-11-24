// Player.cpp
#include <iostream>
#include <string>
#include "provided.h"
#include "support.h"
using namespace std;

class HumanPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);};

class SmartPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    // receive the input by the player
    // make a move at that col, the uppest spot
    if (s.numberEmpty())
    {
        cout << "Choose a column: " << endl;
        int k;
        cin >> k;
        while (k < 1 || k > s.cols() || s.checkerAt(k, s.levels()) != VACANT)
        {
            cout << "Invalid, choose a different column: "<< endl;
            cin >> k;
        }
        return k;
    }
    return -1;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    // just from down to up,left to right
    if (s.numberEmpty())
    {
        for (int i = 1; i < s.levels() + 1; i++)
        {
            for (int k = 1; k < s.cols() + 1; k++)
            {
                if (s.checkerAt(k, i) == -1)
                {
                    return k; // the lower left vacant grid has priority
                }
            }
        }
    }
    return -1;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color) // check full, -1
{
    Scaffold testS = s;
    bool sequence = true; // in order to have computer choose the max
    int depth = 0; // initial condition
    return determineBestMove(testS, N, color, depth, sequence).first; // .first saves the col choosen
    //return 1;
}

//******************** Player derived class functions *************************

// These functions simply delegate to the Impl classes' functions.
// You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
: Player(nm)
{
    m_impl = new HumanPlayerImpl;
}

HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}

int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
: Player(nm)
{
    m_impl = new BadPlayerImpl;
}

BadPlayer::~BadPlayer()
{
    delete m_impl;
}

int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
: Player(nm)
{
    m_impl = new SmartPlayerImpl;
}

SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}

int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
