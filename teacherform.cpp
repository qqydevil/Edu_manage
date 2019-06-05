#include "teacherform.h"
#include "ui_teacherform.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QFileDialog>
#include <QTextStream>

teacherform::teacherform(QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacherform)
{
    ui->setupUi(this);
    Name = name ;
    scoreInfoModel = new QSqlTableModel ;
    scoreInfoModel->setTable("Score");
    scoreInfoModel->setEditStrategy(QSqlTableModel::OnManualSubmit); //修改提交过之后更新到数据库
    scoreInfoModel->select();
    //获取当前列 的索引
    scoreInfoModel->setHeaderData(0,Qt::Horizontal,tr("ID"));
    scoreInfoModel->setHeaderData(1,Qt::Horizontal,tr("学生学号"));
    scoreInfoModel->setHeaderData(2,Qt::Horizontal,tr("类型"));
    scoreInfoModel->setHeaderData(3,Qt::Horizontal,tr("成绩"));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//使其不可编辑
    ui->tableView->setModel(scoreInfoModel);
    ui->tabWidget->setCurrentIndex(0);

    QObject::connect(ui->addButton,SIGNAL(clicked()),this,SLOT(addButton_onclick()));
    QObject::connect(ui->deleteButton,SIGNAL(clicked()),this,SLOT(deleteButton_onclick()));
    QObject::connect(ui->refreshButton,SIGNAL(clicked()),this,SLOT(refreshButton_onclick()));
    QObject::connect(ui->exitButton,SIGNAL(clicked()),this,SLOT(exitButton_onclick()));
    QObject::connect(ui->searchButton,SIGNAL(clicked()),this,SLOT(searchButton_onclick()));
    QObject::connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(saveButton_onclick()));
    QObject::connect(ui->cancleButton,SIGNAL(clicked()),this,SLOT(cancleButton_onclick()));
   // QObject::connect(ui->listView,SIGNAL(clicked()),this,SLOT(listview_onclick(QModelIndex)));
}

teacherform::~teacherform()
{
    delete ui;
}

void teacherform::cancleButton_onclick()      //取消功能函数
{
   this->close() ;
}


void teacherform::saveButton_onclick()        //保存功能函数
{
   if(ui->oldEdit->text() == "" ||ui->newEdit->text() =="" || ui->confireEdit->text() == "")
   {
       QMessageBox::about(this,"Message","item with * can't not be empty!") ;
       return ;
   }

   if(ui->newEdit->text() != ui->confireEdit->text())
   {
       QMessageBox::about(this,"Message",tr("新密码和确认密码不一致！"));
       return ;
   }

   QSqlQuery query ;

   query.exec("update Teacher set Password = '"+ui->newEdit->text()+"' WHERE Name = '"+Name+"'") ;
   if(query.isActive())
   {
       query.numRowsAffected();
       QMessageBox::about(this,"message",tr("修改密码成功！"));
   }

}


void teacherform::searchButton_onclick()      //搜索功能函数
{
   scoreInfoModel->setFilter("StdNum = "+ui->numberEdit->text());   //从数据库中找出对应学生编号的信息
   scoreInfoModel->select() ;
}


void teacherform::listview_onclick(QModelIndex index)   //视图功能函数
{
    QString qstrTitle=index.data().toString();         //获取点击的对应行数据内容
    QString qstrSub=ui->typecomboBox->currentText();   //获取科目类型

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select Content from question where Title ='"+qstrTitle+"' and sub='"+qstrSub+"'");
    ui->listView_2->setModel(model);
}


void teacherform::exitButton_onclick()        //退出功能函数
{
    this->close() ;
}


void teacherform::refreshButton_onclick()     //刷新功能函数
{
    QString qstrSub=ui->typecomboBox->currentText();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select Title from question where sub ='"+qstrSub+"'");
    ui->listView->setModel(model);
}


void teacherform::deleteButton_onclick()      //删除功能函数
{
    QString qstrTitle = ui->listView->currentIndex().data().toString() ;
    QSqlQuery query ;
    query.exec("delete from question where Title = '"+qstrTitle+"'") ;  //删除表格中对应数据
    if(query.isActive())
    {
        query.numRowsAffected() ;
        QMessageBox::about(this,"message",tr("删除成功！")) ;
    }
    refreshButton_onclick();
}


void teacherform::addButton_onclick()         //添加功能函数
{
    QString qstrSub =ui->typecomboBox->currentText() ;
    QString qstrAnswer = ui->answercomboBox->currentText() ;
    int nId ;
    int nMaxid ;
    QString filename = QFileDialog::getOpenFileName() ;
    if(filename.isEmpty())
    {
        return ;
    }
    QFile file(filename) ;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"error",tr("操作文件失败！")) ;
        return ;
    }
    QTextStream in(&file) ;
    QString temp = in.readAll() ;
    QSqlQuery query ;
    query.exec("select max(ID) from question") ;
    if(query.next())
    {
        nMaxid = query.value(0).toInt() ;
    }
    nId = nMaxid+1 ;
    query.exec("insert into question values('"+QString::number(nId)+"','"+qstrSub+"','"+filename+"','"+temp+"','"+qstrAnswer+"')");

    refreshButton_onclick();

}


