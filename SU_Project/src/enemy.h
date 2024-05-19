#pragma once

#include "character.h"
#include <QtSql>


class Enemy: public Character{

public:
    Enemy(QString name, int hp, int strength, int xp): Character(name, hp, strength, xp){}
};

