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
    void detailInfor(QString result);
    void refresh();

signals:
    void windowClosed(); // 窗口关闭信号

private slots:
    void locate();

    void on_projects_clicked(const QModelIndex &index);

private:
    Ui::result *ui;
};

#endif // RESULT_H
