#include <QCoreApplication>
#include <QtSql>

#include "robot.h"

robot::robot(QString name): _name(name){
}

int robot::doTask(){

    QSqlQuery query; 

    query.exec("SELECT * FROM task"); // Get current task

    query.first();
    int     task_id = query.value(0).toInt();
    QString description  = query.value(1).toString();

    // Give current task to robot
    query.prepare("UPDATE robots SET current_task = ? WHERE robot_id = ?;");

    query.addBindValue(task_id);
    query.addBindValue(_robot_id);

    if(!query.exec()){ // Add task to robot in robots table
        qDebug()  << query.lastError();
        return 0;
    }

    qDebug() << "Robot:" << _name << "Doing task:" << description;

    removeTask(task_id); // Delete current task from task table

    return 1;
}

int robot::removeTask(int task_id){
    QSqlQuery query;

    query.prepare("DELETE FROM task WHERE task_id = ?");
    query.addBindValue(task_id);

    if(!query.exec()){ // Delete task from task table and print status
        qDebug()  << "Do Task Query fail" << query.lastError() << "\n";
        return 0;
    }

    qDebug()  << "\n";
    return 1;
}

int robot::initiateRobots(){
    QSqlQuery query;

    if(!query.exec("DROP TABLE robots;")){ // Clean up old table
        qDebug()  << query.lastError();
        return 0;
    }

    // Initiate table task
    if(!query.exec("CREATE TABLE robots (robot_id int NOT NULL AUTO_INCREMENT, name char(125), current_task int, PRIMARY KEY (robot_id));")){
        qDebug() << "Init Query fail:" << query.lastError();
        return 0;
    }

    query.prepare("INSERT INTO robots (name) "
                  "VALUES (?);");

    query.addBindValue(_name);

    if(!query.exec()){ // Add robot to robots table
        qDebug()  << query.lastError();
        return 0;
    }

    // Get robot_id from table
    query.exec("SELECT * FROM robots;");
    query.last();
    _robot_id = query.value(0).toInt();

    return 1;
}

robot::~robot(){
    QSqlQuery query;

    // Remove robot from table
    query.prepare("DELETE FROM robots WHERE robot_id = ?;");
    query.addBindValue(_robot_id);
    if(!query.exec()){
        qDebug()  << query.lastError();
    }
}

int robot::printRobots(){
    QSqlQuery query;

    if(!query.exec("SELECT * FROM robots")){ // Execute query and print status
        qDebug()  << "Show Robots Query fail:" << query.lastError() << "\n";
        return 0;
    }

    qDebug() << "Name:" << "\t\t" << "Current Task:";

    while (query.next()) { // Print all rows from query
        QString name  = query.value(1).toString();
        int     current_task = query.value(2).toInt();
        qDebug()  << name << "\t\t" << current_task;
        }

    qDebug()  << "\n";
    return 1;
}
