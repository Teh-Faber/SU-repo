#pragma once

#include <QtSql>
#include <vector>
#include "enemy.h"

class Dungeon{
public:
    QString name;
    int gold;
    std::vector<Enemy> enemies;

    Dungeon(QString name, int gold, std::vector<Enemy> enemies): name(name), gold(gold), enemies(enemies){}
};
