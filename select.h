#ifndef SELECT_H
#define SELECT_H

#include <QWidget>

namespace Ui {
class Select;
}

class Select : public QWidget
{
    Q_OBJECT

public:
    explicit Select(QWidget *parent = nullptr);
    ~Select();
    void addItem();
    void removeItem();

private:
    Ui::Select *ui;
};

#endif // SELECT_H
