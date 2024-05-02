#pragma once

#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include "character.h"
#include "hero.h"
#include "enemy.h"

class Game{
    QSqlDatabase _db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery _q;
    std::shared_ptr<Hero> currentHero;

public:

    Game(){
        _db.setDatabaseName("gameData");
        if (!_db.open()) qDebug() << "Failed to connect to Database";

        initDatabase();

        menu();
    }

    void menu(){
        int choice;
        do {
            qDebug() << "\nMenu:";
            qDebug() << "1. Load Hero";
            qDebug() << "2. Create New Hero";
            qDebug() << "3. Figth Enemy";
            qDebug() << "4. Save & Exit";

            qDebug() << "Enter your choice: ";
            QTextStream cin(stdin);
            choice = cin.readLine().toInt();

            switch (choice) {
            case 1:
                if(currentHero){ // save the current hero
                    save();
                }
                loadHero(); // load new hero
                break;

            case 2:
                if(currentHero){ // save the current hero
                    save();
                }
                newHero(); // create new hero
                break;

            case 3:
                if(!currentHero){ // check for a hero
                    qDebug() << "\nYou have no hero to fight for you! Please load a hero & try again.";
                }else{
                    fight(); // fight enemy
                }
                break;

            case 4:
                qDebug() << "\nExiting...\n";
                save(); // save before exiting
                break;

            default:
                qDebug() << "\nInvalid choice! Please try again.";
            }
        } while(choice != 4); // exit
    }


    void loadHero(){ // load hero into current hero
        qDebug() << "\n--- Loading Heros ---" << "";

        if(!_q.exec("SELECT * FROM Heros")){ // execute query and print status
            qDebug()  << "\nLoad Heros failed:"  << _q.lastError() << "\n";
            return ;
        }


        while (_q.next()) { // print all rows from query
            int     id      = _q.value(0).toInt();
            QString name    = _q.value(1).toString();
            int     hp      = _q.value(2).toInt();
            int     strength= _q.value(3).toInt();
            int     xp      = _q.value(4).toInt();
            int     level   = _q.value(5).toInt();
            qDebug()  << id << ":" << name << "\t"  << "Hp:" << hp << "\t" << "Strength:" << strength << "\t" <<  "Xp:" << xp << "Level:" << level;
        }

        qDebug() << "Enter the index of your choice:";
        QTextStream cin(stdin);
        int choice = cin.readLine().toInt();

        // prepare query of selecting hero
        _q.prepare("SELECT * FROM Heros WHERE hero_id = ? ;");

        _q.addBindValue(choice);

        if(!_q.exec()){
            qDebug()  << "\nSelect hero failed:" << _q.lastError() << "\n";
            return ;
        }

        if(!_q.next()){ // next to select one hero in case none or duplicate names matches
            qDebug()  << "\nSelect hero failed";
            return ;
        }

        // load hero data from database
        int     id      = _q.value(0).toInt();
        QString name    = _q.value(1).toString();
        int     hp      = _q.value(2).toInt();
        int     strength= _q.value(3).toInt();
        int     xp      = _q.value(4).toInt();
        int     level   = _q.value(5).toInt();

        currentHero = std::make_shared<Hero>(Hero(name, hp, strength, xp, level, id)); // throw hero on the heap and point to him
    }


    void newHero(){ // create new hero and make them current hero
        qDebug() << "\nPlease enter the name of your new Hero: ";
        QTextStream cin(stdin);
        QString name = cin.readLine();

        currentHero = std::make_shared<Hero>(Hero(name));
    }


