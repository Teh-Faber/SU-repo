#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("robot_worker");
    db.setUserName("root");  // Change to username
    db.setPassword("password");  // Change to password
    db.open();
    
    QSqlQuery query;
    
    qDebug() << query.exec("SELECT * FROM task"); // employee er her navnet på en tabel, ikke et schema


    while (query.next()) {
        QString desciption  = query.value(1).toString();
        int     time = query.value(2).toInt();
        qDebug() << "Desciption:" << desciption << "Time:" << time;
        }
    
    qDebug() << "Number of rows:" << query.size(); 
    
    qDebug() << "Finished";
    return 1;
}


