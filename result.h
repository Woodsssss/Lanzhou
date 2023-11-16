#ifndef RESULT_H
#define RESULT_H

#include <QWidget>

namespace Ui {
class result;
}

class result : public QWidget
{
    Q_OBJECT

public:
    explicit result(QWidget *parent = nullptr);
    ~result();
    void show_table();
    int get_sql_row();
    void on_tableWidget_clicked(const QModelIndex &index);
    void refresh();

private:
    Ui::result *ui;
};

#endif // RESULT_H
