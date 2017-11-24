//
//  creature.cpp
//  1
//
//  Created by 杨博超 on 16/4/28.
//  Copyright © 2016年 杨博超. All rights reserved.
//

/*
#include <iostream>
#include <string>
using namespace std;
*/

class Creature
{
public:
    Creature (string name);
    virtual ~Creature();
    virtual string name() const;
    virtual string move() const;
    virtual bool isMortal() const = 0;

private:
    string m_name;
};

class Phoenix: public Creature
{
public:
    Phoenix(string name)
    :Creature(name)
    {}
    virtual ~Phoenix();
    virtual string move() const;
    virtual bool isMortal() const;
};

class Giant: public Creature
{
public:
    Giant(string name, int weight)
    :Creature(name),m_weight(weight)
    {}
    virtual ~Giant();
    virtual string move() const;
    virtual bool isMortal() const;
private:
    int m_weight;
};

class Centaur: public Creature
{
public:
    Centaur(string name)
    :Creature(name)
    {}
    virtual ~Centaur();
    virtual string move() const;
    virtual bool isMortal() const;
};

Creature::Creature(string name)
:m_name(name)
{}

Creature::~Creature()
{}

string Creature::name() const
{
    return m_name;
}

string Creature::move() const
{
    return "walk";
}

Phoenix::~Phoenix()
{
    cout << "Destroying " << Creature::name() << " the phoenix" << endl;
}

string Phoenix::move() const
{
    return "fly";
}

bool Phoenix::isMortal() const
{
    return false;
}

Giant::~Giant()
{
    cout << "Destroying " << Creature::name() << " the giant" << endl;
}

string Giant::move() const
{
    if(m_weight < 20)
        return "trump";
    else
        return "lumber";
}

bool Giant::isMortal() const
{
    return true;
}

Centaur::~Centaur()
{
    cout << "Destroying " << Creature::name() << " the centaur" << endl;
}

string Centaur::move() const
{
    return "trot";
}

bool Centaur::isMortal() const
{
    return true;
}

void animate(const Creature* c)
{
    cout << c->name() << ", who is ";
    if (c->isMortal())
        cout << "mortal";
    else
        cout << "immortal";
    cout << ", will now " << c->move() << ".\n";
}

/*
int main()
{
    Creature* creatures[4];
    creatures[0] = new Phoenix("Squawkes");
    // Giants have a name and a weight in tons.  Giants under 20 tons
    // walk by tromping; giants weighing at least 20 tons lumber.
    creatures[1] = new Giant("Frawp", 17);
    creatures[2] = new Giant("Gridwulfa", 22);
    creatures[3] = new Centaur("Florence");
    
    cout << "Here are the creatures." << endl;
    for (int k = 0; k < 4; k++)
        animate(creatures[k]);
    
    // Clean up the creatures before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete creatures[k];
}

int main()
{
    cout << "Here are the creatures." << endl
    << "Squawkes, who is immortal, will now fly." << endl
    << "Frawp, who is mortal, will now tromp." << endl
    << "Gridwulfa, who is mortal, will now lumber." << endl
    << "Florence, who is mortal, will now trot." << endl
    << "Cleaning up." << endl
    << "Destroying Squawkes the phoenix." << endl
    << "Destroying Frawp the giant." << endl
    << "Destroying Gridwulfa the giant." << endl
    << "Destroying Florence the centaur." << endl;

}
*/