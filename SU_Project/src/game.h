#pragma once

#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include "character.h"
#include "hero.h"
#include "enemy.h"
#include "dungeon.h"
#include "magic.h"

class Game{
    QSqlDatabase _db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery _q;
    std::shared_ptr<Hero> currentHero;

    void resetDatabase(){ // reset game
        if(!_q.exec("DROP TABLE IF EXISTS Heros;")){
            qDebug()  << "Delete table Heros failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("DROP TABLE IF EXISTS Enemies;")){
            qDebug()  << "Delete table Enemies failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("DROP TABLE IF EXISTS Enemy_list;")){
            qDebug()  << "Delete table Enemy_list failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("DROP TABLE IF EXISTS Dungeons;")){
            qDebug()  << "Delete table Dungeons failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("DROP TABLE IF EXISTS Inventory;")){
            qDebug()  << "Delete table Inventory failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("DROP TABLE IF EXISTS Magic;")){
            qDebug()  << "Delete table Magic failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("DROP TABLE IF EXISTS MagicShop;")){
            qDebug()  << "Delete table MagicShop failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("DROP TABLE IF EXISTS Requirements;")){
            qDebug()  << "Delete table Requirements failed:"  << _q.lastError() << "\n";
        }

        if(!_q.exec("DROP TABLE IF EXISTS Element;")){
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
            if(!_q.exec("CREATE TABLE Heros("
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                        "name char(125) NOT NULL,"
                        "xp integer NOT NULL,"
                        "level integer NOT NULL,"
                        "gold integer NOT NULL);")){
                qDebug()  << "Initate table Heros failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }

            if(!_q.exec("INSERT INTO Heros (name, xp, level, gold) "
                        "VALUES ('Timmy', 0, 1, 0);")){
                qDebug()  << "Initate table Heros failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }
        }

        // Element
        // check if already exists
        _q.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Element';");
        if(!_q.next()){
            //if it doesnt create and fill with default values
            if(!_q.exec("CREATE TABLE Element("
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                        "name char(125) NOT NULL,"
                        "strongAgainst integer NOT NULL,"
                        "weakAgainst integer NOT NULL);")){
                qDebug()  << "Initate table Element failed:"  << _q.lastError() << "\n"; // if not succesfull print error
            }

            if(!_q.exec("INSERT INTO Element (name, strongAgainst, weakAgainst) "
                        "VALUES "
                        "('Fire', 3, 4),"
                        "('Metal', 5, 1),"
                        "('Forest', 4, 2),"
                        "('Water', 2, 5),"
                        "('Earth', 1, 3);")){
                qDebug()  << "Initate table Element failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }
        }


        // Enemies
        // check if already exists
        _q.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Enemies';");
        if(!_q.next()){
            //if it doesnt create and fill with default values
            if(!_q.exec("CREATE TABLE Enemies("
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                        "name char(125) NOT NULL,"
                        "hp integer NOT NULL,"
                        "damage integer NOT NULL,"
                        "xp integer NOT NULL,"
                        "element_id integer NOT NULL,"
                        "FOREIGN KEY (element_id) REFERENCES Element(id));")){
                qDebug()  << "Initate table Enemies failed:"  << _q.lastError() << "\n"; // if not succesfull print error
            }

            if(!_q.exec("INSERT INTO Enemies (name, hp, damage, xp, element_id) "
                        "VALUES "
                        "('Hest', 4, 1, 100, 3),"
                        "('Weak Goblin', 4, 2, 200, 5),"
                        "('Strong Goblin', 8, 3, 400, 2),"
                        "('Stronger Goblin', 10, 4, 500, 1),"
                        "('Strongest Goblin', 15, 5, 800, 1),"
                        "('King Ape', 30, 5, 1000, 3),"
                        "('Unicorn', 5, 8, 1500, 4),"
                        "('Dragon', 100, 10, 3000, 1);")){
                qDebug()  << "Fill table Enemies failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }
        }

        // Dungeons
        // check if already exists
        _q.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Dungeons';");
        if(!_q.next()){
            //if it doesnt create and fill with default values
            if(!_q.exec("CREATE TABLE Dungeons("
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                        "name char(125) NOT NULL,"
                        "gold integer NOT NULL);")){
                qDebug()  << "Initate table Dungeons failed:"  << _q.lastError() << "\n"; // if not succesfull print error
            }

            if(!_q.exec("INSERT INTO Dungeons (name, gold) "
                        "VALUES "
                        "('The Dread Tunnels', 15),"
                        "('The Rugged Grotto', 30),"
                        "('Vault of the Perished Goblin', 70),"
                        "('The Dragon Lair', 3000);")){
                qDebug()  << "Initate table Dungeons failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }
        }

        // check if already exists
        _q.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Enemy_list';");
        if(!_q.next()){
            //if it doesnt create and fill with default values
            if(!_q.exec("CREATE TABLE Enemy_list("
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                        "dungeon_id integer NOT NULL,"
                        "enemy_id integer NOT NULL,"
                        "FOREIGN KEY (dungeon_id) REFERENCES Dungeons(id),"
                        "FOREIGN KEY (enemy_id) REFERENCES Enemies(id));")){
                qDebug()  << "Initate table Enemy_list failed:"  << _q.lastError() << "\n"; // if not succesfull print error
            }

            if(!_q.exec("INSERT INTO Enemy_list (dungeon_id, enemy_id) "
                        "VALUES "
                        "(1, 1),"
                        "(1, 2),"
                        "(1, 2),"
                        "(2, 2),"
                        "(2, 3),"
                        "(2, 4),"
                        "(3, 4),"
                        "(3, 5),"
                        "(3, 6),"
                        "(4, 8);")){
                qDebug()  << "Initate table Enemy_list failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }
        }

        // Magic
        // check if already exists
        _q.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Magic';");
        if(!_q.next()){
            //if it doesnt create and fill with default values
            if(!_q.exec("CREATE TABLE Magic("
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                        "name char(125) NOT NULL,"
                        "damage integer NOT NULL,"
                        "selfDamage integer NOT NULL,"
                        "manaCost integer NOT NULL,"
                        "element_id integer NOT NULL,"
                        "FOREIGN KEY (element_id) REFERENCES Element(id));")){
                qDebug()  << "Initate table Magic failed:"  << _q.lastError() << "\n"; // if not succesfull print error
            }

            if(!_q.exec("INSERT INTO Magic (name, damage, selfDamage, manaCost, element_id) "
                        "VALUES ('Embers', 4, 1, 2, 1),"
                        "('Knife', 1, 0, 0, 2),"
                        "('Sword', 3, 1, 0, 2),"
                        "('Morning star', 6, 3, 0, 2),"
                        "('Fire star', 12, 3, 0, 2),"
                        "('Fireball', 6, 1, 4, 1),"
                        "('Lifesteal', 2, -2, 2, 3),"
                        "('Stick', 5, 0, 1, 3),"
                        "('Mana regen', 0, 0, -5, 4),"
                        "('Health regen', 0, -10, 5, 4);")){
                qDebug()  << "Fill table Magic failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }
        }

        // MagicShop
        // check if already exists
        _q.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='MagicShop';");
        if(!_q.next()){
            //if it doesnt create and fill with default values
            if(!_q.exec("CREATE TABLE MagicShop("
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                        "magic_id integer NOT NULL,"
                        "price integer NOT NULL,"
                        "FOREIGN KEY (magic_id) REFERENCES Magic(id));")){
                qDebug()  << "Initate table MagicShop failed:"  << _q.lastError() << "\n"; // if not succesfull print error
            }

            if(!_q.exec("INSERT INTO MagicShop (magic_id, price) "
                        "VALUES "
                        "(1, 5),"
                        "(2, 0),"
                        "(3, 10),"
                        "(4, 20),"
                        "(5, 40),"
                        "(6, 15),"
                        "(7, 15),"
                        "(8, 5),"
                        "(9, 10),"
                        "(10, 20);")){
                qDebug()  << "Initate table MagicShop failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }
        }

        // Requirements
        // check if already exists
        _q.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Requirements';");
        if(!_q.next()){
            //if it doesnt create and fill with default values
            if(!_q.exec("CREATE TABLE Requirements("
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                        "magicShop_id integer NOT NULL,"
                        "magic_id integer NOT NULL,"
                        "FOREIGN KEY (magicShop_id) REFERENCES MagicShop(id),"
                        "FOREIGN KEY (magic_id) REFERENCES Magic(id));")){
                qDebug()  << "Initate table Requirements failed:"  << _q.lastError() << "\n"; // if not succesfull print error
            }

            if(!_q.exec("INSERT INTO Requirements (magicShop_id, magic_id) "
                        "VALUES "
                        "(1, 0),"
                        "(2, 0),"
                        "(3, 2),"
                        "(4, 3),"
                        "(5, 4),"
                        "(5, 6),"
                        "(6, 1),"
                        "(7, 0),"
                        "(8, 0),"
                        "(9, 0),"
                        "(10, 9);")){
                qDebug()  << "Initate table Requirements failed:"  << _q.lastError() << "\n";// if not succesfull print error
            }
        }

        // Inventory
        // check if already exists
        _q.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Inventory';");
        if(!_q.next()){
            //if it doesnt create and fill with default values
            if(!_q.exec("CREATE TABLE Inventory("
                        "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                        "hero_id integer NOT NULL,"
                        "magic_id integer NOT NULL,"
                        "FOREIGN KEY (hero_id) REFERENCES Hero(id),"
                        "FOREIGN KEY (magic_id) REFERENCES Magic(id));")){
                qDebug()  << "Initate table Inventory failed:"  << _q.lastError() << "\n"; // if not succesfull print error
            }

            if(!_q.exec("INSERT INTO Inventory (hero_id, magic_id) "
                        "VALUES "
                        "(1, 1),"
                        "(1, 2);")){
                qDebug()  << "Initate table Inventory failed:"  << _q.lastError() << "\n";// if not succesfull print error
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
        while(1){
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
            qDebug() << "4. Buy something from the shop";
            qDebug() << "5. Save & Exit";

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
                }else if(currentHero->inventory.empty()) {
                    qDebug() << "\nYou have no weapon/magic to fight with! Please go to the shop & buy something to try again.";
                }else{
                    selectDungeon(); // fight enemy
                }
                break;

            case 4:
                std::system("clear"); // clear terminal

                if(!currentHero){ // check for a hero
                    qDebug() << "\nYou have no hero equipped to buy magic! Please load a hero & try again.";
                }else{
                    shop(); // fight enemy
                }
                break;

            case 5:
                qDebug() << "\nExiting...\n";
                save(); // save before exiting
                return; // exit

            default:
                qDebug() << "\nInvalid choice! Please try again.";
            }
        }
    }


    void loadHero(){ // load hero into current hero
        start:;
        qDebug() << "\n--- Loading Heros ---" << "";

        if(!_q.exec("SELECT * FROM Heros")){ // execute query and print status
            qDebug()  << "\nLoad Heros failed:"  << _q.lastError() << "\n";
            return ;
        }


        while (_q.next()) { // print all rows from query
            int     id      = _q.value(0).toInt();
            QString name    = _q.value(1).toString();
            int     xp      = _q.value(2).toInt();
            int     level   = _q.value(3).toInt();
            int     gold    = _q.value(4).toInt();
            Hero temp(name, xp, level, id, gold);
            qDebug() << id << ":" << temp.name << "\t"  << "Hp:" << temp.hp << "\t" <<  "Xp:" << temp.xp << "Level:" << temp.level << "Gold:" << temp.gold;
            qDebug() << "\tInventory:";
            temp.printInventory();
            qDebug()<< " ";
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
            return;
        }

        qDebug()  << "\nHero loaded succesfully";

        // load hero data from database
        int     id      = _q.value(0).toInt();
        QString name    = _q.value(1).toString();
        int     xp      = _q.value(2).toInt();
        int     level   = _q.value(3).toInt();
        int     gold    = _q.value(4).toInt();
        currentHero = std::make_shared<Hero>(Hero(name, xp, level, id, gold)); // throw hero on the heap and point to him
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

        start:;
        qDebug() << "\n--- Loading Dungeons ---" << "";

        if(!_q.exec("SELECT * FROM Dungeons")){
            qDebug()  << "\nLoad Dungeons failed:"  << _q.lastError() << "\n";
            return ;
        }


        while (_q.next()) { // print all dungeons from query
            qDebug() << "\n" << _q.value(0).toInt() << ":" << _q.value(1).toString() << "Gold:" << _q.value(2).toInt() << "\n\tEnemies:";

            // select all enemies in the dungeon
            temp_q.prepare("SELECT * FROM Enemies INNER JOIN Enemy_list ON Enemies.id = Enemy_list.enemy_id INNER JOIN Element on Enemies.element_id = Element.id WHERE Enemy_list.dungeon_id = ?;");
            temp_q.addBindValue(_q.value(0).toInt());

            if(!temp_q.exec()){
                qDebug()  << "\nLoad Enemies failed:"  << _q.lastError() << "\n";
                return ;
            }

            while (temp_q.next()) { // print all enemies from query
                QString name    = temp_q.value(1).toString();
                int     hp      = temp_q.value(2).toInt();
                int     damage  = temp_q.value(3).toInt();
                int     xp      = temp_q.value(4).toInt();
                QString element = temp_q.value(10).toString();
                qDebug() << "\t" << name << "\t"  << "Hp:" << hp << "\t" << "Damage:" << damage << "\t" <<  "Xp:" << xp << "\t" << "Element:" << element;
            }
            qDebug() << "--------------------------------------------------------------------------------------";
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

        if(!_q.next()){ // next() to select one dungeon in case none exist
            qDebug()  << "\nNo Dungeon at that index. Press enter to try again";

            // wait for a enter keypress
            QTextStream in(stdin);
            forever {
                QString line = in.readLine();
                if (!line.isNull())
                    break;
            }

            std::system("clear"); // clear terminal when menu is opened
            goto start;
        }

        // select all enemies in dungeon
        temp_q.prepare("SELECT * FROM Enemies INNER JOIN Enemy_list ON Enemies.id = Enemy_list.enemy_id INNER JOIN Element on Enemies.element_id = Element.id WHERE Enemy_list.dungeon_id = ?;");
        temp_q.addBindValue(_q.value(0).toInt());

        if(!temp_q.exec()){
            qDebug()  << "\nLoad Enemies failed:"  << _q.lastError() << "\n";
            return ;
        }

        while(temp_q.next()){
            // load from database
            QString name       = temp_q.value(1).toString();
            int     hp         = temp_q.value(2).toInt();
            int     strength   = temp_q.value(3).toInt();
            int     xp         = temp_q.value(4).toInt();
            int     element_id = temp_q.value(5).toInt();
            QString element    = temp_q.value(10).toString();

            enemies.push_back(Enemy(name, hp, strength, xp, element_id, element)); // create the enemy
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
                qDebug() << "\nYou feel your health and Mana Restored";
                currentHero->restoreHp();
                currentHero->restoreMana();
            }
        }

        currentHero->gold += dungeon.gold;

        qDebug() << "Your Hero" << currentHero->name << "defeated all enemies in" << dungeon.name << "and gained" << dungeon.gold << "gold";
    }

    void shop(){ // open shop to buy magics
        QSqlQuery temp_q;
        qDebug() << "\n--- Loading Shop ---" << "";

        qDebug() << "\nYour Gold:" << currentHero->gold;

        if(!_q.exec("SELECT * FROM MagicShop "
                    "INNER JOIN Magic ON MagicShop.magic_id = Magic.id  "
                    "INNER JOIN Element ON Magic.element_id = Element.id;")){ // execute query and print status
            qDebug()  << "\nLoad Shop failed:"  << _q.lastError() << "\n";
            return ;
        }

        qDebug() << "\nAvailable Magics:" << "";
        while (_q.next()) { // print all rows from query
            int     id          = _q.value(0).toInt();
            int     price       = _q.value(2).toInt();
            QString name        = _q.value(4).toString();
            int     damage      = _q.value(5).toInt();
            int     selfDamage  = _q.value(6).toInt();
            int     manaCost    = _q.value(7).toInt();
            QString element     = _q.value(10).toString();

            qDebug() << id << ":\t" << name << "\t" << "Price:" << price << "Damage:" << damage << "Self Damage:" << selfDamage << "\t" << "Mana Cost:" << manaCost << "\t" << "Element:" << element;

            // load requirements for current magic
            temp_q.prepare("SELECT * FROM MagicShop "
                           "LEFT JOIN Requirements ON Requirements.magicShop_id = MagicShop.id "
                           "LEFT JOIN Magic ON Requirements.magic_id = Magic.id "
                           "WHERE MagicShop.id = ? ;");
            temp_q.addBindValue(id);
            if(!temp_q.exec()){
                qDebug()  << "\nLoad Requirements failed:"  << _q.lastError() << "\n";
                return ;
            }

            temp_q.first();
            if(temp_q.value(6).toInt() > 0){ // if there is at least on required magic print all
                qDebug() << "\t  Required Magics:";
                do{
                    qDebug() << "\t   " << temp_q.value(7).toString();
                }while(temp_q.next());
            }
            qDebug() << "-----------------------------------------------------------";
        }
        qDebug() << "Enter the index of your choice:";
        QTextStream in(stdin);
        int choice = in.readLine().toInt();

        // prepare query of selecting hero
        _q.prepare("SELECT * FROM MagicShop "
                   "INNER JOIN Magic ON MagicShop.magic_id = Magic.id  "
                   "INNER JOIN Element ON Magic.element_id = Element.id "
                   "WHERE MagicShop.id = ? ;");
        _q.addBindValue(choice);

        if(!_q.exec()){
            qDebug()  << "\nSelect MagicShop failed:" << _q.lastError() << "\n";
            return ;
        }

        if(!_q.next()){ // next to select one hero in case none matches
            qDebug()  << "\nNo magic at that index";
            return;
        }
        int     price       = _q.value(2).toInt();
        int     id          = _q.value(3).toInt();
        QString name        = _q.value(4).toString();
        int     damage      = _q.value(5).toInt();
        int     selfDamage  = _q.value(6).toInt();
        int     manaCost    = _q.value(7).toInt();
        int     element_id  = _q.value(9).toInt();
        QString element     = _q.value(10).toString();

        if(!(currentHero->gold >= price)){
            qDebug()  << "\nYou do not have enough gold for that magic";
            return;
        }

        for(Magic m: currentHero->inventory){
            if(m.id == id){
                qDebug()  << "\nYou alraedy own that magic";
                return;
            }
        }

        // load requirements for current magic
        temp_q.prepare("SELECT * FROM MagicShop "
                       "LEFT JOIN Requirements ON Requirements.magicShop_id = MagicShop.id "
                       "LEFT JOIN Magic ON Requirements.magic_id = Magic.id "
                       "WHERE MagicShop.id = ? ;");
        temp_q.addBindValue(id);
        if(!temp_q.exec()){
            qDebug()  << "\nLoad Requirements failed:"  << _q.lastError() << "\n";
            return ;
        }

        temp_q.first();
        if(temp_q.value(6).toInt() > 0){ // if there is at least on required magic print all
            do{
                int magicExistInInventory = 0;
                for(Magic m:currentHero->inventory){
                    if(temp_q.value(6).toInt() == m.id){
                        magicExistInInventory++;
                    }
                }
                if(!(magicExistInInventory > 0)){
                    qDebug()  << "\nYou do not own the required magic" << temp_q.value(7).toString();
                    return;
                }
            }while(temp_q.next());
        }



        // remove gold from current hero
        currentHero->gold -= price;

        // add magic to current hero invetory
        currentHero->inventory.push_back(Magic(id, name, damage, selfDamage, manaCost, element_id, element));

        qDebug()  << "\nYou have purchased"<< name << "\n\nThank you for your purchase!";
    }

    void save(){ // save current hero to database
        _q.clear(); // clear query to make space for prepare

        _q.prepare("SELECT * FROM Heros WHERE id = ? ;");
        _q.addBindValue(currentHero->id);

        if(!_q.exec()){
            qDebug()  << "\nSave Check Hero failed:"  << _q.lastError() << "\n";
        }

        if(_q.next()){
            _q.clear(); // clear query to make space for prepare
            // if they exist update hero
            _q.prepare("UPDATE Heros SET xp = ?, level = ?, gold = ? WHERE id = ?;");
            _q.addBindValue(currentHero->xp);
            _q.addBindValue(currentHero->level);
            _q.addBindValue(currentHero->gold);
            _q.addBindValue(currentHero->id);

            if(!_q.exec()){
                qDebug()  << "\nSave Update Hero failed:"  << _q.lastError() << "\n";
            }

            // delete old inventory
            _q.prepare("DELETE FROM Inventory WHERE hero_id = ?;");
            _q.addBindValue(currentHero->id);

            if(!_q.exec()){
                qDebug()  << "\nSave Delete Inventory failed:"  << _q.lastError() << "\n";
            }

            for(Magic m:currentHero->inventory){ // save all items in currentHero inventory into database
                _q.prepare("INSERT INTO Inventory (hero_id, magic_id) "
                           "VALUES (?, ?);");
                _q.addBindValue(currentHero->id);
                _q.addBindValue(m.id);

                if(!_q.exec()){
                    qDebug()  << "\nSave Update Inventory failed:"  << _q.lastError() << "\n";
                }
            }

        }else{
            // if they dont exist insert into table
            _q.prepare("INSERT INTO Heros (name, xp, level, gold) "
                       "VALUES (?, ?, ?, ?);");
            _q.addBindValue(currentHero->name);
            _q.addBindValue(currentHero->xp);
            _q.addBindValue(currentHero->level);
            _q.addBindValue(currentHero->gold);

            if(!_q.exec()){
                qDebug()  << "\nSave Insert Hero failed:"  << _q.lastError() << "\n";
            }

            // get id of the resently saved hero
            _q.exec("SELECT * FROM Heros;");
            _q.last();
            int id = _q.value(0).toInt();

            for(Magic m:currentHero->inventory){ // save all items in currentHero inventory into database
                _q.prepare("INSERT INTO Inventory (hero_id, magic_id) "
                           "VALUES (?, ?);");
                _q.addBindValue(id);
                _q.addBindValue(m.id);

                if(!_q.exec()){
                    qDebug()  << "\nSave Insert Inventory failed:"  << _q.lastError() << "\n";
                }
            }
        }

        // remove hero from memory
        currentHero.reset();
    }
};
