#include "addperinfor.h"
#include "ui_addperinfor.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

addperinfor::addperinfor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addperinfor)
{
    ui->setupUi(this);
    //教师管理
    teacherInfoModel = new QSqlTableModel(this) ;
    teacherInfoModel->setTable("Teacher");
    teacherInfoModel->setEditStrategy(QSqlTableModel::OnManualSubmit) ;  //设置保存策略为手动提交
    teacherInfoModel->select() ;          //在筛选和排序的条件下，将数据库中符合要求的在mode表格中显示出来

    //获取当前列的索引
    teacherInfoModel->setHeaderData(0,Qt::Horizontal,tr("ID")) ;      //设置水平头或垂直头标题
    teacherInfoModel->setHeaderData(1,Qt::Horizontal,tr("教师编号")) ;
    teacherInfoModel->setHeaderData(2,Qt::Horizontal,tr("用户名")) ;
    teacherInfoModel->setHeaderData(3,Qt::Horizontal,tr("用户密码")) ;
    ui->tvTeacher->setEditTriggers(QAbstractItemView::NoEditTriggers);  //使视图不可以被编辑
    ui->tvTeacher->setModel(teacherInfoModel);

    //学生管理
    StudentInfoModel = new QSqlTableModel(this) ;
    StudentInfoModel->setTable("Student");
    StudentInfoModel->setEditStrategy(QSqlTableModel::OnManualSubmit) ;  //设置保存策略为手动提交
    StudentInfoModel->select() ;

    //获取当前列的索引
    StudentInfoModel->setHeaderData(0,Qt::Horizontal,tr("ID")) ;
    StudentInfoModel->setHeaderData(1,Qt::Horizontal,tr("学生编号")) ;
    StudentInfoModel->setHeaderData(2,Qt::Horizontal,tr("用户名")) ;
    StudentInfoModel->setHeaderData(3,Qt::Horizontal,tr("用户密码")) ;
    ui->tvStudent->setEditTriggers(QAbstractItemView::NoEditTriggers);  //使视图不可以被编辑
    ui->tvStudent->setModel(StudentInfoModel);

    ui->tabWidget->setCurrentIndex(0);

    QObject::connect(ui->addButton1,SIGNAL(clicked()),this,SLOT(addButtonT_onclick()));
    QObject::connect(ui->deleteButton1,SIGNAL(clicked()),this,SLOT(deleteButtonT_onclick()));
    QObject::connect(ui->refreshButton1,SIGNAL(clicked()),this,SLOT(refreshButtonT_onclick()));
    QObject::connect(ui->addButton2,SIGNAL(clicked()),this,SLOT(addButtonS_onclick()));
    QObject::connect(ui->deleteButton2,SIGNAL(clicked()),this,SLOT(deleteButtonS_onclick()));
    QObject::connect(ui->refreshButton2,SIGNAL(clicked()),this,SLOT(refreshButtonS_onclick()));


}


addperinfor::~addperinfor()
{
    delete ui;
}


void addperinfor::search()   //检索功能
{
    teacherInfoModel->select() ;
    StudentInfoModel->select() ;
}


void addperinfor::addButtonT_onclick()      //添加教师信息槽函数
{
    addthform *pAddthform = new addthform;
    pAddthform->show();
}


void addperinfor::deleteButtonT_onclick()   //删除教师信息槽函数
{

    QString qstrID = ui->tvTeacher->currentIndex().data().toString() ;
    qDebug()<<qstrID ;

    QSqlQuery query ;
    query.exec("delete from Teacher where ID = '"+qstrID+"'");
    if(query.isActive())   //判断是否执行，为活动状态
    {
        query.numRowsAffected() ;
        QMessageBox::about(this,"message",tr("删除成功！")) ;
    }

    search() ;

}


void addperinfor::refreshButtonT_onclick()  //刷新教师信息槽函数
{
    search() ;
}


void addperinfor::addButtonS_onclick()      //添加学生信息槽函数
{
    addstdform *pAddstdform = new addstdform;
    pAddstdform->show();
}


void addperinfor::deleteButtonS_onclick()   //删除学生信息槽函数
{
    QString qstrID = ui->tvStudent->currentIndex().data().toString() ;
    qDebug()<<qstrID ;

    QSqlQuery query ;
    query.exec("delete from Student where ID = '"+qstrID+"'");
    if(query.isActive())   //判断是否执行，为活动状态
    {
        query.numRowsAffected() ;
        //QMessageBox::about(this,"message","Delete success") ;
    }

    search() ;
}


void addperinfor::refreshButtonS_onclick()  //刷新学生信息槽函数
{
    search();
}



