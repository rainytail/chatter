#include "server.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server w;
    Login login;
    // 先登录，等待输入正确
    if (login.exec() == QDialog::Accepted) {
        w.show();
        return a.exec();
    } else return 0;
}
