#include "manager.h"
#include "ui_manager.h"
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


Manager::Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager)
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
    this->show_table();                                                             // 填充数据
    connect(ui->user_account,SIGNAL(textChanged(QString)),this,SLOT(locate()));
    connect(ui->project_name,SIGNAL(textChanged(QString)),this,SLOT(locate_2()));
    connect(ui->step_name,SIGNAL(textChanged(QString)),this,SLOT(locate_3()));
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

// 获取数据库中的行数
int Manager::get_sql_row2()
{
    int row = 0;
    // 获取数据库中的行数b
    QString cmd = "select count(*) from testproject;";
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
int Manager::get_sql_row3()
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
// 从数据库中填充表格
void Manager::show_table()
{

    // 设置正确行数
    ui->tableWidget->setRowCount(this->get_sql_row());
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
            if(permission=="0"){
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem("管理员"));
            }else {
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem("用户"));
            }

            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(password));
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


    //table3
    // 设置正确行数
    ui->tableWidget_3->setRowCount(this->get_sql_row3());
    // 获取数据库
    QString cmd3 = "select * from teststep;";
    if (sql->exec(cmd3))
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
            QString c ;
            // 展示表格内容
            ui->tableWidget_3->setItem(row, 0, new QTableWidgetItem(id));
            ui->tableWidget_3->setItem(row, 1, new QTableWidgetItem(name));
            c="select * from user where user.id = "+ createrbyid + ";";
            QString creater="";
            if(sql2->exec(c)){
                while (sql2->next()){
                    creater=sql2->value(1).toString();
                }
            }
            ui->tableWidget_3->setItem(row, 2, new QTableWidgetItem(creater));
            ui->tableWidget_3->setItem(row, 3, new QTableWidgetItem(testmode));
            row++;
        }
    }
    else
        qDebug() << "数据获取失败" << sql->lastError().text();
}


//页面切换
void Manager::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void Manager::on_pushButton_2_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);
}

void Manager::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


//用户界面退出
void Manager::on_button_exit_clicked()
{
    this->close();
}


//用户界面插入数据
void Manager::on_button_insert_clicked()
{
    //弹窗获取数据
    bool bOk = false;
    QString account = QInputDialog::getText(this,"input data dialog","请输入账号",QLineEdit::Normal,"input account",&bOk);
    QStringList tLi;
    tLi<< "管理员" << "用户";
    QString permissions= QInputDialog::getItem(this,"input data dialog","请设置用户权限",tLi,0,false,&bOk);
    if(permissions=="管理员"){
        permissions = "0";
    }else {
        permissions = "1";
    }

    QString password = QInputDialog::getText(this,"input data dialog","请设置密码",QLineEdit::Normal,"input password",&bOk);
    //将数据插入数据库
    if(bOk && !account.isEmpty() &&!permissions.isEmpty() && !password.isEmpty()){
        if(db.open()){
            QString cmd = QString("select * from user order by id desc limit 1;");
            int maxId = 0;
            if (sql->exec(cmd))
            {
                qDebug() << sql;
                while (sql->next()){
                    maxId = sql->value(0).toInt();
                }
            }
            qDebug() << maxId;
            QString cmd2 = QString("insert into user(id,Name,Permission,Password) values('%1','%2','%3','%4')").arg(maxId+1).arg(account).arg(permissions).arg(password);
            if(sql->exec(cmd2)){
                qDebug() << "插入数据成功";
                show_table();
            }else
                qDebug() << "插入数据失败" << sql->lastError().text();
        }
    }else{
        QMessageBox::critical(this, tr("Error"),  tr("用户名或密码为空"),
                                           QMessageBox::Yes);
        return;
    }
}
//用户界面删除
void Manager::on_button_delete_clicked()
{
    if(mIndex.row()==-1 &&mIndex.column()==-1){
        QMessageBox::critical(this, tr("Error"),  tr("请在表格中选择一个数据"),
                                           QMessageBox::Yes);
        return;
    }
    QMessageBox::StandardButton confirmDelete = QMessageBox::question(
                nullptr,
                "Confirm Delete",
                "确定删除?",
                QMessageBox::Yes | QMessageBox::No
    );
    if(confirmDelete == QMessageBox::No){
        return;
    }

    if(CUsername == ui->tableWidget->item(mIndex.row(), 1)->text()){
        QMessageBox::critical(this, tr("Error"),  tr("不能删除"),
                                           QMessageBox::Yes);
        return;
    }
    QString cmd = "delete from user where id="+ui->tableWidget->item(mIndex.row(), 0)->text();

        if (sql->exec(cmd))
        {
            // 成功才会更新展示并返回，否则都会收到提示框
            this->show_table();
            return;
        }
        else
            qDebug() << "数据删除失败" << sql->lastError().text();

    QMessageBox::warning(this, tr("删除信息"), tr("输入有误，请检查！"), QMessageBox::Ok);
}

