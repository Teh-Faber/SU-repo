#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include "task.h"

#include<unistd.h> // for sleep on unix


int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("robot_worker"); // Ret til det schema navn du har valgt
    db.setUserName("root");  // Ret brugernavn
    db.setPassword("password");  // Ret password
    db.open();
  
    QString robot_name = argv[1];
  
   qDebug() << "\n";

    taskPrint();

    taskAdd();

    taskPrint();
    
    return 1;
}
