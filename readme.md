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

##### QTcpserver

| 函数\信号\槽                        | 参数         | 备注                               | 返回值           |
| ----------------------------------- | ------------ | ---------------------------------- | ---------------- |
| bool listen(QHostAddress, port)     | IP地址、端口 | IP地址为QString类，端口为short类   | 是否连接成功     |
| void newconnection()                | 无           | 槽函数，新的socket连接进来时会触发 | 无               |
| QTcpsocket *nextPendingConnection() | 无           | 获取连接进来的socket对象地址       | socket对象的地址 |

##### QTcpsocket

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



### QTextBrowser 实现每行不同风格文字

在本项目中，QTextBrowser用来打印所有的聊天信息，而不同的客户端会进行不同的个性化设置，这需要在聊天窗口得以体现。

再QTextBrowser中实现不同风格，有两种方式：

1. 由于在QTextBrowser中可以内嵌html元素，因此可以实现不同风格文字的打印。

2. 对QTextBrowser字体的任何修改，都是修改之后加入的信息，不会影响前面的信息，因此我们也可以直接对QTextBrowser进行设置。

#### 颜色不同

参考：https://blog.csdn.net/u010687717/article/details/101281121

使用 `<font>` 元素中的 `color` 属性即可设置。

![image-20220524221925436](D:\Horb7\QtWork\images\image-20220524221925436.png)

![image-20220524221945689](D:\Horb7\QtWork\images\image-20220524221945689.png)

这样我们还需要对数字进行16进制编码，比较麻烦，我们采用第二种方法。

注意QJson对象不能插入QColor对象，因此可以将三原色rgb用三个int对象插入到Json中，在解码时再转化为QColor即可。

![image-20220524223930289](D:\Horb7\QtWork\images\image-20220524223930289.png)

![image-20220524223937719](D:\Horb7\QtWork\images\image-20220524223937719.png)

#### 字体加粗

同样使用第二种方法，把字体设置为粗体。

由于QTextBrowser不存在直接设置粗体的方法，我们可以在类中定义字体的状态 `is_bold` 记录当前是否为粗体，在编码时插入到 QJson 中即可，然后在解码时，提取 QTextBrowser 的字体，改为粗体再将其设置为 QT而心痛Browser 的字体。

需要注意的是，由于 Server 端的消息也需要打印，而这时不需要解码，因此还要对其进行额外操作，在点击按钮时，设置粗体。

**但是，粗体在QTextBroswer中只能全体增加，而且 Html 标签的 Font 不存在设置粗体的属性，因此不能个性化设置。**