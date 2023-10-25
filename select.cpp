#include "select.h"
#include "ui_select.h"
#include <QListWidget>
#include <QPushButton>

Select::Select(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Select)
{
    ui->setupUi(this);

// 将所有可选择的选项添加到左边的列表
ui->availableListWidget->addItem("Option 1");
ui->availableListWidget->addItem("Option 2");
ui->availableListWidget->addItem("Option 3");

// 连接“添加”按钮的点击事件到槽函数
connect(ui->addButton, &QPushButton::clicked, this, &Select::addItem);
// 连接“删除”按钮的点击事件到槽函数
connect(ui->removeButton, &QPushButton::clicked, this, &Select::removeItem);
}


// 编写槽函数，以在点击“添加”按钮时将选定的选项从左边的列表移动到右边的列表
void Select::addItem() {
    QListWidgetItem* selectedItem = ui->availableListWidget->currentItem();
    if (selectedItem) {
        ui->availableListWidget->takeItem(ui->availableListWidget->row(selectedItem));
        ui->selectedListWidget->addItem(selectedItem->text());
    }
}

// 编写槽函数，以在点击“删除”按钮时将选定的选项从右边的列表移动回左边的列表
void Select::removeItem() {
    QListWidgetItem* selectedItem = ui->selectedListWidget->currentItem();
    if (selectedItem) {
        ui->selectedListWidget->takeItem(ui->selectedListWidget->row(selectedItem));
        ui->availableListWidget->addItem(selectedItem->text());
    }
}

Select::~Select()
{
    delete ui;
}
