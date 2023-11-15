#include "editoptions.h"
#include "ui_editoptions.h"

#include <QListWidget>
#include <QPushButton>
#include <globle.h>

// SQL 相关
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QString>
#include <QMessageBox>
#include "user.h"

editOptions::editOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editOptions)
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

    init();


    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(onTreeItemChanged(QTreeWidgetItem*, int)));

    totalItemCount = 0;
    visitedItemCount =0;
    int topLevelItemCount = ui->treeWidget->topLevelItemCount();
    for (int i = 0; i < topLevelItemCount; ++i) {
        QTreeWidgetItem* topLevelItem = ui->treeWidget->topLevelItem(i);
        // 递归处理每个顶层项
        traverseTree(topLevelItem);
     }
    this->flag = 0;

}

editOptions::~editOptions()
{
    delete ui;
}

void editOptions::init()
{

    ui->treeWidget->clear();    //初始化树形控件
    ui->treeWidget->setHeaderHidden(true);  //隐藏表头
    ui->radioButton->setChecked(true); //设置全自动模式选中

    //定义第一个树形组 爷爷项
    QTreeWidgetItem* group1 = new QTreeWidgetItem(ui->treeWidget);
    group1->setText(0, QStringLiteral("可选检测项"));    //树形控件显示的文本信息
    group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);   //设置树形控件子项的属性
    group1->setCheckState(0, Qt::Unchecked); //初始状态没有被选中
    //第一组子项
    QTreeWidgetItem* subItem11 = new QTreeWidgetItem(group1);
    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    subItem11->setText(0, "功耗检查");  //设置子项显示的文本
    subItem11->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* subItem12 = new QTreeWidgetItem(group1);
    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    subItem12->setText(0, "基准电压精度检查");
    subItem12->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem13 = new QTreeWidgetItem(group1);
    subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    subItem13->setText(0, "输入信号特征检查");
    subItem13->setCheckState(0, Qt::Unchecked);


    //父亲项
    QTreeWidgetItem* group2 = new QTreeWidgetItem(group1);
    group2->setText(0, "优先级别检查");
    group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group2->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group3 = new QTreeWidgetItem(group1);
    group3->setText(0, "余度检查");
    group3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group3->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group4 = new QTreeWidgetItem(group1);
    group4->setText(0, "429通信检查");
    group4->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group4->setCheckState(0, Qt::Unchecked);


    //从数据库中加载每类的测试项
    QString cmd = "select * from step;";
    if (sql->exec(cmd)){
        while (sql->next()){
            QString Type = sql->value(2).toString();
            QString Name = sql->value(1).toString();
            if(Type == "功耗检查"){
                //孙子项
                QTreeWidgetItem* subItem = new QTreeWidgetItem(subItem11);   //指定子项属于哪一个父项
                subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem->setText(0, Name);
                subItem->setCheckState(0, Qt::Unchecked);
            }else if(Type == "基准电压精度检查"){
                //孙子项
                QTreeWidgetItem* subItem = new QTreeWidgetItem(subItem12);   //指定子项属于哪一个父项
                subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem->setText(0, Name);
                subItem->setCheckState(0, Qt::Unchecked);
            }else if(Type == "输入信号特征检查"){
                //孙子项
                QTreeWidgetItem* subItem = new QTreeWidgetItem(subItem13);   //指定子项属于哪一个父项
                subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem->setText(0, Name);
                subItem->setCheckState(0, Qt::Unchecked);
            }else if(Type == "优先级别检查"){
                //孙子项
                QTreeWidgetItem* subItem = new QTreeWidgetItem(group2);   //指定子项属于哪一个父项
                subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem->setText(0, Name);
                subItem->setCheckState(0, Qt::Unchecked);
            }else if(Type == "余度检查"){
                //孙子项
                QTreeWidgetItem* subItem = new QTreeWidgetItem(group3);   //指定子项属于哪一个父项
                subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem->setText(0, Name);
                subItem->setCheckState(0, Qt::Unchecked);
            }else{
                //孙子项
                QTreeWidgetItem* subItem = new QTreeWidgetItem(group4);   //指定子项属于哪一个父项
                subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem->setText(0, Name);
                subItem->setCheckState(0, Qt::Unchecked);
            }
        }
    }

    ui->treeWidget->expandAll();  //展开树

}



