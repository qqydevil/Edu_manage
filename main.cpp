#include "mainwindow.h"
#include <QApplication>
#include "database.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection())  //判断是否连接成功
    {
        qWarning("Database Error");
        return 0;
    }

    //显示登陆界面
    MainWindow w;
    w.show();

    return a.exec();
}
