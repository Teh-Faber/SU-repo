#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>

#include "client.h"
#include "robot.h"


int main()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("company"); // Ret til det schema navn du har valgt
    db.setUserName("root");  // Ret brugernavn
    db.setPassword("password");  // Ret password
    db.open();

    client client;
    robot robot("R2D2");

    client.printTask();

    robot.doTask();

    robot.doTask();

    robot.printRobots();

    client.printTask();

    return 0;
}
