#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <globle.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // connect(ui->LoginButton, SIGNAL(clicked()), this, SLOT(on_LoginButton_clicked()));
   // ui->hide();
   // connect(ui->LoginButton, SIGNAL(clicked()), this, SLOT(show2()));
    ui->Login_password_2->setEchoMode(QLineEdit::Password);
    ui->radioButton_4->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoginButton_2_clicked()
{
   QString username = ui->Login_username_2->text();
   QString password = ui->Login_password_2->text();
   qDebug()<<"用户名："<<username<<"密码:"<<password;
   QSqlDatabase db;
   if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
   else
   db = QSqlDatabase::addDatabase("QMYSQL");;
   db.setHostName("localhost");
   db.setDatabaseName("lanzhou");
   db.setUserName("root");
   db.setPassword("123456");
   if (!db.open())
   qDebug() << "Failed to connect to root mysql";
    else qDebug() << "open";
   if( ui->radioButton_3->isChecked()){
       QSqlQuery query(db);
       db.exec("SET NAMES 'GBK'");
       query.exec("select id,name,permission,password from user");
       bool T1=false;
       while(query.next())
                  {
                      QString user = query.value(1).toString();
                      int pre=query.value(2).toInt();
                      QString pass = query.value(3).toString();
                      qDebug() << user << pass ;
                      if(username.compare(user)==0&&password.compare(pass)==0&&pre==0){
                          password_qj=password;
                          username_qj=username;
                          T1=true;
                          this->hide();
                          m=new Manager;
                      //    emit sendData(username+"&"+password);
                          m->show();
                      }


                 }


       if(T1==false)
        QMessageBox::information(this, "警告", "用户名或密码错误");


    }

   if( ui->radioButton_4->isChecked()){


   QSqlQuery query(db);
   db.exec("SET NAMES 'GBK'");
   query.exec("select id,name,permission,password from user");
   bool T=false;
   while(query.next())
              {
                  QString user = query.value(1).toString();
                  int pre=query.value(2).toInt();
                  QString pass = query.value(3).toString();
                  qDebug() << user <<pre<< pass ;
                  if(username.compare(user)==0&&password.compare(pass)==0&&pre==1){
                      password_qj=password;
                      username_qj=username;
                      T=true;
                      this->hide();
                      u=new User;
                 //     emit sendData(username+"&"+password);
                      u->show();

                  }
              }

   if(T==false)
    QMessageBox::information(this, "警告", "用户名或密码错误");


   }



}





void MainWindow::on_remitButton_2_clicked()
{
    ui->Login_username_2->clear();
    ui->Login_password_2->clear();
}
