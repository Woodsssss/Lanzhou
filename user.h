#ifndef USER_H
#define USER_H
#include"editoptions.h"
#include"select.h"
#include"result.h"

#include <QMainWindow>
class editOptions;
class result;

namespace Ui {
    class User;
}

class User : public QMainWindow
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = nullptr);
    ~User();
    void show_table();
    int get_sql_row();
    int get_sql_row2();
    void setSteps(QString str);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_button_insert_clicked();

    void on_button_exit_clicked();

    void refresh();

    void on_button_change_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

private:
    Ui::User *ui;
    Select *select;
    editOptions *edit;
    result *Result;
    bool check1;
        bool check2;
        bool check3;
        bool check4;
        bool check5;
        bool check6;
        QTreeWidgetItem* existingParent1;
        QTreeWidgetItem* existingParent2;
        QTreeWidgetItem* existingParent3;
        QTreeWidgetItem* existingParent4;
        QTreeWidgetItem* existingParent5;
        QTreeWidgetItem* existingParent6;
};

#endif // USER_H
