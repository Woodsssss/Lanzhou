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
    void show_table();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_button_exit_clicked();

private:
    Ui::Manager *ui;
    bool SortUporDown; // 排序规则
};

#endif // MANAGER_H
