#ifndef ADDSTDFORM_H
#define ADDSTDFORM_H

#include <QWidget>

namespace Ui {
class addstdform;
}

class addstdform : public QWidget
{
    Q_OBJECT

public:
    explicit addstdform(QWidget *parent = 0);
    ~addstdform();

private:
    Ui::addstdform *ui;

private slots:
    void submitButton_onclick() ;    //提交按钮槽函数
    void cancleButton_onclick() ;    //取消按钮槽函数   
};

#endif // ADDSTDFORM_H
