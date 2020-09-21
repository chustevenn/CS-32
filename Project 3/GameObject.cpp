//
//  GameObject.cpp
//  cs32-p3
//
//  Created by Stephen Chu on 5/14/20.
//  Copyright © 2020 Steven Chu. All rights reserved.
//

#include <iostream>
#include <string>
#include "GameObject.h"
using namespace std;

//base class constructor
GameObject::GameObject(int row, int col, string name): m_row(row), m_col(col), m_name(name)
{}

//base class destructor
GameObject::~GameObject()
{}

//trivial getters and setters
string GameObject::name() const
{
    return m_name;
}

int GameObject::row() const
{
    return m_row;
}

int GameObject::col() const
{
    return m_col;
}

// Scroll constructor: takes in the name, and position, and assigns an effect string based on the name
Scroll::Scroll(int row, int col, string name) : GameObject(row, col, name)
{
    if(name == "scroll of enhance health")
        m_type = "heal";
    if(name == "scroll of raise strength")
        m_type = "strength";
    if(name == "scroll of improve armor")
        m_type = "armor";
    if(name == "scroll of enhance dexterity")
        m_type = "dexterity";
    if(name == "scroll of teleportation")
        m_type = "teleportation";
}

// scroll destructor
Scroll::~Scroll()
{}

// return the effect of the scroll
string Scroll::read() const
{
    return m_type;
}

// Weapon constructor: takes the position and name, and assigns attributes of the weapon based on the name
Weapon::Weapon(int row, int col, string name) : GameObject(row, col, name)
{
    if(name == "short sword")
    {
        m_dexterityBonus = 0;
        m_damageAmount = 2;
        m_attackAction = "slashes short sword at";
    }
    if(name == "mace")
    {
        m_dexterityBonus = 0;
        m_damageAmount = 2;
        m_attackAction = "swings mace at";
    }
    if(name == "long sword")
    {
        m_dexterityBonus = 2;
        m_damageAmount = 4;
        m_attackAction = "swings long sword at";
    }
    if(name == "magic axe")
    {
        m_dexterityBonus = 5;
        m_damageAmount = 5;
        m_attackAction = "chops magic axe at";
    }
    if(name == "magic fangs of sleep")
    {
        m_dexterityBonus = 3;
        m_damageAmount = 2;
        m_attackAction = "strikes magic fangs at";
    }
}

// weapon destructor
Weapon::~Weapon()
{}


// getters and setters
string Weapon::attackAction() const
{
    return m_attackAction;
}

int Weapon::damageAmount() const
{
    return m_damageAmount;
}

int Weapon::dexterityBonus() const
{
    return m_dexterityBonus;
}