void editOptions::updateParentItem(QTreeWidgetItem* item)
{
    QTreeWidgetItem *parent = item->parent();
    if (parent == NULL)
        return;

    int nSelectedCount = 0;
    int childCount = parent->childCount();

    for (int i = 0; i < childCount; i++) //判断有多少个子项被选中
    {
        QTreeWidgetItem* childItem = parent->child(i);
        if (childItem->checkState(0) == Qt::Checked || childItem->checkState(0) == Qt::PartiallyChecked)
        {
            nSelectedCount++;
        }
    }

    if (nSelectedCount <= 0)  //如果没有子项被选中，父项设置为未选中状态
        parent->setCheckState(0, Qt::Unchecked);
    else if (nSelectedCount > 0 && nSelectedCount < childCount)    //如果有部分子项被选中，父项设置为部分选中状态，即用灰色显示
        parent->setCheckState(0, Qt::PartiallyChecked);
    else if (nSelectedCount == childCount)    //如果子项全部被选中，父项则设置为选中状态
        parent->setCheckState(0, Qt::Checked);

    updateParentItem(parent);

}

void editOptions::onTreeItemChanged(QTreeWidgetItem* item, int column)
{
    int count = item->childCount(); //返回子项的个数

    if (Qt::Checked == item->checkState(0))
    {
        if (count > 0)
        {
            for (int i = 0; i < count; i++)
                item->child(i)->setCheckState(0, Qt::Checked);
        }
        else
            updateParentItem(item);
    }
    else if (Qt::Unchecked == item->checkState(0))
    {
        if (count > 0)
        {
            for (int i = 0; i < count; i++)
                item->child(i)->setCheckState(0, Qt::Unchecked);
        }
        else
            updateParentItem(item);
    }
}



void editOptions::on_pushButton_clicked()
{

    //遍历QTreeWidget的项
    // 遍历QTreeWidget的项
    int topLevelItemCount = ui->treeWidget->topLevelItemCount();
    for (int i = 0; i < topLevelItemCount; ++i) {
        QTreeWidgetItem* topLevelItem = ui->treeWidget->topLevelItem(i);
        // 递归处理每个顶层项
        saveSelectedLeafItemsRecursive(topLevelItem);
     }
    visitedItemCount=0;
    this->close();
    emit windowClosed();

}

void editOptions::saveSelectedLeafItemsRecursive(QTreeWidgetItem* item)
{
    visitedItemCount++;
    QString itemName = ui->project_name->text();
    int itemMode = 0;
    if(ui->radioButton->isChecked()){
        itemMode = 1;
    }
    if(ui->radioButton_2->isChecked()){
        itemMode = 2;
    }
    if(itemMode==0){
        QMessageBox::critical(this, tr("Error"),  tr("请选择测试模式!"),
                                           QMessageBox::Yes);
        return;
    }
    if (item->childCount() == 0 && item->checkState(0) == Qt::Checked) {
        // 该项是叶子节点且被选中

        //在数据库中查询该叶子节点文本对应的编号
        QString cmd = "select id from step where Name='"+item->text(0)+"'and Type ='"+ item->parent()->text(0)+"' ;";

        if(sql2->exec(cmd)){
            if (sql2->next()) {
                itemText.append(sql2->value(0).toString()+";");

            }
        }
//        itemText.append(item->text(0)); // 获取项的文本信息
    } else {
        // 遍历子项
        int childCount = item->childCount();
        for (int i = 0; i < childCount; ++i) {
            QTreeWidgetItem* childItem = item->child(i);
            saveSelectedLeafItemsRecursive(childItem);
        }
    }

    if(db.open()){
        QString cmd = QString("select * from teststep order by id desc limit 1;");
        int maxId = 0;
        if (sql->exec(cmd))
        {
            while (sql->next()){
                maxId = sql->value(0).toInt();
            }
        }
        if(totalItemCount==visitedItemCount&&this->flag==0){
            // 将选中的项存入数据库，假设使用SQL语句插入数据
            QString sql = QString("UPDATE teststep SET id='%1', Name='%2', CreatedById='%3', TestMode='%4', Steps='%5' WHERE id='%6'")
                .arg(id)
                .arg(itemName)
                .arg(userid.toInt())
                .arg(itemMode)
                .arg(itemText)
                .arg(id);
            QSqlQuery query;
            if (query.exec(sql)) {
                // 插入成功
                qDebug() << "Item saved to database";
            } else {
                // 插入失败
                qDebug() << "Failed to save item to database";
            }
            this->flag = 1;
        }
    }

}


