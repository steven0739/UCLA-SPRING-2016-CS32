//
//  Game.h
//  Project 1
//
//  Created by 杨博超 on 16/4/4.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#ifndef Game_h
#define Game_h

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

#endif /* Game_h */
