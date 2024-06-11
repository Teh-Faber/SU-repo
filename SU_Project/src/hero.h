#pragma once

#include "character.h"
#include "enemy.h"
#include "magic.h"
#include <unistd.h>
#include <vector>
#include <QtSql>

class Hero: public Character{
    QSqlQuery _q;
public:
    int mana;
    int level;
    int id;
    int gold;
    std::vector<Magic> inventory;

    Hero(QString name): Character(name, 10, 0), level(1), id(0), gold(0){} // new hero

    // load hero
    Hero(QString name, int xp, int level, int id, int gold):level(level), id(id), gold(gold), Character(name, 8 + 2*level, xp), mana(8 + 2*level){
        // fill inventory
        _q.prepare("SELECT * FROM Magic INNER JOIN Inventory ON Magic.id = Inventory.magic_id INNER JOIN Element ON Magic.element_id = Element.id WHERE hero_id = ?");
        _q.addBindValue(id);

        if(!_q.exec()){ // execute query and print status
            qDebug()  << "\nLoad Inventory failed:"  << _q.lastError() << "\n";
        }

        while (_q.next()) { // add all rows from query in inventory vector
            int     id          = _q.value(0).toInt();
            QString name        = _q.value(1).toString();
            int     damage      = _q.value(2).toInt();
            int     selfDamage  = _q.value(3).toInt();
            int     manaCost    = _q.value(4).toInt();
            int     element_id  = _q.value(5).toInt();
            QString element     = _q.value(10).toString();

            inventory.push_back(Magic(id, name, damage, selfDamage, manaCost, element_id, element));
        }
    }

    void printInventory(){
        int i = 0; // iterator & index
        for(Magic m: inventory){
            i++;
            qDebug() << "\t" << i << ":" << m.name << "\t" << "Damage:" << m.damage << "\t" << "Self Damage:" << m.selfDamage << "\t" << "Mana Cost:" << m.manaCost << "\t" << "Element:" << m.element;
        }
    }

    bool attack(Enemy& enemy){
        start:;
        usleep(300000); // wait for a bit

        qDebug() << "\n-----------------------------";
        qDebug() << name << "attacks" << enemy.name << "( Element:" << enemy.element << ")";
        qDebug() << "\nPlease select a magic to use to continue";

        printInventory();

        qDebug() << "Enter the index of your choice:";
        QTextStream in(stdin);
        int choice = in.readLine().toInt()-1;//-1 for zero indexing

        // if choice is outside the scope of inventory retry
        if(choice < 0 || choice > inventory.size()-1){//-1 for zero indexing
            qDebug() << "Invalid choice press enter to try again";
            //wait for a enter keypress
            QTextStream cin(stdin);
            forever {
                QString line = cin.readLine();
                if (!line.isNull())
                    break;
            }

            goto start;
        }

        // if hero doesnt have enough mana for choice retry
        if(inventory.at(choice).manaCost > mana){
            qDebug() << "You do not have enough Mana for that! Press enter to try again";
            //wait for a enter keypress
            QTextStream cin(stdin);
            forever {
                QString line = cin.readLine();
                if (!line.isNull())
                    break;
            }

            goto start;
        }

        // calculate new hero hp
        hp -= inventory.at(choice).selfDamage;
        // calculate new hero mana
        mana -= inventory.at(choice).manaCost;

        _q.prepare("SELECT * FROM Element WHERE id = ?");
        _q.addBindValue(enemy.element_id);

        if(!_q.exec()){ // execute query and print status
            qDebug()  << "\nLoad Elements failed:"  << _q.lastError() << "\n";
        }
        _q.first();
        int strongAgainst   = _q.value(2).toInt();
        int weakAgainst     = _q.value(3).toInt();

        // if choice valid continue
        // calculate new enemy hp
        if(inventory.at(choice).element_id == strongAgainst){ // if strong against
            enemy.hp -= inventory.at(choice).damage*0.5; // take half damage

            qDebug() << inventory.at(choice).name << "was not very effective";
            qDebug() << "\n" << enemy.name << "took" << inventory.at(choice).damage*0.5 << "points of damage. Leaving them at" << enemy.hp << "hp";

        }else if(inventory.at(choice).element_id == weakAgainst){ // if weak against
            enemy.hp -= inventory.at(choice).damage*2; // take double damage

            qDebug() << inventory.at(choice).name << "was super effective";
            qDebug() << "\n" << enemy.name << "took" << inventory.at(choice).damage*2 << "points of damage. Leaving them at" << enemy.hp << "hp";

        }else{
            enemy.hp -= inventory.at(choice).damage; // take normal damage

            qDebug() << "\n" << enemy.name << "took" << inventory.at(choice).damage << "points of damage. Leaving them at" << enemy.hp << "hp";

        }

        qDebug() << "\n" << name << "took" << inventory.at(choice).selfDamage << "points of damage. Leaving them at" << hp << "hp";
        qDebug() << "" << name << "has" << mana << "Mana left";

        if(enemy.hp <= 0){
            qDebug() << "\n----------------------------" << "\n";
            qDebug() << name << "defeated" << enemy.name;
            levelUp(enemy); // if enemy dies levelup hero
            return false;// return false when oppenent dies
        }
        return true;
    }

    void levelUp(Character& enemy){

        qDebug() << name << "gained" << enemy.xp << "xp" << "\n";
        xp += enemy.xp;

        while(xp > 1000*level){ // xp requirement increase with level
            xp -= (1000*level);
            level++;
            hp += 2;
            mana += 2;
            damage++;
            qDebug() << name << "is now level" << level << "\n";
        }
    }

    int restoreHp(){
        return hp = 8 + 2*level;
    }

    int restoreMana(){
        return mana = 8 + 2*level;
    }

};