void editOptions::traverseTree(QTreeWidgetItem *item){
    totalItemCount++;

    int childCount = item->childCount();

    for (int i = 0; i < childCount; ++i) {
            QTreeWidgetItem* childItem = item->child(i);
            traverseTree(childItem);
     }

}



void editOptions::on_pushButton_2_clicked()
{
    this->close();
}


void editOptions::handleItemSelected(){
    if(db.open()){
      QString searchValue = this->id;
      QSqlQuery query;
      query.prepare("SELECT * FROM teststep WHERE id = :value");
      query.bindValue(":value",searchValue);
      if(query.exec()){
          // 处理结果
          while (query.next()) {
              // 获取每一行的数据
              QVariant name = query.value("Name");
              QVariant testmode = query.value("TestMode");
              QVariant steps = query.value("Steps");

              // 在这里处理每一行的数据
              // ...
              qDebug()<<"拿到的结果："<< name<<testmode<<steps;

              if(name.canConvert<QString>()){
                  QString pname = name.toString();
                  ui->project_name->setText(pname);
              }else{
                  qDebug() << "类型无法转换";
              }

              if(testmode.canConvert<int>()){
                  int ptestmode = testmode.toInt();
                  if(ptestmode == 1) {
                      ui->radioButton->setChecked(true);
                  }
                  else{
                      ui->radioButton_2->setChecked(true);
                  }
              }else{
                  qDebug() << "类型无法转换";
              }

              if(steps.canConvert<QString>()){
                 QList<QString> stepList = steps.toString().split(";");
                 //删除其中的 空项
                 for (auto iter = stepList.begin(); iter != stepList.end(); ) {
                     if (iter->isEmpty()) {
                         iter = stepList.erase(iter);  // 删除空项，并返回指向下一个元素的迭代器
                     } else {
                         ++iter;  // 移动到下一个元素
                     }
                 }
                 QList<QString> checkStepList;
                 for(auto iter = stepList.begin(); iter != stepList.end();++iter){

                     QString cmd = "select Name from step where Id="+ *iter +" ;";
                     if(sql->exec(cmd)){
                         if (sql->next()) {
                             checkStepList.append(sql->value(0).toString());
                         }
                     }else{
                         qDebug()<<"数据库执行错误";
                     }
                 }
                 //根据checkStepList中的名字，设置treewidget中的项为真
                 // 遍历根节点
                 for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++) {
                     QTreeWidgetItem *rootItem = ui->treeWidget->topLevelItem(i);
                     setLeafNodeSelection(rootItem, checkStepList);
                 }


              }
          }
      }else{
          qDebug()<<"sql执行出错!";
    }
   }else{
       qDebug()<<"sql执行出错!";
    }
}

void editOptions::getId(QString newid){
       this->id = newid;
       handleItemSelected();
}

void editOptions::setLeafNodeSelection(QTreeWidgetItem *item, const QStringList &checkStepList) {
    if (item->childCount() == 0) {
        // 当前节点为叶子节点
        QString nodeName = item->text(0);
        if (checkStepList.contains(nodeName)) {
            item->setCheckState(0, Qt::Checked); // 设置选择状态为 true
        }else{
            item->setCheckState(0, Qt::Unchecked); // 设置选择状态为 true
        }
    } else {
        // 当前节点为父节点
        for (int i = 0; i < item->childCount(); i++) {
            setLeafNodeSelection(item->child(i), checkStepList); // 递归遍历子节点
        }
    }
}

