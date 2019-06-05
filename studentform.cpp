#include "studentform.h"
#include "ui_studentform.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <qdatetime.h>
#include <stdlib.h>
#include <time.h>

studentform::studentform(QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentform)
{
    ui->setupUi(this);
   // ui->tabWidget->currentIndex(0) ;   //设置标题1
    stdName = name ;
    QString stdNum;
    QString stdname;
    QString password;
    QString sub;
    QString score1;
    QSqlQuery query;
    query.exec("select * from Student where Name= '"+stdName+"'");
    while(query.next())     //在textedit中添加学生的个人信息
    {
        stdNum = query.value(1).toString();
        stdname = query.value(2).toString();
        password = query.value(3).toString();
        ui->textEdit->append(tr("学号：")+stdNum);
        ui->textEdit->append(tr("用户名：")+stdname);
        ui->textEdit->append(tr("密码：")+password);
    }

    query.exec("select * from Score where StdNum= '"+stdNum+"'");   //根据编号搜索该学生的得分表
    while(query.next())     //在textedit中添加学生的科目和成绩
    {
        sub = query.value(2).toString();
        score1 = query.value(3).toString();
        ui->textEdit->append(tr("科目：")+sub+tr("  成绩：")+score1);
    }

    score = 0;     //初始化
    currentNum = 0;
    questionNum = 20;
    currentTime = 0;
    for(int i =0;i<20;i++)
    {
        answer[i] = "";
        QuestionId[i]=0;
    }

    ui->previousButton->setEnabled(false);     //按钮设为无效
    ui->nextButton->setEnabled(false);
    ui->submitButton->setEnabled(false);

    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    QObject::connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(saveButton_onclick()));
    QObject::connect(ui->cancleButton,SIGNAL(clicked()),this,SLOT(cancleButton_onclick()));
    QObject::connect(ui->previousButton,SIGNAL(clicked()),this,SLOT(previousButton_onclick()));
    QObject::connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(nextButton_onclick()));
    QObject::connect(ui->submitButton,SIGNAL(clicked()),this,SLOT(submitButton_onclick()));
    QObject::connect(ui->startButton,SIGNAL(clicked()),this,SLOT(startButton_onclick()));


}

studentform::~studentform()
{
    delete ui;
}


void studentform::nextButton_onclick()       //下一题功能按钮
{
    if(currentNum>=questionNum)
    {
        QMessageBox::warning(this,tr("Warning"),tr("这已经是最后一道题了！"));
        return;
    }

    if(ui->radioA->isChecked())   //将学生答案放入回答数组中
    {
        answer[currentNum-1] = "A";
    }
    else if(ui->radioB->isChecked())
    {
        answer[currentNum-1] = "B";
    }
    else if(ui->radioC->isChecked())
    {
        answer[currentNum-1] = "C";
    }
    else
    {
        answer[currentNum-1] = "D";
    }


    ui->textEdit_2->clear();
    currentNum = currentNum+1;
    ui->numberEdit->setText(QString::number(currentNum));
    QSqlQuery query;
    query.exec("select * from Question where ID='"+QString::number(QuestionId[currentNum-1])+"'");
    if(query.next())
    {
        ui->textEdit_2->append(query.value(3).toString());
        if(query.value(4).toString()==answer[currentNum-2])   //对上一题学生的作答检查
        {
           score = score +5;
        }
    }

    ui->correct_answerEdit->setText("");   //将回答答案置空
    ui->youranswerEdit->setText("");

}


void studentform::previousButton_onclick()   //前一题功能按钮
{
    if(currentNum<=1)
    {
        QMessageBox::warning(this,tr("Warning"),tr("这是第一道题！"));
        return;
    }
    ui->textEdit_2->clear();      //将textedit上的内容清空
    currentNum = currentNum-1;    //设置为上一题的序号
    ui->numberEdit->setText(QString::number(currentNum));   //显示序号

    QSqlQuery query;
    query.exec("select * from Question where ID='"+QString::number(QuestionId[currentNum-1])+"'");   //从随机数组中找到对应序号的序号
    if(query.next())
    {
        ui->textEdit_2->append(query.value(3).toString());
        ui->correct_answerEdit->setText(query.value(4).toString());   //将盖提正确答案显示出来
    }
    ui->youranswerEdit->setText(answer[currentNum-1]);    //将学生的答案显示出来
}


