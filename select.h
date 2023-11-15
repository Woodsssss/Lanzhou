#ifndef SELECT_H
#define SELECT_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTableWidget>

namespace Ui {
    class Select;
}

class Select : public QWidget
{
    Q_OBJECT

public:
    explicit Select(QWidget *parent = nullptr);
    ~Select();

    void init();
    void updateParentItem(QTreeWidgetItem* item);
    void saveSelectedLeafItemsRecursive(QTreeWidgetItem* item);
    void traverseTree(QTreeWidgetItem* item);
signals:
    void windowClosed(); // 窗口关闭信号


public slots:   //申明信号与槽,当树形控件的子选项被改变时执行
    void onTreeItemChanged(QTreeWidgetItem* item, int column);


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();


private:
    Ui::Select *ui;
    QString itemText;
    int totalItemCount;
    int visitedItemCount;
    int flag;
};

#endif // SELECT_H
