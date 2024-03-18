#pragma once
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>

#include<unistd.h> // for sleep on unix


int taskPrint(){
    QSqlQuery query;

    qDebug() << query.exec("SELECT * FROM task"); //task table

    while (query.next()) {
        QString desciption  = query.value(1).toString();
        int     time = query.value(2).toInt();
        qDebug() << "Desciption:" << desciption << "Time:" << time;
        }

    return 1;
}

int taskAdd(){
    QSqlQuery query;

    qDebug() << "Enter desciption:";
    QTextStream qtin1(stdin);
    QString desciption = qtin1.readLine();

    qDebug() << "Enter time:";
    QTextStream qtin2(stdin);
    int time;
    qtin2 >> time;


    query.prepare("INSERT INTO task "
                  "VALUES (?, ?)");

    query.addBindValue(desciption);
    query.addBindValue(time);

    return 1;

}
