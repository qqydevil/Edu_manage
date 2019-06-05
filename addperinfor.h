#ifndef ADDPERINFOR_H
#define ADDPERINFOR_H

#include <QWidget>
#include <QSqlTableModel>
#include "addthform.h"
#include "addstdform.h"

namespace Ui {
class addperinfor;
}

class addperinfor : public QWidget
{
    Q_OBJECT

public:
    explicit addperinfor(QWidget *parent = 0);
    ~addperinfor();

private:
    Ui::addperinfor *ui;
    QSqlTableModel *teacherInfoModel;     //获取教师信息
    QSqlTableModel *StudentInfoModel;     //获取学生信息

private slots:
    void addButtonT_onclick() ;       //添加老师信息
    void deleteButtonT_onclick() ;    //删除老师信息
    void refreshButtonT_onclick() ;   //更新老师信息表
    void addButtonS_onclick() ;       //添加学生信息
    void deleteButtonS_onclick() ;    //删除学生信息
    void refreshButtonS_onclick() ;   //更新学生信息表

public:
    void search() ;   //检索

};

#endif // ADDPERINFOR_H
