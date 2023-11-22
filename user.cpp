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
    this->show_table();

    select =new Select;
    edit = new editOptions;
    Result = new result;
    connect(select, &Select::windowClosed, this, &User::refresh);
    connect(edit, &editOptions::windowClosed, this, &User::refresh);
    connect(Result, &result::windowClosed, this, &User::refresh);
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

    select ->show();
}

void User::refresh()
{
    qDebug()<<"shuaxin";
    this->show_table();
    on_tableWidget_clicked(mIndex);
}
void User::on_button_exit_clicked()
{
    this->close();
}



void User::on_tableWidget_clicked(const QModelIndex &index)
{
    mIndex=index;
    QString cmd = "select * from teststep where id="+ui->tableWidget->item(mIndex.row(), 0)->text();

        if (sql->exec(cmd))
        {
            while (sql->next())
            {
                // 获取数据库内容
                QString id = sql->value(0).toString();
                QString name = sql->value(1).toString();
                QString createrid = sql->value(2).toString();
                QString testmode = sql->value(3).toString();
                QString steps = sql->value(4).toString();
                ui->name->setText(name);
                QString qsql = "select name from user where id="+createrid;
                if (sql2->exec(qsql)){
                    while (sql2->next()){
                        ui->creater->setText(sql2->value(0).toString());
                    }
                }
                if(testmode=="1"){
                    ui->model->setText("全自动测试");
                }else{
                    ui->model->setText("手动测试");
                }

                setSteps(steps);
            }
        }
        else
            qDebug() << "数据获取失败" << sql->lastError().text();
}

void User::on_button_change_clicked()
{
    if(mIndex.row()==-1 &&mIndex.column()==-1){
        QMessageBox::critical(this, tr("Error"),  tr("请在表格中选择一个数据"),
                                           QMessageBox::Yes);
        return;
    }

    edit->getId(ui->tableWidget->item(mIndex.row(),0)->text());
    edit->show();
}

void User::setSteps(QString str){
    ui->treeWidget->clear();    //初始化树形控件
    ui->treeWidget->setHeaderHidden(true);  //隐藏表头
    check1=false;
    check2=false;
    check3=false;
    check4=false;
    check5=false;
    check6=false;

    existingParent1=NULL;
    existingParent2=NULL;
    existingParent3=NULL;
    existingParent4=NULL;
    existingParent5=NULL;
    existingParent6=NULL;
    QStringList stringList = str.split(";");

    // 遍历QStringList并输出每个字符串内容
    for (const QString &s : stringList) {
        if(s!=""){
            QString qsql = "select * from step where id ="+ s;
            if(sql2->exec(qsql)){
                while(sql2->next()){
                    QString Type = sql2->value(2).toString();
                    QString Name = sql2->value(1).toString();
                    if(Type == "功耗检查"){
                        if (!check1){
                            QTreeWidgetItem* subItem11 = new QTreeWidgetItem(ui->treeWidget);
                            //subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
                            subItem11->setText(0, "功耗检查");  //设置子项显示的文本
                            //subItem11->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态
                            check1=true;
                            existingParent1=subItem11;
                        }
                        //孙子项
                        QTreeWidgetItem* subItem = new QTreeWidgetItem(existingParent1);   //指定子项属于哪一个父项
//                        subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                        subItem->setText(0, Name);
//                        subItem->setCheckState(0, Qt::Unchecked);
//                        subItem->setFlags(subItem->flags() & ~Qt::ItemIsUserCheckable);
                    }else if(Type == "基准电压精度检查"){
                        if (!check2){
                            QTreeWidgetItem* subItem12 = new QTreeWidgetItem(ui->treeWidget);
//                            subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
                            subItem12->setText(0, "基准电压精度检查");
//                            subItem12->setCheckState(0, Qt::Unchecked);
                            check2=true;
                            existingParent2=subItem12;
                        }
                        //孙子项
                        QTreeWidgetItem* subItem = new QTreeWidgetItem(existingParent2);   //指定子项属于哪一个父项
//                        subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                        subItem->setText(0, Name);
//                        subItem->setCheckState(0, Qt::Unchecked);
                    }else if(Type == "输入信号特征检查"){
                        if (!check3){
                            QTreeWidgetItem* subItem13 = new QTreeWidgetItem(ui->treeWidget);
//                            subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
                            subItem13->setText(0, "输入信号特征检查");
//                            subItem13->setCheckState(0, Qt::Unchecked);
                            check3=true;
                            existingParent3=subItem13;
                        }
                        //孙子项
                        QTreeWidgetItem* subItem = new QTreeWidgetItem(existingParent3);   //指定子项属于哪一个父项
//                        subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                        subItem->setText(0, Name);
//                        subItem->setCheckState(0, Qt::Unchecked);
                    }else if(Type == "优先级别检查"){
                        if (!check4){
                            QTreeWidgetItem* group2 = new QTreeWidgetItem(ui->treeWidget);
                            group2->setText(0, "优先级别检查");
//                            group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
//                            group2->setCheckState(0, Qt::Unchecked);
                            check4=true;
                            existingParent4=group2;
                        }
                        //孙子项
                        QTreeWidgetItem* subItem = new QTreeWidgetItem(existingParent4);   //指定子项属于哪一个父项
//                        subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                        subItem->setText(0, Name);
//                        subItem->setCheckState(0, Qt::Unchecked);
                    }else if(Type == "余度检查"){
                        if (!check5){
                            QTreeWidgetItem* group3 = new QTreeWidgetItem(ui->treeWidget);
                            group3->setText(0, "余度检查");
//                            group3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
//                            group3->setCheckState(0, Qt::Unchecked);
                            check5=true;
                            existingParent5=group3;
                        }
                        //孙子项
                        QTreeWidgetItem* subItem = new QTreeWidgetItem(existingParent5);   //指定子项属于哪一个父项
//                        subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                        subItem->setText(0, Name);
//                        subItem->setCheckState(0, Qt::Unchecked);
                    }else{
                        if (!check6){
                            QTreeWidgetItem* group4 = new QTreeWidgetItem(ui->treeWidget);
                            group4->setText(0, "429通信检查");
//                            group4->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
//                            group4->setCheckState(0, Qt::Unchecked);
                            check6=true;
                            existingParent6=group4;
                        }
                        //孙子项
                        QTreeWidgetItem* subItem = new QTreeWidgetItem(existingParent6);   //指定子项属于哪一个父项
//                        subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                        subItem->setText(0, Name);
//                        subItem->setCheckState(0, Qt::Unchecked);
                    }

                }
            }
        }
    }
}

void User::on_pushButton_3_clicked()
{

    Result->show();
}
