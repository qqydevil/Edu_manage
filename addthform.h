#ifndef ADDTHFORM_H
#define ADDTHFORM_H

#include <QWidget>

namespace Ui {
class addthform;
}

class addthform : public QWidget
{
    Q_OBJECT

public:
    explicit addthform(QWidget *parent = 0);
    ~addthform();

private:
    Ui::addthform *ui;

private slots:
    void submitButton_onclick() ;    //提交按钮槽函数
    void cancleButton_onclick() ;    //取消按钮槽函数
};

#endif // ADDTHFORM_H
