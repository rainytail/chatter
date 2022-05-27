#include "signup.h"
#include "ui_signup.h"
#include <QDebug>

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
    ui->pwdEdit->setEchoMode(QLineEdit::Password);

    connect(ui->signup, &QPushButton::clicked, this, &SignUp::try_get_new_account);
    connect(ui->quit, &QPushButton::clicked, this, &SignUp::close);
}

void SignUp::try_get_new_account() {
    // 注册用户,在数据库中加入即可
    qDebug() << "get new account\n";

    // 如果用户名已经存在，则不能注册
    QSqlQuery query;
    query.exec("select username, password from admins");
    while(query.next()) {
        QString username = query.value(0).toString();
        QString password = query.value(1).toString();
        if (ui->userEdit->text() == username) {
            QMessageBox::warning(this, "注册失败", "该用户名已经存在!", QMessageBox::Ok);
            return ;
        }
    }

    // 注册成功
    QMessageBox::information(this, "注册成功", "恭喜你注册成功!");
    query.exec("insert into admins(username, password) values(" + ui->userEdit->text()
               + ", " + ui->pwdEdit->text() + ")");
    this->close();
}

SignUp::~SignUp()
{
    delete ui;
}
