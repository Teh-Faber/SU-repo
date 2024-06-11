#pragma once

#include <QtSql>
#include <unistd.h>

class Character{
public:
    QString name;
    int hp;
    int damage;
    int xp;

    Character(QString name, int hp, int damage, int xp): name(name), hp(hp), damage(damage), xp(xp){}

    // hero no longer has fixed damage
    Character(QString name, int hp, int xp): name(name), hp(hp), damage(0), xp(xp){}


    virtual bool attack(Character& oppenent){

        usleep(300000); // wait for a bit

        qDebug() << "\n-----------------------------";
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
        oppenent.hp -= damage;

        qDebug() << oppenent.name << "took" << damage << "points of damage. Leaving them at" << oppenent.hp << "hp";

        if(oppenent.hp <= 0){
            qDebug() << "----------------------------" << "\n";
            qDebug() << name << "defeated" << oppenent.name;
            return false;// return false when oppenent dies
        }
        return true;
    }

};
