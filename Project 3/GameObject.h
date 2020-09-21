//
//  GameObject.h
//  cs32-p3
//
//  Created by Stephen Chu on 5/14/20.
//  Copyright © 2020 Steven Chu. All rights reserved.
//

#ifndef GameObject_h
#define GameObject_h
#include <string>
using namespace std;

class GameObject
{
public:
    GameObject(int row, int col, string name);
    virtual ~GameObject();
    string name() const;
    int row() const;
    int col() const;
private:
    int m_row;
    int m_col;
    string m_name;
    
};

class Scroll : public GameObject
{
public:
    Scroll(int row, int col, string name);
    ~Scroll();
    string read() const;
private:
    string m_type;
};

class Weapon : public GameObject
{
public:
    Weapon(int row, int col, string name);
    ~Weapon();
    string attackAction() const;
    int dexterityBonus() const;
    int damageAmount() const;
private:
    int m_dexterityBonus;
    int m_damageAmount;
    string m_attackAction;
};

#endif /* GameObject_h */
