#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
// SQL 相关
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

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

private:
    Ui::Manager *ui;
    bool SortUporDown; // 排序规则
};

#endif // MANAGER_H
