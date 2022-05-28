#include "server.h"
#include "ui_server.h"
#include <QDebug>

void Server::set_status() {
    // 状态栏，临时信息：当前人数，禁言情况；永久信息：聊天室信息
    status_label = new QLabel(this->statusBar());
    status_label->setText("当前在线人数: 0");
    statusBar()->addWidget(status_label);

    QLabel *permanent = new QLabel("简易聊天室", this);
    statusBar()->addPermanentWidget(permanent);
}

void Server::set_menus() {
    server_menu = menuBar()->addMenu("服务器");
    start_monitor = new QAction("开启监听", this);
    start_monitor->setShortcut(QKeySequence("Alt+O"));
    end_monitor = new QAction("结束监听", this);
    end_monitor->setShortcut(QKeySequence("Alt+E"));

    server_menu->addAction(start_monitor);
    server_menu->addAction(end_monitor);

    end_monitor->setEnabled(false);
}

void Server::set_table_widget() {
    // 两个属性列
    ui->Current->setColumnCount(2);
    // 设置表头
    ui->Current->setHorizontalHeaderLabels(QStringList() << "用户" << "ip");
    // 设置不可被编辑
    ui->Current->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Server::set_ui() {
    QFile qss_body(":/server.qss");
    qss_body.open(QFile::ReadOnly);
    QString qss = qss_body.readAll();
    qDebug() << "in server ui qss: " << qss << '\n';
    setStyleSheet(qss);

    //button
    QFile qss_btn(":/button.qss");
    qss_btn.open(QFile::ReadOnly);
    qss = qss_btn.readAll();
    ui->Submit->setStyleSheet(qss);
    ui->Clear->setStyleSheet(qss);
}

void Server::moveOne() {
    // Pass
}

void Server::set_curList() {
    move = new QAction("移除群聊", this);
    ui->CurrentLable->addAction(move);
    connect(move, &QAction::triggered, this, &Server::moveOne);
}

/*
 * 这里用来处理各个工具类按钮的功能
 */

void Server::chooseColor() {
    QColor choosed = QColorDialog::getColor();
    qDebug() << "choose " << choosed << '\n';
    ui->Chat->setTextColor(choosed);
}

void Server::chooseBold() {
    is_bold = !is_bold;
    QFont font = ui->Chat->font();
    font.setBold(is_bold);
    ui->Chat->setFont(font);
    qDebug() << is_bold << '\n';
}

void Server::chooseFontFamily() {
    bool ok = false;
    QFont sel = QFontDialog::getFont(&ok);
    if (ok) {
        font = sel;
        ui->Chat->setFont(font);
    }
}

// 根据用户和信息，编码为对应的Json文件
QByteArray Server::encode(const QString &user, const QString &msg) {
    // 创建json对象
    QJsonObject json;
    json.insert("user", user);
    json.insert("message", msg);
    json.insert("font color r", ui->Chat->textColor().red());
    json.insert("font color g", ui->Chat->textColor().green());
    json.insert("font color b", ui->Chat->textColor().blue());
    json.insert("font bold", is_bold);
    json.insert("font family", font.family());

    // 构建json文档
    QJsonDocument doc;
    doc.setObject(json);
    return doc.toJson(); // 转化为二进制数据
}

void Server::decode(const QByteArray &Info) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(Info, &error);
    if (doc.isNull() || error.error != QJsonParseError::NoError) {
        qDebug() << "In decode Error\n";
    } else {
        QJsonObject json = doc.object();
        user = json.value("user").toString();
        message = json.value("message").toString();
        int color_r = json.value("font color r").toInt();
        int color_g = json.value("font color g").toInt();
        int color_b = json.value("font color b").toInt();
        QFont font = ui->Chat->font();
        font.setBold(true);
        font.setFamily(json.value("font family").toString());
        ui->Chat->setFont(font);
        qDebug() << "now char font bold " << ui->Chat->font().bold() << '\n';
        ui->Chat->setTextColor(QColor(color_r, color_g, color_b));
    }
}

void Server::show_msg(const QString &msg) {
    QTime nowTime = QTime::currentTime();
    QString now_time = nowTime.toString("hh:mm:ss ap");
//    qDebug() << now_time << '\n';

    // 将信息打印在textBrowser上
    ui->Chat->append(now_time + " " + msg + "\n");
}

