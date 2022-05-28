#include "signup.h"
#include "ui_signup.h"
#include <QDebug>

void SignUp::set_ui() {
    QFile btn(":/login.qss");
    btn.open(QFile::ReadOnly);
    QString qss = btn.readAll();
    setStyleSheet(qss);

    QFile qss_btn(":/button.qss");
    qss_btn.open(QFile::ReadOnly);
    qss = qss_btn.readAll();
    ui->signup->setStyleSheet(qss);
    ui->quit->setStyleSheet(qss);
}

void SignUp::clear() {
    ui->userEdit->clear();
    ui->pwdEdit->clear();
}

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
    ui->pwdEdit->setEchoMode(QLineEdit::Password);
    set_ui();

    connect(ui->signup, &QPushButton::clicked, this, &SignUp::try_get_new_account);
    connect(ui->quit, &QPushButton::clicked, this, &SignUp::close);
}

void SignUp::try_get_new_account() {
    // 注册用户,在数据库中加入即可
    qDebug() << "get new account\n";

    // 如果用户名或者密码没有填写
    if (ui->userEdit->text().isEmpty()) {
        QMessageBox::warning(this, "注册失败", "请填写用户名!", QMessageBox::Ok);
        return ;
    } else if (ui->pwdEdit->text().isEmpty()) {
        QMessageBox::warning(this, "注册失败", "请填写密码!", QMessageBox::Ok);
        return ;
    }

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
    query.exec("insert into admins(username, password) values(\"" + ui->userEdit->text()
               + "\", \"" + ui->pwdEdit->text() + "\")");
    this->close();
}

SignUp::~SignUp()
{
    delete ui;
}