    void fight(){ // select enemy for current hero to fight

        qDebug() << "\n--- Loading Enemies ---" << "";

        if(!_q.exec("SELECT * FROM Enemies")){
            qDebug()  << "\nLoad Enemies failed:"  << _q.lastError() << "\n";
            return ;
        }

        while (_q.next()) { // print all rows from query
            int     id      = _q.value(0).toInt();
            QString name    = _q.value(1).toString();
            int     hp      = _q.value(2).toInt();
            int     strength= _q.value(3).toInt();
            int     xp      = _q.value(4).toInt();
            qDebug() << id << ":" << name << "\t"  << "Hp:" << hp << "\t" << "Strength:" << strength << "\t" <<  "Xp:" << xp;
        }

        qDebug() << "\nPlease enter the index of the enemy you wish to fight:";
        QTextStream cin(stdin);
        int choice = cin.readLine().toInt();

        // prepare query of selecting hero
        _q.prepare("SELECT * FROM Enemies WHERE enemy_id = ? ;");

        _q.addBindValue(choice);

        if(!_q.exec()){
            qDebug()  << "\nSelect enemy failed:" << _q.lastError() << "\n";
            return ;
        }

        if(!_q.next()){ // next to select one enemy in case none or duplicate names matches
            qDebug()  << "\nSelect enemy failed";
            return ;
        }

        // load from database
        QString name    = _q.value(1).toString();
        int     hp      = _q.value(2).toInt();
        int     strength= _q.value(3).toInt();
        int     xp      = _q.value(4).toInt();

        Enemy enemy(name, hp, strength, xp);

        qDebug() << "\nYour Hero" << currentHero->name << "will fight with" << enemy.name;

        while(currentHero->attack(enemy) && enemy.attack(*currentHero)){} // keep figthing untill someone dies

        if(currentHero->hp <= 0){ // if hero dies he is deleted
            //delete from database
            _q.prepare("DELETE FROM Heros WHERE hero_id = ? AND name = ?;");
            _q.addBindValue(currentHero->id);
            _q.addBindValue(currentHero->name);

            if(!_q.exec()){
                qDebug()  << "\nDelete failed:"  << _q.lastError() << "\n";
            }
            // delete from memory
            currentHero.reset();

        }else{ // hero gets his hp restored after the fight
            currentHero->restoreHp();
        }
    }


    void save(){ // save current hero to database
        _q.clear(); // clear query to make space for prepare

        // update hero
        _q.prepare("UPDATE Heros SET hp = ?, strength = ?, xp = ?, level = ? WHERE hero_id = ? AND name = ?;");
        _q.addBindValue(currentHero->hp);
        _q.addBindValue(currentHero->strength);
        _q.addBindValue(currentHero->xp);
        _q.addBindValue(currentHero->level);
        _q.addBindValue(currentHero->id);
        _q.addBindValue(currentHero->name);

        if(!_q.exec()){
            qDebug()  << "\nSave failed:"  << _q.lastError() << "\n";
        }

        // if they dont exist insert into table
        if(_q.numRowsAffected() == 0){
            _q.prepare("INSERT INTO Heros (name, hp, strength, xp, level) "
                       "VALUES (?, ?, ?, ?, ?);");
            _q.addBindValue(currentHero->name);
            _q.addBindValue(currentHero->hp);
            _q.addBindValue(currentHero->strength);
            _q.addBindValue(currentHero->xp);
            _q.addBindValue(currentHero->level);

            if(!_q.exec()){
                qDebug()  << "\nSave failed:"  << _q.lastError() << "\n";
            }
        }
    }

    void initDatabase(){ // reset game save data.

        if(!_q.exec("DROP TABLE IF EXISTS Heros;")){
            qDebug()  << "Initate table failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("CREATE TABLE Heros( "
                    "hero_id integer NOT NULL PRIMARY KEY AUTOINCREMENT, "
                    "name char(125) NOT NULL, "
                    "hp integer NOT NULL, "
                    "strength integer NOT NULL, "
                    "xp integer NOT NULL, "
                    "level integer NOT NULL);")){
            qDebug()  << "Initate table failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("INSERT INTO Heros (name, hp, strength, xp, level) "
                    "VALUES ('Timmy', 10, 2, 0, 1);")){
            qDebug()  << "Initate table failed:"  << _q.lastError() << "\n";
        }


        if(!_q.exec("DROP TABLE IF EXISTS Enemies;")){
            qDebug()  << "Initate table failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("CREATE TABLE Enemies( "
                    "enemy_id integer NOT NULL PRIMARY KEY AUTOINCREMENT, "
                    "name char(125) NOT NULL, "
                    "hp integer NOT NULL, "
                    "strength integer NOT NULL, "
                    "xp integer NOT NULL);")){
            qDebug()  << "Initate table failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("INSERT INTO Enemies (name, hp, strength, xp) "
                    "VALUES ('Hest', 4, 1, 100),"
                    "('Weak Goblin', 4, 2, 200),"
                    "('Strong Goblin', 8, 3, 400),"
                    "('Stronger Goblin', 10, 4, 500),"
                    "('Strongest Goblin', 15, 5, 800),"
                    "('King Ape', 30, 5, 1000),"
                    "('Unicorn', 5, 8, 1500),"
                    "('Dragon', 100, 10, 3000);")){
            qDebug()  << "Initate table failed:"  << _q.lastError() << "\n";
        }
    }
};
