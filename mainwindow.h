#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include "user.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "manager.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_LoginButton_2_clicked();

    void on_remitButton_2_clicked();

signals:
    void sendData(QString);
private:
    Ui::MainWindow *ui;
    User *u;
    Manager *m;
};

#endif // MAINWINDOW_H