//选择用户界面一个元素
void Manager::on_tableWidget_clicked(const QModelIndex &index)
{
    mIndex=index;
}
//用户界面编辑
void Manager::on_pushButton_3_clicked()
{
    if(mIndex.row()==-1 &&mIndex.column()==-1){
        QMessageBox::critical(this, tr("Error"),  tr("请在表格中选择一个数据"),
                                           QMessageBox::Yes);
        return;
    }
    qDebug()<<mIndex.column()<<"  "<<mIndex.row();
    bool isOK;//定义bool类型
    QString text;
    if(mIndex.column() == 2){
         QStringList tLi;
         tLi<< "管理员" << "用户";
         text = QInputDialog::getItem(this,"input data dialog","请设置用户权限",tLi,0,false,&isOK);
     }else
       text = QInputDialog::getText(this,"Update","修改当前内容",QLineEdit::Normal,mIndex.data().toString(),&isOK);//弹出修改框，默认显示当前内容，修改后点击按钮，是则isOK为true，否则isOK为false

     if(isOK){
         QTableWidgetItem *item = new QTableWidgetItem(text);
         ui->tableWidget->setItem(mIndex.row(), mIndex.column(), item);

         // 获取要更新的值
         QString newValue = text;
         qDebug()<<newValue<<"  "<<mIndex.column()<<"  "<<mIndex.row();


         // 构造 SQL 更新语句
         QString updateCmd = "UPDATE user SET ";
         if (mIndex.column() == 1) {
             updateCmd += "name='" + newValue + "'";
         } else if (mIndex.column() == 2) {
             if(newValue=="用户"){
                 updateCmd += "permission='1'";
             }else{
                 updateCmd += "permission='0'";
             }

         } else if (mIndex.column() == 3) {
             updateCmd += "password='" + newValue + "'";
         }
         updateCmd += " WHERE id='" + ui->tableWidget->item(mIndex.row(), 0)->text() + "'";
         qDebug()<<updateCmd;
         // 执行 SQL 更新语句
         QSqlQuery query;
         if (query.exec(updateCmd)) {
            qDebug() << "数据已更新";
         } else {
            qDebug() << "数据更新失败: " << query.lastError().text();
         }
     }
}
//用户界面查找
void Manager::locate()
{
    QString input_name =ui->user_account->text();
    int row_num=this->get_sql_row();
    if(input_name==""){
        for(int i=0;i<row_num;i++){
            ui->tableWidget->setRowHidden(i,false);
        }
    }
    else{
        QList <QTableWidgetItem *> item = ui->tableWidget->findItems(ui->user_account->text(),Qt::MatchContains);
        //隐藏所有行
        for(int i=0;i<row_num;i++){
            ui->tableWidget->setRowHidden(i,true);//隐藏
        }
        if(!item.empty()){
            //恢复对应的行
            for(int i=0;i<item.count();i++){
                ui->tableWidget->setRowHidden(item.at(i)->row(),false);
            }
        }
    }
}


//测试工程界面退出
void Manager::on_button_exit_2_clicked()
{
    this->close();
}
//选择测试工程界面一个元素
void Manager::on_tableWidget_2_clicked(const QModelIndex &index)
{
    mIndex2=index;
}

