#include "user.h"
#include "ui_user.h"
#include <QDebug>
#include <QStackedWidget>
#include <globle.h>
#include <QTabWidget>
// SQL 相关
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>


User::User(QWidget *parent) :


    QMainWindow(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);
    qDebug() << ui->stackedWidget->count();

    // 初始化数据库
    if(QSqlDatabase::contains("qt_sql_default_connection"))
         db = QSqlDatabase::database("qt_sql_default_connection");
    else
    db = QSqlDatabase::addDatabase("QMYSQL");;
    db.setHostName("localhost");
    db.setDatabaseName("lanzhou");
    db.setUserName(sqluser);
    db.setPassword(sqlpass);
    if (db.open())
    {
        qDebug() << "打开数据库成功";
        sql = new QSqlQuery(db);
        sql2 = new QSqlQuery(db);
    }
    else
    {
        qDebug() << "打开数据库失败";
    }


    // 表格控件初始化
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);             // 禁用编辑
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自适应
    this->show_table();                                                             //
}

User::~User()
{
    delete ui;
}


void User::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void User::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

int User::get_sql_row()
{
    int row = 0;
    // 获取数据库中的行数b
    QString cmd = "select count(*) from teststep;";
    if (sql->exec(cmd))
    {
        qDebug() << sql;
        while (sql->next()){
            row = sql->value(0).toInt();
        }
    }
    return row;
}

// 获取数据库中的行数
int User::get_sql_row2()
{
    int row = 0;
    // 获取数据库中的行数b
    QString cmd = "select count(*) from testproject where testproject.TesterId = "+userid +";";
    if (sql->exec(cmd))
    {
        qDebug() << sql;
        while (sql->next()){
            row = sql->value(0).toInt();
        }
    }
    return row;
}

void User::show_table(){

    // 设置正确行数
    ui->tableWidget->setRowCount(this->get_sql_row());
    // 获取数据库
    QString cmd = "select * from teststep;";
    if (sql->exec(cmd))
    {
        int row = 0;
        while (sql->next())
        {
            // 获取数据库内容
            QString id = sql->value(0).toString();
            QString name = sql->value(1).toString();
            QString createrbyid = sql->value(2).toString();
            QString testmode = sql->value(3).toString();
            QString steps = sql->value(3).toString();

            // 展示表格内容
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(id));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(name));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(createrbyid));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(testmode));
            row++;
        }
    }
    else
        qDebug() << "数据获取失败" << sql->lastError().text();



    //table2
    ui->tableWidget_2->setRowCount(this->get_sql_row2());
    QString cmd2 = "select * from testproject;";
    if (sql->exec(cmd2))
    {
        int row = 0;
        while (sql->next())
        {
            // 获取数据库内容
            QString id = sql->value(0).toString();
            QString projectname = sql->value(1).toString();
            QString testid = sql->value(2).toString();
            QString c ;
            c= "select * from user where user.id = "+testid+";";
            QString testname ="";
            if(sql2->exec(c)){
                while (sql2->next()){
                    testname=sql2->value(1).toString();
                }
            }
            QString equip = sql->value(3).toString();
            QString time = sql->value(4).toString();
            QString state = sql->value(5).toString();
            QString stepsid = sql->value(7).toString();
            c="select * from teststep where teststep.id = "+stepsid+";";
            QString teststep ="";
            if(sql2->exec(c)){
                while (sql2->next()){
                    teststep=sql2->value(1).toString();
                }
            }
            QString resultid = sql->value(8).toString();
            c="select * from testresult where testresult.id = "+resultid+";";
            QString testresult ="";
            if(sql2->exec(c)){
                while (sql2->next()){
                    testresult=sql2->value(1).toString();
                }
            }



            // 展示表格内容
            ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(id));
            ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(projectname));
            ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(testname));
            ui->tableWidget_2->setItem(row, 3, new QTableWidgetItem(equip));
            ui->tableWidget_2->setItem(row, 4, new QTableWidgetItem(time));
            if(state =="0"){
                ui->tableWidget_2->setItem(row, 5, new QTableWidgetItem("已完成"));
            }else {
                ui->tableWidget_2->setItem(row, 5, new QTableWidgetItem("未完成"));
            }
            ui->tableWidget_2->setItem(row, 6, new QTableWidgetItem(teststep));
            ui->tableWidget_2->setItem(row, 7, new QTableWidgetItem(testresult));
            row++;
        }
    }
    else
        qDebug() << "数据获取失败" << sql->lastError().text();
}

void User::on_button_insert_clicked()
{
    select =new Select;
    select ->show();
}
