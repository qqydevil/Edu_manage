#include "addstdform.h"
#include "ui_addstdform.h"
#include <QMessageBox>
#include <QSqlQuery>

addstdform::addstdform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addstdform)
{
    ui->setupUi(this);
    QObject::connect(ui->submitButton,SIGNAL(clicked()),this,SLOT(submitButton_onclick()));
    QObject::connect(ui->cancleButton,SIGNAL(clicked()),this,SLOT(cancleButton_onclick()));
}

addstdform::~addstdform()
{
    delete ui;
}


void addstdform::submitButton_onclick()   //提交功能槽函数
{
     //当输入有为空时
     if(ui->IDEdit->text() == "" ||ui->NameEdit->text() == ""||ui->NumEdit->text() == ""||ui->PasswordEdit->text()=="")
     {
         QMessageBox::about(this,"Message","item with * can't not be empty!") ;
         return ;
     }

     QSqlQuery query ;
     query.exec("select count(*) from Student where ID = '"+ui->IDEdit->text()+"'") ;
     int nID = 0 ;
     if(query.next())   //找到匹配的ID
     {
         nID = query.value(0).toInt() ;
     }

     if(nID != 0)       //该ID已存在
     {
         QMessageBox::about(this,"Message","this ID has existed !") ;
         QString qstrMaxNum ;
         query.exec("select  ID from Student order by ID desc");  //找到最后一个id
         if(query.next())
         {
             qstrMaxNum = query.value(0).toString();
         }
         QMessageBox::about(this,"Message","max ID="+qstrMaxNum);
         return ;
     }

     query.exec("select * from Student where Name='"+ui->NameEdit->text()+"'");
     if(query.next())   //该用户名已存在
     {
         QMessageBox::about(this,"Message",tr("该用户已经存在！"));
         return ;
     }

     query.exec("insert into Student values('"+ui->IDEdit->text()+"','"+ui->NumEdit->text()+"','"+ui->NameEdit->text()+"','"+ui->PasswordEdit->text()+"')");
     if(query.isActive())  //有活动，受到影响
     {
            query.numRowsAffected();
            QMessageBox::about(this,"Message","Add success !");
            this->close() ;
     }
}

void addstdform::cancleButton_onclick()   //取消功能槽函数
{
    this->close() ;
}

