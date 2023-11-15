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


private slots:
    void locate();

private:
    Ui::result *ui;
};

#endif // RESULT_H
