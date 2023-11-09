#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
// SQL 相关
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include"select.h"

namespace Ui {
class Manager;
}

class Manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = nullptr);
    ~Manager();
    int get_sql_row();
    int get_sql_row2();
    int get_sql_row3();
    void show_table();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_button_exit_clicked();

    void on_button_insert_clicked();

    void on_button_delete_clicked();

    void on_pushButton_3_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_button_exit_2_clicked();

    void on_tableWidget_2_clicked(const QModelIndex &index);

    void on_button_delete_2_clicked();

    void locate();

    void locate_2();

    void locate_3();

    void on_pushButton_4_clicked();

    void on_button_exit_3_clicked();

    void on_tableWidget_3_clicked(const QModelIndex &index);

    void on_button_delete_3_clicked();

    void refresh();

    void on_button_insert_4_clicked();


private:
    Ui::Manager *ui;
    Select *select;
};

#endif // MANAGER_H
