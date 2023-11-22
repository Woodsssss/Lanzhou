#include "result.h"
#include "ui_result.h"
#include <QDebug>
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


    // 表格控件初始化
    ui->projects->setEditTriggers(QAbstractItemView::NoEditTriggers);             // 禁用编辑
    ui->projects->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自适应
    this->show_table();

    connect(ui->project_name,SIGNAL(textChanged(QString)),this,SLOT(locate()));
    connect(ui->projects, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(on_projects_clicked(mIndex)));
}

result::~result()
{
    delete ui;
}


// 获取数据库中的行数
int result::get_sql_row()
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

void result::show_table(){

    // 设置正确行数
    ui->projects->setRowCount(this->get_sql_row());
    QString cmd = "select * from testproject;";
    if (sql->exec(cmd))
    {
        int row = 0;
        while (sql->next())
        {
            // 获取数据库内容
            QString id = sql->value(0).toString();
            QString projectname = sql->value(1).toString();
            QString c ;
            QString resultid = sql->value(8).toString();
            c="select * from testresult where testresult.id = "+resultid+";";
            QString testresult ="";
            if(sql2->exec(c)){
                while (sql2->next()){
                    testresult=sql2->value(1).toString();
                }
            }

            // 展示表格内容
            ui->projects->setItem(row, 0, new QTableWidgetItem(id));
            ui->projects->setItem(row, 1, new QTableWidgetItem(projectname));
            ui->projects->setItem(row, 2, new QTableWidgetItem(testresult.split(";")[0]));
            row++;
        }
    }
    else
        qDebug() << "数据获取失败" << sql->lastError().text();
}

//检查结果界面查找
void result::locate()
{
    QString input_name =ui->project_name->text();
    int row_num=this->get_sql_row();
    if(input_name==""){
        for(int i=0;i<row_num;i++){
            ui->projects->setRowHidden(i,false);
        }
    }
    else{
        QList <QTableWidgetItem *> item = ui->projects->findItems(ui->project_name->text(),Qt::MatchContains);
        //隐藏所有行
        for(int i=0;i<row_num;i++){
            ui->projects->setRowHidden(i,true);//隐藏
        }
        if(!item.empty()){
            //恢复对应的行
            for(int i=0;i<item.count();i++){
                ui->projects->setRowHidden(item.at(i)->row(),false);
            }
        }
    }
}

void result::refresh()
{
    qDebug()<<"刷新";
    this->show_table();
    on_projects_clicked(mIndex);
}

void result::on_projects_clicked(const QModelIndex &index)
{
//    qDebug()<<"更新表格";
    mIndex=index;
    QString cmd = "select * from testproject where id="+ui->projects->item(mIndex.row(), 0)->text();
        if (sql->exec(cmd))
        {
            while (sql->next())
            {
                // 获取数据库内容
                QString id = sql->value(0).toString();
                QString name = sql->value(1).toString();
                QString equipment = sql->value(3).toString();
                QString time = sql->value(4).toString();
                QString resultid = sql->value(8).toString();
                //更新右侧项目名称等信息
                ui->name->setText(name);
                ui->equipment->setText(equipment);
                ui->time->setText(time);
                QString qsql = "select * from testresult where Id="+resultid;
                if (sql2->exec(qsql)){
                    while (sql2->next()){
                        QString state=sql2->value(1).toString();
                        QString results=sql2->value(2).toString();
                        //更新详细测试结果文本
                        detailInfor(results);
                    }
                }
            }
        }
        else
            qDebug() << "数据获取失败" << sql->lastError().text();
}

void result::detailInfor(QString results){
    ui->treeWidget->clear();    //初始化树形控件
    ui->treeWidget->setHeaderHidden(true);  //隐藏表头
    results = results.mid(0,results.size()-1);
    //按分号分割
    QStringList resultList = results.split(";");
    QString step,s,testValue;
    // 遍历QStringList并输出每个字符串内容
    QString temp = "0";
    QTreeWidgetItem* treeTemp = nullptr;
    for (const QString &result : resultList) {
        step="";
        s="";
        testValue="";
        //按逗号分割
        QStringList detailList = result.split(",");
        int i=0;
        for (const QString &detail : detailList) {
                if(i==0){
                    step=detail;
                }else if(i==1){
                    s=detail;
                }else{
                    testValue=detail;
                }
                i++;
        }
        QString qs = "select * from step where Id="+step;
        QString type;
        QString steptext;
        if (sql2->exec(qs)){
            while (sql2->next()){
                steptext=sql2->value(1).toString();
                type=sql2->value(2).toString();
            }
        }
        if (type!=temp){
            QTreeWidgetItem* subItem = new QTreeWidgetItem(ui->treeWidget);
            subItem->setText(0, type);  //设置子项显示的文本
            treeTemp = subItem;
            temp=type;
        }
        // 构建要显示的字符串
        QString rresult = steptext;
        QString flag = (s == "0") ? "(通过)" : "(未通过)";
        rresult.append(flag);
        if (testValue!="NULL"){
            rresult.append(":" + testValue);
        }
        QTreeWidgetItem* subItem1 = new QTreeWidgetItem(treeTemp);
        subItem1->setText(0, rresult);  //设置子项显示的文本
    }
}
