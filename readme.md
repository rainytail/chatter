# chatter 设计报告

## 介绍

一个简单的网络聊天室工具，能够进行服务端与客户端的通信。

利用数据库完成用户的登录与注册等，但由于时间问题，目前只有服务端有，客户端只提供基础的连接通信功能。但两者的代码实现是相同的。

分三个模块介绍，分别为通信模块、数据库模块和UI模块。

## 目录结构

![image-20220528111440647](D:\Horb7\QtWork\images\image-20220528111440647.png)



该工具由两个QT项目组成，分别为 Server(服务端) 和 Client(客户端) 。

## 操作

### 通信连接

运行 Server 和 Client ，对于 Server，登录后(若没有账号则进行注册)，点击菜单栏项 "服务器" 的 "开启监听"；对于 Client，点击菜单栏项 "服务器" 的 "连接" ，然后即可进行通信。

### 快捷键

#### Server:Login

| 备注 | Widget      | ObjectName | QKeySequence |
| ---- | ----------- | ---------- | ------------ |
| 登录 | QPushButton | login      | Alt + return |
| 退出 | QpushButton | quit       | Alt + Q      |
| 注册 | QpushButton | signUp     | Alt + S      |

#### Server:SignUp

| 备注 | Widget      | ObjectName | QKeySequence |
| ---- | ----------- | ---------- | ------------ |
| 注册 | QPushButton | signup     | Alt + return |
| 退出 | QPushButton | quit       | Alt + Q      |

#### Server/Client

| 备注              | Widget      | ObjectName          | QKeySequence |
| ----------------- | ----------- | ------------------- | ------------ |
| 发送              | QPushButton | Submit              | Alt + S      |
| 清除              | QPushButton | Clear               | Alt + L      |
| 开启监听/连接     | QAction     | start_monitor/conn  | Alt + O      |
| 结束监听/断开连接 | QAction     | end_monitor/disconn | Alt + E      |

## 具体设计

### 通信模块

主要用到了 Qt tcp socket 通信编程。

这篇讲的很好：https://www.jianshu.com/p/066d99da7cbd

下面罗列我整理的相关函数或槽、信号等，以及一些浅薄的认知。下面统一把 QTcpsocket 称作 socket。

#### QTcpserver

| 函数\信号\槽                        | 参数         | 备注                               | 返回值           |
| ----------------------------------- | ------------ | ---------------------------------- | ---------------- |
| bool listen(QHostAddress, port)     | IP地址、端口 | IP地址为QString类，端口为short类   | 是否连接成功     |
| void newconnection()                | 无           | 槽函数，新的socket连接进来时会触发 | 无               |
| QTcpsocket *nextPendingConnection() | 无           | 获取连接进来的socket对象地址       | socket对象的地址 |

#### QTcpsocket

| 函数\信号\槽                           | 参数             | 备注                             | 返回值               |
| -------------------------------------- | ---------------- | -------------------------------- | -------------------- |
| void connectToHost(QHostAddress, port) | IP地址、端口     | IP地址为QString类，端口为short类 | 无                   |
| void disconnectFromHost()              | 无               | 断开此socket的连接               | 无                   |
| SocketState state()                    | 无               | socket类内函数                   | 返回当前socket的状态 |
| void disconnect()                      | 无               | 信号，表示该socket断开连接       | 无                   |
| void readyRead()                       | 无               | 信号，该socket内存有数据         | 无                   |
| qint64 write(QByteArray)               | 字节流QByteArray | 向该socket存进去数据             | 存进去数据的大小     |

由上可以得出该通信模块的具体操作流程：

+ 在服务端创建QTcpserver来建立TCP连接，监听本地 `1289` 端口。
+ 在客户端创建socket，同样连接至本地 `1289` 端口，QTcpserver触发newconnection槽函数，将该socket存储起来。
+ 客户端发送信息后，触发socket的readyRead信号；或者服务端发送信息后：服务端对所有socket写入对应的信息，同时将其打印到自己的屏幕上。

##### 问题

服务端对socket进行信息写入时，只能写入QByteArray字节流，如何将发送的QString类转换成字节流？

使用QJson对象，当发送信息时，将当前信息存入到QJson对象中，打包成QJson文档，将QJson文档转化为QByteArray即可。

这样有一个好处，就是不仅能传输发送的信息，还能传入其他设置的信息，比如设置字体的颜色。

当客户端的socket中存储了信息后，触发readyRead信号，将QJson文档解析为QJson对象，然后将对象内存储的数据取出来打印到自己的屏幕上。

QJson介绍：https://blog.csdn.net/foxgod/article/details/90407960

![image-20220528143548328](D:\Horb7\QtWork\images\image-20220528143548328.png)



给出服务端和客户端的头文件：

#### 服务端

```c++
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
#include <QTime>

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
    void start_listen(); // 开启监听
    void end_listen(); // 结束监听
    void tackle_sockets(); // 处理newconnection
    void socket_read(); // 处理readyRead
    void socket_disconnect(); // 处理 disconnect
    void send(); // 发送信息
    void clear(); // 清除信息
    void moveOne(); // 移除某个用户

    // 工具类
    void chooseColor();
    void chooseBold();
    void chooseFontFamily();


private:
    Ui::Server *ui;
};

#endif // SERVER_H

```

#### 客户端

```c++
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
#include <QTime>

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

```





### 数据库模块

参考：https://blog.csdn.net/qq_43333395/article/details/91126477