void studentform::submitButton_onclick()     //提交功能按钮
{
    int maxID;
    QString qstrTemp;  //学生编号
    timer->stop();    //时间停止
    ui->submitButton->setEnabled(false);
    ui->startButton->setEnabled(true);

    if(ui->radioA->isChecked())   //将学生答案放入回答数组中
    {
        answer[currentNum-1] = "A";
    }
    else if(ui->radioB->isChecked())
    {
        answer[currentNum-1] = "B";
    }
    else if(ui->radioC->isChecked())
    {
        answer[currentNum-1] = "C";
    }
    else
    {
        answer[currentNum-1] = "D";
    }

    QSqlQuery query;
    query.exec("select * from Question where ID='"+QString::number(QuestionId[currentNum-1])+"'");
    if(query.next())
    {
        if(query.value(4).toString()==answer[currentNum-2])
        {
            score = score +5;
        }

    }

    query.exec("select StuNum from Student where Name='"+stdName+"'");
    if(query.next())
    {
        qstrTemp = query.value(0).toString();   //获取该学生的编号
    }

    query.exec("select count(*) from Score ");
    if(query.next())
    {
        maxID= query.value(0).toInt();    //获取目前Score表中最大的id号
    }

    query.exec("insert into Score values('"+QString::number(maxID+1)+"','"+qstrTemp+"','"+ui->comboBox->currentText()+"','"+QString::number(score)+"')");
    ui->scoreEdit->setText(QString::number(score));
}


void studentform::startButton_onclick()      //开始功能按钮
{
     int num ;
     timer->start(1000) ;
     ui->previousButton->setEnabled(true);
     ui->nextButton->setEnabled(true);
     ui->submitButton->setEnabled(true);
     ui->startButton->setEnabled(false);
     QSqlQuery query;
     query.exec("select count(*) from Question");
     if(query.next())
     {
         num = query.value(0).toInt();
     }

     if(num>20)
     {
         srand((int)time(NULL));
         for(int i=0;i<20;i++)
         {
             QuestionId[i]=rand()%num;
         }
     }
     else
     {
         for(int i=0;i<num;i++)
         {
             QuestionId[i]=i+1;
         }

         questionNum = num;   //获得当前所有的问题数目
     }
     currentNum =1;
     query.exec("select * from Question where ID='"+QString::number(QuestionId[0])+"'");   //找到第一题
     ui->numberEdit->setText(QString::number(currentNum));
     if(query.next())
     {
         ui->textEdit_2->append(query.value(3).toString());     //将第一题的内容显示到textedit上
     }

}


void studentform::saveButton_onclick()       //保存功能按钮
{
    if(ui->oldpassEdit->text() == "" || ui->newpassEdit->text() == "" || ui->newpassEdit2->text() == "")
    {
        QMessageBox::about(this,"Message","Item with * can't not be empty !");
        return ;
    }

    if(ui->newpassEdit->text()!=ui->newpassEdit2->text())
    {
        QMessageBox::about(this,"Message",tr("新密码和确认新密码不统一！"));
        return ;
    }

    QSqlQuery query;
    query.exec("update Student set Password='"+ui->newpassEdit->text()+"' WHERE Name='"+stdName+"'");
    if(query.isActive())
    {
        query.numRowsAffected();
        QMessageBox::about(this,"message",tr("修改密码成功!"));
    }

}


void studentform::cancleButton_onclick()     //取消功能按钮
{
    this->close() ;
}


void studentform::timerUpDate()    //显示时间
{
    currentTime++;
    ui->timeEdit->setText(QString::number(currentTime));
}


