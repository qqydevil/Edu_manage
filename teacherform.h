#ifndef TEACHERFORM_H
#define TEACHERFORM_H

#include <QWidget>
#include <QModelIndex>
#include <QSqlTableModel>


namespace Ui {
class teacherform;
}

class teacherform : public QWidget
{
    Q_OBJECT

public:
    explicit teacherform(QWidget *parent = 0);
    teacherform(QString name ,QWidget *parent = 0) ;
    ~teacherform();

private:
    Ui::teacherform *ui;
    QSqlTableModel *scoreInfoModel ;    //获取教师信息
    QString Name ;

private slots:
    void cancleButton_onclick();                  //取消按钮槽函数
    void saveButton_onclick();                    //保存按钮槽函数
    void searchButton_onclick();                  //搜索按钮槽函数
    void listview_onclick(QModelIndex index);     //视图按钮槽函数
    void exitButton_onclick();                    //退出按钮槽函数
    void refreshButton_onclick();                 //刷新按钮槽函数
    void deleteButton_onclick();                  //删除按钮槽函数
    void addButton_onclick();                     //添加按钮槽函数
};

#endif // TEACHERFORM_H