使用数据库进行用户的登录和注册，由于时间关系只做了Server(服务端)的模块。

这里我使用的数据库为 MySql，本来想连接到远程服务器的数据库，但是一直显示丢失连接，然后就用了本地的数据库。

**注意**：因为Qt没有提供64位的版本，因此必须要使用32位的MySql，否则无法启动MySql驱动。具体看这里：https://blog.csdn.net/weixin_43343803/article/details/97102028

在Login和SignUp界面使用数据库模块。

注意在使用数据库模块前需要先创建对应的数据库和表格，为了方便可以添加一些初始数据，这些可以使用MySql语言创建，也可以在Qt中创建。

![image-20220528123941466](D:\Horb7\QtWork\images\image-20220528123941466.png)

**初始数据:**

![image-20220528124006149](D:\Horb7\QtWork\images\image-20220528124006149.png)

**测试登录功能:**

![image-20220528124051083](D:\Horb7\QtWork\images\image-20220528124051083.png)

**测试注册功能：**

注册成功：

![image-20220528124140906](D:\Horb7\QtWork\images\image-20220528124140906.png)

![image-20220528125133140](D:\Horb7\QtWork\images\image-20220528125133140.png)



注册失败：

![image-20220528125202073](D:\Horb7\QtWork\images\image-20220528125202073.png)

![image-20220528125215340](D:\Horb7\QtWork\images\image-20220528125215340.png)



### UI模块

UI模块主要由各部件本身的代码设计和QSS文件设计组成。

##### 部件设计

###### 状态栏

在服务端，使用QLabel放置在状态栏上，用来显示当前聊天室内的人数。

同时，设置永久信息来显示chatter的信息。

在客户端，状态栏用来显示当前的状态，如：输入信息为空时，不能输出到socket中。

###### QTabelWidget

放置在服务端，用来显示当前聊天室的人数，以及登录人员的具体信息(用户名+IP地址)。

QTabelWidget详解：http://c.biancheng.net/view/9419.html

###### 工具项

工具项主要由字体加粗，选择字体颜色，选择字体等按钮实现，表现在QTextBrowser中。

###### QTextBrowser

这个是聊天界面，显示服务端与各客户端的所有发出的信息。

由于QTextBrowser设置字体颜色是不会改变整体的，所以可以显示各个不同客户端的个性化设置。

在QTextBrowser中实现不同风格，有两种方式：

1. 由于在QTextBrowser中可以内嵌html元素，因此可以实现不同风格文字的打印。

2. 对QTextBrowser字体的任何修改，都是修改之后加入的信息，不会影响前面的信息，因此我们也可以直接对QTextBrowser进行设置。



**颜色不同**

参考：https://blog.csdn.net/u010687717/article/details/101281121

使用 `<font>` 元素中的 `color` 属性即可设置。

![image-20220524221925436](D:\Horb7\QtWork\images\image-20220524221925436.png)

![image-20220524221945689](D:\Horb7\QtWork\images\image-20220524221945689.png)

这样我们还需要对数字进行16进制编码，比较麻烦，我们采用第二种方法。

注意QJson对象不能插入QColor对象，因此可以将三原色rgb用三个int对象插入到Json中，在解码时再转化为QColor即可。

![image-20220524223930289](D:\Horb7\QtWork\images\image-20220524223930289.png)

![image-20220524223937719](D:\Horb7\QtWork\images\image-20220524223937719.png)



**字体加粗**

同样使用第二种方法，把字体设置为粗体。

由于QTextBrowser不存在直接设置粗体的方法，我们可以在类中定义字体的状态 `is_bold` 记录当前是否为粗体，在编码时插入到 QJson 中即可，然后在解码时，提取 QTextBrowser 的字体，改为粗体再将其设置为 QTextBrowser 的字体。

需要注意的是，由于 Server 端的消息也需要打印，而这时不需要解码，因此还要对其进行额外操作，在点击按钮时，设置粗体。

**但是，粗体在QTextBrowser中只能全体增加，而且 Html 标签的 Font 不存在设置粗体的属性，因此不能个性化设置。**



**字体选择**

字体选择与字体选择类似，同样也不能个性化设置，更改后会影响整个QTextBrowser的字体。



##### QSS文件设计

QSS即QT Style Sheet，中文名Qt样式表，可以实现QT部件的样式美化，与CSS类似，但没有CSS强大，功能较少。

官方文档：https://doc.qt.io/qt-5/stylesheet-reference.html#border-style

在chatter中，对Login、SignUp和Server界面进行美化，主要是一些比较简单的美化，比如将QPushButton设置圆角等。

以 QPushButton 的QSS文件为例：

```css
QPushButton {
    background: #0088CC;
    color: #fff;
    border-style: outset;
    border-radius: 10px;
}

QPushButton:pressed {
    background-color: #49afcd;
    color: #dedede;
    border-style: inset;
}

QPushButton:hover {
    background-color: #49afcd;
    border-color: #5599ff;
}
```



## 总结

这次的QT大作业只是完成了部分网络聊天室的功能，还有部分比如踢出群聊，保存历史聊天记录等功能没有完成。

由于时间比较紧迫，导致代码写起来比较乱，而且只完善了服务端，客户端还有很多可以完善。有些地方可以写的更简洁或者拆分成多个模块来完成。

不过这次也学习了很多知识，也更好地了解了面向对象编程，希望以后有时间的话可以再改进一些地方。

![image-20220528153446436](D:\Horb7\QtWork\images\image-20220528153446436.png)