//测试工程界面删除
void Manager::on_button_delete_2_clicked()
{
    if(mIndex2.row()==-1 &&mIndex2.column()==-1){
           QMessageBox::critical(this, tr("Error"),  tr("请在表格中选择一个数据"),
                                              QMessageBox::Yes);
           return;
    }

    QMessageBox::StandardButton confirmDelete = QMessageBox::question(
                nullptr,
                "Confirm Delete",
                "确定删除?",
                QMessageBox::Yes | QMessageBox::No
    );
    if(confirmDelete == QMessageBox::No){
        return;
    }

    QString cmd = "delete from testproject where id="+ui->tableWidget_2->item(mIndex2.row(), 0)->text();

    if (sql->exec(cmd)) {
               // 成功才会更新展示并返回，否则都会收到提示框
               this->show_table();
               return;
     }else
               qDebug() << "数据删除失败" << sql->lastError().text();

    QMessageBox::warning(this, tr("删除信息"), tr("输入有误，请检查！"), QMessageBox::Ok);
}

//测试工程界面查找
void Manager::locate_2()
{
    QString input_name =ui->project_name->text();
    int row_num=this->get_sql_row2();
    if(input_name==""){
        for(int i=0;i<row_num;i++){
            ui->tableWidget_2->setRowHidden(i,false);
        }
    }
    else{
        QList <QTableWidgetItem *> item = ui->tableWidget_2->findItems(ui->project_name->text(),Qt::MatchContains);
        //隐藏所有行
        for(int i=0;i<row_num;i++){
            ui->tableWidget_2->setRowHidden(i,true);//隐藏
        }
        if(!item.empty()){
            //恢复对应的行
            for(int i=0;i<item.count();i++){
                ui->tableWidget_2->setRowHidden(item.at(i)->row(),false);
            }
        }
    }
}


//检测项界面退出
void Manager::on_button_exit_3_clicked()
{
    this->close();
}
//选择检测项界面一个元素
void Manager::on_tableWidget_3_clicked(const QModelIndex &index)
{
    mIndex3 = index;
}


//检测项界面删除
void Manager::on_button_delete_3_clicked()
{
    if(mIndex3.row()==-1 &&mIndex3.column()==-1){
        QMessageBox::critical(this, tr("Error"),  tr("请在表格中选择一个数据"),
                                           QMessageBox::Yes);
        return;
    }

    QMessageBox::StandardButton confirmDelete = QMessageBox::question(
                nullptr,
                "Confirm Delete",
                "确定删除?",
                QMessageBox::Yes | QMessageBox::No
    );
    if(confirmDelete == QMessageBox::No){
        return;
    }

    QString c = QString("select count(*) from testproject where testproject.stepsid ="+ui->tableWidget_3->item(mIndex3.row(),0)->text());
    int row = 0;
    if (sql2->exec(c))
    {
        while (sql2->next()){
            row = sql2->value(0).toInt();
        }
    }

    if(row!=0){
        QMessageBox::critical(this, tr("Error"),  tr("已有检测工程使用该检测项，无法删除"),
                                           QMessageBox::Yes);
        return;
    }
    qDebug()<<ui->tableWidget_3->item(mIndex3.row(),0)->text()<<"row ="<<row;
//    QString cmd = QString("delete from teststep where id="+ui->tableWidget->item(mIndex3.row(), 0)->text());
    sql2->prepare("DELETE FROM teststep WHERE id = :id");
    sql2->bindValue(":id", ui->tableWidget_3->item(mIndex3.row(), 0)->text());
        if (sql2->exec())
        {
            qDebug()<<ui->tableWidget_3->item(mIndex3.row(),0)->text()<<"row ="<<row;
            // 成功才会更新展示并返回，否则都会收到提示框
            this->show_table();
            return;
        }
        else
            qDebug() << "数据删除失败" << sql->lastError().text();

    QMessageBox::warning(this, tr("删除信息"), tr("输入有误，请检查！"), QMessageBox::Ok);
}

//检测项界面查找
void Manager::locate_3()
{
    QString input_name =ui->step_name->text();
    int row_num=this->get_sql_row3();
    if(input_name==""){
        for(int i=0;i<row_num;i++){
            ui->tableWidget_3->setRowHidden(i,false);
        }
    }
    else{
        QList <QTableWidgetItem *> item = ui->tableWidget_3->findItems(ui->step_name->text(),Qt::MatchContains);
        //隐藏所有行
        for(int i=0;i<row_num;i++){
            ui->tableWidget_3->setRowHidden(i,true);//隐藏
        }
        if(!item.empty()){
            //恢复对应的行
            for(int i=0;i<item.count();i++){
                ui->tableWidget_3->setRowHidden(item.at(i)->row(),false);
            }
        }
    }
}


