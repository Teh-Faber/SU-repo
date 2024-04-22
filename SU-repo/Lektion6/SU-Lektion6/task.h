#pragma once
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include<unistd.h> // for sleep on unix


int taskPrint(){
    QSqlQuery query;

    if(query.exec("SELECT * FROM task")){ // execute query and print status
        qDebug()  << "Show Tasks: Query success";
    }else{
        qDebug()  << "Show Tasks: Query fail" << query.lastError() << "\n";
    }


    qDebug() << "Desciption:" << "\t\t" << "Time:";

    while (query.next()) { //Print all rows from query
        QString desciption  = query.value(1).toString();
        int     time = query.value(2).toInt();
        qDebug()  << desciption << "\t\t" << time;
        }

    qDebug()  << "\n";
    return 1;
}

int taskAdd(){
    QSqlQuery query;

    qDebug() << "Add task:" << "\nEnter desciption:";
    QTextStream qtin1(stdin);
    QString desciption = qtin1.readLine();

    qDebug() << "Enter time:";
    QTextStream qtin2(stdin);
    int time = qtin2.readLine().toInt();


    query.prepare("INSERT INTO task (description, time) "
                  "VALUES( ? , ?)");

    query.addBindValue(desciption);
    query.addBindValue(time);

    if(query.exec()){ // execute query and print status
        qDebug()  << "Query success";
    }else{
        qDebug()  << "Query fail:" << query.lastError() << "\n";
    }

    qDebug()  << "\n";
    return 1;
}
