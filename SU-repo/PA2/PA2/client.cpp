#include <QCoreApplication>
#include <QtSql>

#include "client.h"

client::client(){
    initiateTasks();
}

int client::printTask(){
    QSqlQuery query;

    if(!query.exec("SELECT * FROM task")){ // Execute query and print status
        qDebug()  << "Show Tasks Query fail:" << query.lastError() << "\n";
        return 0;
    }

    qDebug() << "Desciption:" << "\t\t" << "Time:";

    while (query.next()) { // Print all rows from query
        QString description  = query.value(1).toString();
        int     time = query.value(2).toInt();
        qDebug()  << description << "\t\t" << time;
        }

    qDebug()  << "\n";
    return 1;
}

int client::addTask(){
    QSqlQuery query;

    qDebug() << "Add task:" << "\nEnter description:";
    QTextStream qtin1(stdin);
    QString description = qtin1.readLine();

    qDebug() << "Enter time:";
    QTextStream qtin2(stdin);
    int time = qtin2.readLine().toInt();

    // Prepare query of inserting task
    query.prepare("INSERT INTO task (description, time) "
                  "VALUES( ? , ?)");

    query.addBindValue(description);
    query.addBindValue(time);

    if(query.exec()){ // Execute query and print status
        qDebug()  << "Query success";
    }else{
        qDebug()  << "Query fail:" << query.lastError() << "\n";
        return 0;
    }

    qDebug()  << "\n";
    return 1;
}

int client::initiateTasks(){
    QSqlQuery query;


    if(!query.exec("drop table task;")){ // Clean up old table
        qDebug() << query.lastError();
        return 0;
    }

    // Initiate table task
    if(!query.exec("create table task (task_id int not null AUTO_INCREMENT, description char(125), time int not null, primary key (task_id));")){
        qDebug() << query.lastError();
        return 0;
    }

    // Fill table
    query.prepare("INSERT INTO task (description, time) "
               "VALUES (? , ?);");

    QVariantList descriptions, times;
    descriptions << "Get garbage" << "Clean stairs" << "Debug the code";
    query.addBindValue(descriptions);

    times << 10 << 30 << 20;
    query.addBindValue(times);

    if(!query.execBatch()){ // Execute query
        qDebug()  << "Init Query fail:" << query.lastError();
        return 0;
    }

    return 1;
}
