#ifndef SERVER_H
#define SERVER_H

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
#include <QAbstractItemView>
#include <QColorDialog>
#include <QFontDialog>
#include <QFile>

namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

    void show_msg(const QString &msg);

    QByteArray encode(const QString &user, const QString &msg); // 对数据进行编码形成Json文件
    void decode(const QByteArray &Info); // 对Json进行解析并应用

    void init_server(); // 建立TCPserver连接
    void close_server(); // 关闭TCPserver连接

    void set_status(); // 设计状态栏
    void set_menus(); // 设计菜单
    void set_ui(); // ui美化

    void set_table_widget(); // 设计teble_widget

    void set_curList(); // 设计curList的菜单


public:
    int numbers = 0; // 记录当前按在线人数
    QString user, message; // 解析出来的上一条信息

    // 一些需要的部件

    // menus
    QMenu *server_menu;

    // Actions
    QAction *start_monitor;
    QAction *end_monitor;

    // curList的菜单项
    QAction *move;

    // Status-Bar
    QLabel *status_label;

    QTcpServer *server; // server用来监听端口，获取tcp连接的描述符
    QList<QTcpSocket*> recv; // 接收到的socket对象


    // 文字状态
    bool is_bold = false;
    bool is_italic = false;
    QFont font; // 字体

public slots:
    void start_listen();
    void end_listen();
    void tackle_sockets();
    void socket_read();
    void socket_disconnect();
    void send();
    void clear();
    void moveOne();

    // 工具类
    void chooseColor();
    void chooseBold();
    void chooseFontFamily();


private:
    Ui::Server *ui;
};

#endif // SERVER_H