void Server::socket_read() {
    // 作为服务端，需要处理的事件
    int cur_pos = 0;
    // 获取发送信息的客户端对象
    QTcpSocket *socket = qobject_cast<QTcpSocket*> (QObject::sender());
    decode(socket->readAll());
    // 给自己显示
    show_msg((user + ":\n" + message).toUtf8());
    // 传输给客户端
    for (auto socket: recv) {
        socket->write(encode(user, message));
        // 这里需要加入等待时间，否则可能会和下面的write混合，导致两个文档合在一起，错误：garbage at the end of document
        // 具体原理不太懂，先这么理解
        // 现在好像又不行了QAQ
        socket->waitForBytesWritten(20000);
        socket->flush();
    }

    // 遍历current列表
    for (; cur_pos < ui->Current->rowCount(); cur_pos ++ ) {
        // 如果当前用户和列表用户ip地址相同
        if (socket->peerAddress().toString() == ui->Current->item(cur_pos, 1)->text()) {
//            break;
            QString old_user = ui->Current->item(cur_pos, 0)->text();
            if (user != old_user) {
                for (auto socket : recv) {
                    socket->write(encode(old_user, QString::fromUtf8("改名为: ") + user));
                }
                show_msg((old_user + QString::fromUtf8(" 改名为: ") + user).toUtf8());
                ui->Current->item(cur_pos, 0)->setText(user);
            }
            break;
        }
    }

    // 如果是用户不在current列表中出现，加入到current列表中
    if (cur_pos == ui->Current->rowCount()) {
        ui->Current->setRowCount(numbers + 1);
        QTableWidgetItem *user_item = new QTableWidgetItem(user);
        QTableWidgetItem *ip_item = new QTableWidgetItem(socket->peerAddress().toString());
        ui->Current->setItem(numbers, 0, user_item);
        ui->Current->setItem(numbers, 1, ip_item);
        numbers ++ ;
        status_label->setText(tr("当前%1人在线").arg(numbers));
    }
}

void Server::socket_disconnect() {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(QObject::sender());
    recv.removeOne(socket);
    // 更新current列表
    for (int c = 0; c < ui->Current->rowCount(); c ++ ) {
        if (ui->Current->item(c, 1)->text() == socket->peerAddress().toString()) {
            show_msg(ui->Current->item(c, 0)->text() + "断开了连接");
            for (auto socket: recv) {
                socket->write(encode(ui->Current->item(c, 0)->text(), "断开了连接"));
                socket->waitForBytesWritten(10000);
                socket->flush();
            }
            delete ui->Current->item(c, 0);
            delete ui->Current->item(c, 1);
            ui->Current->removeRow(c);
            numbers -- ;
        }
    }
}


void Server::tackle_sockets() {
    // 获取下一条socket信息
    QTcpSocket *socket = server->nextPendingConnection();
    // 处理新的连接，加入socket
    recv << socket;
    // 信息有传输和断开连接，分别建立槽函数
    connect(socket, &QTcpSocket::readyRead, this, &Server::socket_read);
    connect(socket, &QTcpSocket::disconnected, this, &Server::socket_disconnect);
    qDebug() << "连接了一个客户端\n";
}

void Server::send() {
    if (ui->SubmitEdit->toPlainText() == "") {
        statusBar()->showMessage("请不要说\"空话\"哦", 2000);
        return ;
    }
    qDebug() << "recv size " << recv.size() << '\n';
    for (auto socket: recv) {
        // 将user和submitEdit内容编码，发送给客户端
        socket->write(encode(ui->user->text(), ui->SubmitEdit->toPlainText().toUtf8()));
    }
    // 同时服务端也要有消息显示
    show_msg(ui->user->text() + QString::fromUtf8(":\n") + ui->SubmitEdit->toPlainText());
    ui->SubmitEdit->clear();
}

void Server::clear() {
    ui->SubmitEdit->clear();
}

void Server::start_listen() {
    server = new QTcpServer(this); // 建立tcp连接

    // 开启监听，需要给出ip和port
    server->listen(QHostAddress(ui->ip->text()), ui->port->text().toUShort());

    connect(server, &QTcpServer::newConnection, this, &Server::tackle_sockets);
    start_monitor->setEnabled(false);
    end_monitor->setEnabled(true);
}

void Server::end_listen() {
    server->close();
    start_monitor->setEnabled(true);
    end_monitor->setEnabled(false);
}

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("简易网络聊天室"));
    this->setWindowIcon(QIcon(":/Icon_server.jpg"));
    set_status();
    set_menus();
    set_table_widget();
    set_curList();
    set_ui();

    connect(start_monitor, &QAction::triggered, this, &Server::start_listen);
    connect(end_monitor, &QAction::triggered, this, &Server::end_listen);
    connect(ui->Submit, &QPushButton::clicked, this, &Server::send); // 发送数据
    connect(ui->Clear, &QPushButton::clicked, this, &Server::clear); // 清除数据
    connect(ui->Color, &QToolButton::clicked, this, &Server::chooseColor); // 选择颜色
    connect(ui->Bold, &QToolButton::clicked, this, &Server::chooseBold); // 选择是否粗体
    connect(ui->Font, &QToolButton::clicked, this, &Server::chooseFontFamily); // 选择字体

    // 测试
    ui->user->setText("服务端");
    ui->ip->setText("10.1.1.144");
    ui->port->setText("1289");

    // 测试将QTextBroser里的文字改成每行颜色不同
//    ui->Chat->append("<font color = \"#FF0000\">" + QString("这是一个红色字体") + "<font>");
//    ui->Chat->append("<font color = \"#00FF00\">" + QString("这是一个绿色字体") + "<font>");
//    ui->Chat->append("<font color = \"#0000FF\">" + QString("这是一个蓝色字体") + "<font>");

    // 测试粗体
//    QFont font = ui->Chat->font();
//    font.setBold(true);
//    ui->Chat->setFont(font);
}

Server::~Server()
{
    delete ui;
}
