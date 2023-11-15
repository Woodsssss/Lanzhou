#ifndef EDITOPTIONS_H
#define EDITOPTIONS_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTableWidget>
#include "user.h"

namespace Ui {
    class editOptions;
}

class editOptions : public QWidget
{
    Q_OBJECT

public:
    explicit editOptions(QWidget *parent = nullptr);
    ~editOptions();
    void init();
    void updateParentItem(QTreeWidgetItem* item);
    void saveSelectedLeafItemsRecursive(QTreeWidgetItem* item);
    void traverseTree(QTreeWidgetItem* item);
    void getId(QString  id);
    void handleItemSelected();//处理接收到的选择项函数
    static void setLeafNodeSelection(QTreeWidgetItem *item, const QStringList &checkStepList);

signals:
    void windowClosed(); // 窗口关闭信号

public slots:   //申明信号与槽,当树形控件的子选项被改变时执行
    void onTreeItemChanged(QTreeWidgetItem* item, int column);


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::editOptions *ui;
    QString itemText;
    int totalItemCount;
    int visitedItemCount;
    int flag;
    QString id;
};

#endif // EDITOPTIONS_H
