#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Lektion2_company"); // Ret til det schema navn du har valgt
    db.setUserName("root");  // Ret brugernavn
    db.setPassword("password");  // Ret password
    db.open();
    
    QSqlQuery query;
    
    
    query.prepare("INSERT INTO employee "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
        
    query.addBindValue("John");
    query.addBindValue("Doe");
    query.addBindValue(77777777);
    query.addBindValue("1905-01-09");
    query.addBindValue("731 Fondren, Houston TX");
    query.addBindValue("M");
    query.addBindValue(30000);
    query.addBindValue(333445555);
    query.addBindValue(5);
    
    qDebug() << query.exec();
    
    qDebug() << query.exec("SELECT * FROM employee"); // employee er her navnet på en tabel, ikke et schema
    
    qDebug() << "Number of rows:" << query.size(); 
    
    while (query.next()) {
        QString fname  = query.value(0).toString();
        QString lname = query.value(1).toString();
        int ssn = query.value(2).toInt();
        qDebug() << "Fname:" << fname << "Lname:" << lname << "SSN:" << ssn;
        }
    qDebug() << "Finished";
    return 1;
}


