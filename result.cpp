#include "result.h"
#include "ui_result.h"
#include <QListWidget>
#include <QPushButton>
#include <globle.h>
// SQL 相关
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>


result::result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::result)
{
    ui->setupUi(this);

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

}

result::~result()
{
    delete ui;
}

void result::refresh()
{
    qDebug()<<"shuaxin";
    this->show_table();
    on_tableWidget_clicked(mIndex);
}
void result::on_tableWidget_clicked(const QModelIndex &index)
{
    mIndex=index;
    QString cmd = "select * from testproject where id="+ui->tableWidget->item(mIndex.row(), 0)->text();

        if (sql->exec(cmd))
        {
            while (sql->next())
            {
                // 获取数据库内容
                QString name = sql->value(0).toString();
                QString id = sql->value(1).toString();
                QString equipment = sql->value(2).toString();
                QString time = sql->value(3).toString();
                ui->name->setText(name);
                ui->equipment->setText(equipment);
                ui->time->setText(time);

            }
        }
        else
            qDebug() << "数据获取失败" << sql->lastError().text();
}

void result::show_table(){
    // 设置正确行数
    ui->tableWidget->setRowCount(this->get_sql_row());
    // 获取数据库
    QString cmd = "select * from testproject;";
    if (sql->exec(cmd))
    {
        int row = 0;
        while (sql->next())
        {
            // 获取数据库内容
            QString name = sql->value(0).toString();
            QString equipment = sql->value(2).toString();
            QString time = sql->value(3).toString();


            // 展示表格内容
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(equipment));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(time));
            row++;

        }
    }
    else
        qDebug() << "数据获取失败" << sql->lastError().text();

}

int result::get_sql_row()
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

