#include "login.h"
#include "ui_login.h"
#include <QDebug>

void Login::set_ui() {
    QFile qss_body(":/login.qss");
    qss_body.open(QFile::ReadOnly);
    QString qss = qss_body.readAll();
    qDebug() << qss << '\n';
    setStyleSheet(qss);

    QFile qss_btn(":/button.qss");
    qss_btn.open(QFile::ReadOnly);
    qss = qss_btn.readAll();
    ui->login->setStyleSheet(qss);
    ui->quit->setStyleSheet(qss);
    ui->signUp->setStyleSheet(qss);
}

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->pwdEdit->setEchoMode(QLineEdit::Password);
    setWindowTitle("入口菜单");
    set_ui();

    connect(ui->login, &QPushButton::clicked, this, &Login::try_login);
    connect(ui->quit, &QPushButton::clicked, this, &Login::close);
    connect(ui->signUp, &QPushButton::clicked, this, &Login::try_signUp);

    // https://blog.csdn.net/qq_43333395/article/details/91126477
    // 初始化数据库
    db = QSqlDatabase::addDatabase("QMYSQL"); // 选择数据库对象，这里使用mysql
    // 连接数据库
    // 用远程数据库会一直显示丢失连接，因此使用本地数据库

//    db.setHostName("121.40.57.214");
//    db.setPort(22000);
//    db.setDatabaseName("Chater");
//    db.setUserName("horb7");
//    db.setPassword("hsb2002");

    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("hsb2002");
    db.setDatabaseName("chatter");

    if (!db.open()) { // 打开数据库
        // 失败
        qDebug() << "数据库打开失败\n";
    } else {
        qDebug() << "数据库打开成功\n";
    }

    qDebug() << QSqlDatabase::drivers() << '\n';

}

void Login::try_login() {
    // 查看数据库是否存在用户
    QSqlQuery query;
    query.exec("select * from admins;");
    while(query.next()) { // 一行一行遍历查询到的数据
        QString username = query.value(0).toString();
        QString password = query.value(1).toString();
        if (username == ui->userEdit->text() &&
                password == ui->pwdEdit->text()) {
            // 查找到这个用户
            QMessageBox::information(this, "information", "登陆成功!", QMessageBox::Ok);
            return accept(); // 返回Accepted
        }
    }

    // 否则弹出提示框
    QMessageBox::warning(this, "错误", "您输入的用户名或密码错误", QMessageBox::Yes, QMessageBox::Cancel);
}

void Login::try_signUp() {
    if (signUpDialog == nullptr) {
        signUpDialog = new SignUp(this);
    }

    signUpDialog->clear();
    signUpDialog->db = this->db;

    // 运行注册模块(模式对话框形式)
    signUpDialog->exec();
}

Login::~Login()
{
    delete ui;
}
