#pragma once

#include "character.h"
#include <QtSql>

class Hero: public Character{
public:
    int level;
    int id;

    Hero(QString name): Character(name, 10, 2, 0), level(1), id(0){} // new hero

    Hero(QString name, int hp, int strength, int xp, int level, int id): Character(name, hp, strength, xp), level(level), id(id){} // load hero

    bool attack(Character& enemy) override{
        bool result = Character::attack(enemy);

        if(!result) levelUp(enemy); // if enemy dies levelup hero

        return result;
    }

    void levelUp(Character& enemy){

        qDebug() << name << "gained" << enemy.xp << "xp";
        xp += enemy.xp;

        if(xp > 1000*level){ // xp requirement increase with level
            xp = xp-(1000*level);
            level++;
            hp += 2;
            strength++;
            qDebug() << name << "is now level" << level;
        }
    }

    void restoreHp(){
        hp = 8 + 2*level;
    }
};

