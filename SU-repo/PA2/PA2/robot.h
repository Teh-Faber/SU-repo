#pragma once
#include <QCoreApplication>
#include <QtSql>


class robot{

    QString _name;
    int _robot_id;

public:

    robot(QString name);

    int initiateRobots();

    int doTask();

    int removeTask(int task_id);

    int printRobots();

    ~robot();
};




