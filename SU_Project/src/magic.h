#pragma once

#include <QtSql>

class Magic{
public:
    int id;
    QString name;
    int damage;
    int selfDamage;
    int manaCost;
    int element_id;
    QString element;

    Magic(int id, QString name, int damage, int selfDamage, int manaCost, int element_id, QString element):
        id(id), name(name), damage(damage), selfDamage(selfDamage), manaCost(manaCost), element_id(element_id), element(element){}
};
