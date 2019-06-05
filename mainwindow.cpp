#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlQuery>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->loginButton,SIGNAL(clicked()),this,SLOT(registButton_onclick())) ;
    QObject::connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(cancelButton_onclick())) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::GiveRemind()
{
    if((qstrUsername == "") || (qstrPassword == ""))  //当输入为空时，给予提示
    {
        QMessageBox::information(this, tr("Warning"), tr("The input cannot be empty !"), QMessageBox::Ok);
        return 0 ;
    }
    else
    {
        return 1 ;
    }
}

void MainWindow::registButton_onclick()    //登录功能槽函数
{
    qstrUsername = ui->user_lineEdit->text() ;
    qstrPassword = ui->password_lineEdit->text() ;
    qstrType = ui->type_comboBox->currentText() ;

    QSqlQuery query ;
    bool bFlag = false ;
    if(qstrType==tr("管理员"))
    {
        query.exec("select * from Usr ");

        while(query.next())
        {

            if((query.value(1).toString()==qstrUsername)&&(query.value(2).toString()==qstrPassword)) //判断是否相等
            {
                bFlag = true;
                addperinfor * pAddperinfor = new addperinfor;
                pAddperinfor->show();
                this->close();
            }
        }
     }
     else if(qstrType==tr("教师"))
     {
         if(GiveRemind() == 0)
         {
             return ;
         }

         query.exec("select * from Teacher");
         while(query.next())
         {
             if((query.value(2).toString()==qstrUsername)&&(query.value(3).toString()==qstrPassword))
             {
                 bFlag = true;
                 teacherform *pTeacherform = new teacherform(qstrUsername);
                 pTeacherform->show();
                 this->close();
             }
         }
      }
      else
      {
          if(GiveRemind() == 0)
          {
              return ;
          }

          query.exec("select * from Student");
          while(query.next())
          {
              if((query.value(2).toString()==qstrUsername)&&(query.value(3).toString()==qstrPassword))
              {
                  bFlag = true;
                  studentform *pStudentform = new studentform(qstrUsername);
                  pStudentform->show();
                  this->close();
              }
          }
      }

      if(!bFlag)  //验证输入是否正确
      {
          QMessageBox::warning(this,tr("Warninng,"),tr("Username or Password is wrong"),QMessageBox::Ok);
      }

}


void MainWindow::cancelButton_onclick()    //退出功能槽函数
{
    this->close();
}
