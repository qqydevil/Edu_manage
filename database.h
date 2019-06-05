#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QMessageBox>


static bool createConnection()   //数据库连接
{
    //QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QSqlDatabase db(QSqlDatabase::addDatabase("QMYSQL"));
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("132097");
    db.setDatabaseName("exam");
    if (!db.open())
    {
        QMessageBox::warning(0, QObject::tr("Database Error"),db.lastError().text());   //打开数据库失败
        return false;
    }
    return true;
}

#endif // DATABASE_H
