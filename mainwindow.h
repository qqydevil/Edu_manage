#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addperinfor.h"
#include "studentform.h"
#include "teacherform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QString qstrUsername ;   //用户名字
    QString qstrPassword ;   //密码
    QString qstrType ;       //身份类别
    Ui::MainWindow *ui;

public:
    int GiveRemind() ;      //消息提示

private slots:
    void registButton_onclick() ;  //登录按钮操作
    void cancelButton_onclick() ;  //退出按钮操作

};

#endif // MAINWINDOW_H
