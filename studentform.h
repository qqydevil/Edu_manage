#ifndef STUDENTFORM_H
#define STUDENTFORM_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class studentform;
}

class studentform : public QWidget
{
    Q_OBJECT

public:
    explicit studentform(QWidget *parent = 0);
    studentform(QString name,QWidget *parent = 0) ;
    ~studentform();

private:
    Ui::studentform *ui;
    QString stdName ;        //学生名字
    QTimer * timer ;
    int QuestionId[20] ;
    QString answer[20] ;
    int questionNum ;
    int currentNum ;
    int currentTime ;
    int score ;

private slots:
    void nextButton_onclick();         //下一题按钮槽函数
    void previousButton_onclick();     //前一题按钮槽函数
    void submitButton_onclick();       //提交按钮槽函数
    void startButton_onclick();        //开始按钮槽函数
    void saveButton_onclick();         //保存按钮槽函数
    void cancleButton_onclick();       //取消按钮槽函数
    void timerUpDate();                //显示时间

};


#endif // STUDENTFORM_H
