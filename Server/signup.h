#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = 0);
    ~SignUp();

    QSqlDatabase db; // 数据库结构，与login相同

private:
    Ui::SignUp *ui;

public slots:
    void try_get_new_account();
};

#endif // SIGNUP_H
