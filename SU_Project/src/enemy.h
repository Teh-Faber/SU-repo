#pragma once

#include "character.h"
#include <QtSql>


class Enemy: public Character{
public:

    int element_id;
    QString element;

    Enemy(QString name, int hp, int strength, int xp, int element_id, QString element): Character(name, hp, strength, xp), element_id(element_id), element(element){}
};

