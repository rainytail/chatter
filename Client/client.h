#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QLabel>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>
#include <QAction>
#include <QFontDialog>
#include <QColorDialog>

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();
    void set_menus(); // 设计菜单栏
    QByteArray encode(const QString &user, const QString &msg); // 为发送的信息编码
    void decode(const QByteArray &Info);

    QTcpSocket *socket; // 客户端建立套接字

    // Menus
    QMenu *server_menu;

    // Actions
    QAction *conn;
    QAction *disconn;

    // 文字状态
    bool is_bold = false;
    bool is_italic = false;
    QFont font; // 字体

public slots:
    void send(); // 发送信息
    void clear(); // 清除信息
    void linkToServer(); // 连接到服务器
    void disconnctToServer(); // 断开连接
    void show_msg(); // 把接受的信息打印在textbrowser上

    // 工具项
    void chooseColor();
    void chooseBold();
    void chooseFontFamily();


private:
    Ui::Client *ui;
};

#endif // CLIENT_H
