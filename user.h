#ifndef USER_H
#define USER_H

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

private:
    Ui::User *ui;
};

#endif // USER_H