#include "manager.h"
#include "ui_manager.h"
#include <QDebug>
#include <QStackedWidget>
#include <globle.h>
// SQL 相关
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
QSqlQuery *sql;

Manager::Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);   
    qDebug() << ui->stackedWidget->count();
    SortUporDown = true; // 默认升序

    // 初始化数据库
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
         db = QSqlDatabase::database("qt_sql_default_connection");
    else
    db = QSqlDatabase::addDatabase("QMYSQL");;
    db.setHostName("localhost");
    db.setDatabaseName("lanzhou");
    db.setUserName("root");
    db.setPassword("172901698xl");
    if (db.open())
    {
        qDebug() << "打开数据库成功";
        sql = new QSqlQuery(db);
    }
    else
    {
        qDebug() << "打开数据库失败";
    }


    // 表格控件初始化
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);             // 禁用编辑
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自适应
    this->show_table();                                                             // 填充数据
}

Manager::~Manager()
{
    delete ui;
}
// 获取数据库中的行数
int Manager::get_sql_row()
{
    int row = 0;
    // 获取数据库中的行数b
    QString cmd = "select count(*) from user;";
    if (sql->exec(cmd))
    {
        qDebug() << sql;
        while (sql->next()){
            row = sql->value(0).toInt();
        }
    }
    return row;
}
// 从数据库中填充表格
void Manager::show_table()
{
        qDebug() << "运行到这1";
    // 设置正确行数
    ui->tableWidget->setRowCount(this->get_sql_row());
    qDebug() << "运行到这2";
    // 获取数据库
    QString cmd = "select * from user;";
    if (sql->exec(cmd))
    {
        int row = 0;
        while (sql->next())
        {
            // 获取数据库内容
            QString id = sql->value(0).toString();
            QString name = sql->value(1).toString();
            QString permission = sql->value(2).toString();
            QString password = sql->value(3).toString();

            // 展示表格内容
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(id));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(name));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(permission));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(password));
            row++;
        }
    }
    else
        qDebug() << "数据获取失败" << sql->lastError().text();
}



void Manager::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void Manager::on_pushButton_2_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);
}

void Manager::on_button_exit_clicked()
{
    this->close();
}
