#ifndef USER_H
#define USER_H
#include"select.h"

#include <QMainWindow>

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

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_button_insert_clicked();

    void on_button_exit_clicked();

private:
    Ui::User *ui;
    Select *select;
};

#endif // USER_H
