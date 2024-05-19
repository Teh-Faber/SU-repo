#pragma once

#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include "character.h"
#include "hero.h"
#include "enemy.h"
#include "dungeon.h"

class Game{
    QSqlDatabase _db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery _q;
    std::shared_ptr<Hero> currentHero;

    void resetDatabase(){ // reset game
        if(!_q.exec("DROP TABLE IF EXISTS Heros;")){
            qDebug()  << "Delete table failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("DROP TABLE IF EXISTS Enemies;")){
            qDebug()  << "Delete table failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("DROP TABLE IF EXISTS Enemy_list;")){
            qDebug()  << "Delete table failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("DROP TABLE IF EXISTS Dungeons;")){
            qDebug()  << "Delete table failed:"  << _q.lastError() << "\n";
        }

        initDatabase();
    };

    void initDatabase(){ // initiate game database.
        // Heros
        // check if already exists
        _q.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Heros';");
        if(!_q.next()){
            //if it doesnt create and fill with default values
            if(!_q.exec("CREATE TABLE Heros( "
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT, "
                        "name char(125) NOT NULL, "
                        "hp integer NOT NULL, "
                        "strength integer NOT NULL, "
                        "xp integer NOT NULL, "
                        "level integer NOT NULL, "
                        "gold integer NOT NULL);")){
                qDebug()  << "Initate table failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }

            if(!_q.exec("INSERT INTO Heros (name, hp, strength, xp, level, gold) "
                        "VALUES ('Timmy', 10, 2, 0, 1, 0);")){
                qDebug()  << "Initate table failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }
        }

        // Enemies
        // check if already exists
        _q.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Enemies';");
        if(!_q.next()){
            //if it doesnt create and fill with default values
            if(!_q.exec("CREATE TABLE Enemies( "
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT, "
                        "name char(125) NOT NULL, "
                        "hp integer NOT NULL, "
                        "strength integer NOT NULL, "
                        "xp integer NOT NULL);")){
                qDebug()  << "Initate table failed:"  << _q.lastError() << "\n"; // if not succesfull print error
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
                qDebug()  << "Initate table failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }
        }

        // Dungeons
        // check if already exists
        _q.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Dungeons';");
        if(!_q.next()){
            //if it doesnt create and fill with default values
            if(!_q.exec("CREATE TABLE Dungeons( "
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT, "
                        "name char(125) NOT NULL, "
                        "gold integer NOT NULL);")){
                qDebug()  << "Initate table failed:"  << _q.lastError() << "\n"; // if not succesfull print error
            }

            if(!_q.exec("INSERT INTO Dungeons (name, gold) "
                        "VALUES ('The Dread Tunnels', 100),"
                        "('The Rugged Grotto', 200),"
                        "('Vault of the Perished Goblin', 400),"
                        "('The Dragon Lair', 3000);")){
                qDebug()  << "Initate table failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }
        }

        // check if already exists
        _q.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Enemy_list';");
        if(!_q.next()){
            //if it doesnt create and fill with default values
            if(!_q.exec("CREATE TABLE Enemy_list( "
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT, "
                        "dungeon_id integer NOT NULL, "
                        "enemy_id integer NOT NULL, "
                        "FOREIGN KEY (dungeon_id) REFERENCES Dungeons(id), "
                        "FOREIGN KEY (enemy_id) REFERENCES Enemies(id));")){
                qDebug()  << "Initate table failed:"  << _q.lastError() << "\n"; // if not succesfull print error
            }

            if(!_q.exec("INSERT INTO Enemy_list (dungeon_id, enemy_id) "
                        "VALUES "
                        "(1, 2),"
                        "(1, 2),"
                        "(1, 3),"
                        "(1, 3),"
                        "(2, 3),"
                        "(2, 4),"
                        "(2, 4),"
                        "(2, 5),"
                        "(3, 5),"
                        "(3, 5),"
                        "(3, 5),"
                        "(3, 6),"
                        "(4, 8);")){
                qDebug()  << "Initate table failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }
        }
    }


public:

    Game(){
        _db.setDatabaseName("gameData");
        if (!_db.open()) qDebug() << "Failed to connect to Database";

        //resetDatabase();
        initDatabase();

        menu();
    }

    void menu(){
        int choice;
        do {
            qDebug() << "Press enter to continue to menu";
            // wait for a enter keypress
            QTextStream in(stdin);
            forever {
                QString line = in.readLine();
                if (!line.isNull())
                    break;
            }
            std::system("clear"); // clear terminal when menu is opened

            qDebug() << "\nMenu:";
            qDebug() << "1. Load Hero";
            qDebug() << "2. Create New Hero";
            qDebug() << "3. Select a Dungeon";
            qDebug() << "4. Save & Exit";

            qDebug() << "Enter your choice: ";
            choice = in.readLine().toInt();

            switch (choice) {
            case 1:
                std::system("clear"); // clear terminal

                if(currentHero){ // save the current hero
                    save();
                }
                loadHero(); // load new hero
                break;

            case 2:
                std::system("clear"); // clear terminal

                if(currentHero){ // save the current hero
                    save();
                }
                newHero(); // create new hero
                break;

            case 3:
                std::system("clear"); // clear terminal

                if(!currentHero){ // check for a hero
                    qDebug() << "\nYou have no hero to fight for you! Please load a hero & try again.";
                }else{
                    selectDungeon(); // fight enemy
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
            int     gold    = _q.value(6).toInt();
            qDebug()  << id << ":" << name << "\t"  << "Hp:" << hp << "\t" << "Strength:" << strength << "\t" <<  "Xp:" << xp << "Level:" << level << "Gold:" << gold;
        }

        qDebug() << "Enter the index of your choice:";
        QTextStream in(stdin);
        int choice = in.readLine().toInt();

        // prepare query of selecting hero
        _q.prepare("SELECT * FROM Heros WHERE id = ? ;");

        _q.addBindValue(choice);

        if(!_q.exec()){
            qDebug()  << "\nSelect hero failed:" << _q.lastError() << "\n";
            return ;
        }

        if(!_q.next()){ // next to select one hero in case none matches
            qDebug()  << "\nNo hero at that index";
            return ;
        }

        qDebug()  << "\nHero loaded succesfully";

        // load hero data from database
        int     id      = _q.value(0).toInt();
        QString name    = _q.value(1).toString();
        int     hp      = _q.value(2).toInt();
        int     strength= _q.value(3).toInt();
        int     xp      = _q.value(4).toInt();
        int     level   = _q.value(5).toInt();
        int     gold    = _q.value(6).toInt();
        currentHero = std::make_shared<Hero>(Hero(name, hp, strength, xp, level, id, gold)); // throw hero on the heap and point to him
    }


    void newHero(){ // create new hero and make them current hero
        qDebug() << "\nPlease enter the name of your new Hero: ";
        QTextStream in(stdin);
        QString name = in.readLine();

        currentHero = std::make_shared<Hero>(Hero(name));

        qDebug() << "\nHero created succesfully";
    }


    void selectDungeon(){ // select dungeon for current hero to explore
        QSqlQuery temp_q;
        std::vector<Enemy> enemies;

        qDebug() << "\n--- Loading Dungeons ---" << "";

        if(!_q.exec("SELECT * FROM Dungeons")){
            qDebug()  << "\nLoad Dungeons failed:"  << _q.lastError() << "\n";
            return ;
        }


        while (_q.next()) { // print all dungeons from query
            qDebug() << "\n" << _q.value(0).toInt() << ":" << _q.value(1).toString() << "Gold:" << _q.value(2).toInt() << "\n\tEnemies:";
            // select all enemies with id
            temp_q.prepare("SELECT * FROM Enemies INNER JOIN Enemy_list ON Enemies.id = Enemy_list.enemy_id WHERE Enemy_list.dungeon_id = ?;");
            temp_q.addBindValue(_q.value(0).toInt());

            if(!temp_q.exec()){
                qDebug()  << "\nLoad Enemies failed:"  << _q.lastError() << "\n";
                return ;
            }

            while (temp_q.next()) { // print all enemies from query
                QString name    = temp_q.value(1).toString();
                int     hp      = temp_q.value(2).toInt();
                int     strength= temp_q.value(3).toInt();
                int     xp      = temp_q.value(4).toInt();
                qDebug() << "\t" << name << "\t"  << "Hp:" << hp << "\t" << "Strength:" << strength << "\t" <<  "Xp:" << xp;
            }
        }

        qDebug() << "\nPlease enter the index of the dungeon you wish to enter:";
        QTextStream in(stdin);
        int choice = in.readLine().toInt();

        // prepare query of selecting dungeon
        _q.prepare("SELECT * FROM Dungeons WHERE id = ? ;");
        _q.addBindValue(choice);

        if(!_q.exec()){ // select the dungeon
            qDebug()  << "\nSelect Dungeon failed:" << _q.lastError() << "\n";
            return ;
        }

        if(!_q.next()){ // next to select one dungeon in case none exist
            qDebug()  << "\nNo Dungeon at that index";
            return ;
        }

        // select all enemies in dungeon
        temp_q.prepare("SELECT * FROM Enemies INNER JOIN Enemy_list ON Enemies.id = Enemy_list.enemy_id WHERE Enemy_list.dungeon_id = ?;");
        temp_q.addBindValue(_q.value(0).toInt());

        if(!temp_q.exec()){
            qDebug()  << "\nLoad Enemies failed:"  << _q.lastError() << "\n";
            return ;
        }

        while(temp_q.next()){
            // load from database
            QString name    = temp_q.value(1).toString();
            int     hp      = temp_q.value(2).toInt();
            int     strength= temp_q.value(3).toInt();
            int     xp      = temp_q.value(4).toInt();

            enemies.push_back(Enemy(name, hp, strength, xp)); // create the enemy
        }

        std::system("clear"); // clear terminal

        Dungeon dungeon(_q.value(1).toString(), _q.value(2).toInt(), enemies);

        qDebug() << "\nYour Hero" << currentHero->name << "will enter"<< dungeon.name;

        for(Enemy enemy: dungeon.enemies){
            qDebug() << currentHero->name << "encoutered" << enemy.name;
            while(currentHero->attack(enemy) && enemy.attack(*currentHero)){} // keep figthing untill someone dies

            if(currentHero->hp <= 0){ // if hero dies he is deleted
                //delete from database
                _q.prepare("DELETE FROM Heros WHERE id = ? AND name = ?;");
                _q.addBindValue(currentHero->id);
                _q.addBindValue(currentHero->name);

                if(!_q.exec()){
                    qDebug()  << "\nDelete hero failed:"  << _q.lastError() << "\n";
                }

                // delete from memory & exit
                currentHero.reset();
                return;

            }else{ // hero gets his hp restored after the fight
                currentHero->restoreHp();
            }
        }

        currentHero->gold += dungeon.gold;

        qDebug() << "Your Hero" << currentHero->name << "defeated all enemies in" << dungeon.name << "and gained" << dungeon.gold << "gold";
    }


    void save(){ // save current hero to database
        _q.clear(); // clear query to make space for prepare

        // update hero
        _q.prepare("UPDATE Heros SET hp = ?, strength = ?, xp = ?, level = ?, gold = ? WHERE id = ? AND name = ?;");
        _q.addBindValue(currentHero->hp);
        _q.addBindValue(currentHero->strength);
        _q.addBindValue(currentHero->xp);
        _q.addBindValue(currentHero->level);
        _q.addBindValue(currentHero->gold);
        _q.addBindValue(currentHero->id);
        _q.addBindValue(currentHero->name);

        if(!_q.exec()){
            qDebug()  << "\nSave failed:"  << _q.lastError() << "\n";
        }

        // if they dont exist insert into table
        if(_q.numRowsAffected() == 0){
            _q.prepare("INSERT INTO Heros (name, hp, strength, xp, level, gold) "
                       "VALUES (?, ?, ?, ?, ?, ?);");
            _q.addBindValue(currentHero->name);
            _q.addBindValue(currentHero->hp);
            _q.addBindValue(currentHero->strength);
            _q.addBindValue(currentHero->xp);
            _q.addBindValue(currentHero->level);
            _q.addBindValue(currentHero->gold);

            if(!_q.exec()){
                qDebug()  << "\nSave failed:"  << _q.lastError() << "\n";
            }
        }

        // remove hero from memory
        currentHero.reset();
    }
};
