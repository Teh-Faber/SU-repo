#pragma once

#include <QtSql>
#include <unistd.h>

class Character{
public:
    QString name;
    int hp;
    int strength;
    int xp;

    Character(QString name, int hp, int strength, int xp): name(name), hp(hp), strength(strength), xp(xp){}

    virtual bool attack(Character& oppenent){

        usleep(100000); // wait for a bit

        qDebug() << "-----------------------------";
        qDebug() << name << "attacks" << oppenent.name;
        qDebug() << "Press enter to continue";

        // wait for a enter keypress
        QTextStream cin(stdin);
        forever {
            QString line = cin.readLine();
            if (!line.isNull())
                break;
        }

        // calculate new hp
        oppenent.hp -= strength;

        qDebug() << oppenent.name << "took" << strength << "points of damage. Leaving them at" << oppenent.hp << "hp";

        if(oppenent.hp <= 0){
            qDebug() << "----------------------------" << "\n";
            qDebug() << name << "defeated" << oppenent.name;
            return false;// return false when oppenent dies
        }
        return true;
    }

};
