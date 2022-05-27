#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include "signup.h"
#include <QPainter>
#include <QFile>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    void set_ui();

    QSqlDatabase db;

    SignUp *signUpDialog = nullptr;

private:
    Ui::Login *ui;


public slots:
    void try_login();
    void try_signUp();

};

#endif // LOGIN_H
