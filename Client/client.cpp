#include "client.h"
#include "ui_client.h"
#include <QDebug>

void Client::set_menus() {
    server_menu = menuBar()->addMenu("服务器");
    conn = new QAction("连接", this);
    conn->setShortcut(QKeySequence("Alt+O"));
    server_menu->addAction(conn);
    disconn = new QAction("断开连接", this);
    disconn->setShortcut(QKeySequence("Alt+E"));
    server_menu->addAction(disconn);

    disconn->setEnabled(false);

    connect(conn, &QAction::triggered, this, &Client::linkToServer);
    connect(disconn, &QAction::triggered, this, &Client::disconnctToServer);
}

void Client::show_msg() {
    qDebug() << "进入了show_msg\n";
    decode(socket->readAll()); // 将二进制的Json读取出来并显示出来
}

/*
 * 完成工具项
 */

void Client::chooseColor() {
    QColor color = QColorDialog::getColor();
    ui->Chat->setTextColor(color);
}

void Client::chooseBold() {
    is_bold = !is_bold;
    QFont font = ui->Chat->font();
    font.setBold(is_bold);
    ui->Chat->setFont(font);
}

void Client::chooseFontFamily() {
    bool ok = false;
    QFont sel = QFontDialog::getFont(&ok);
    if (ok) {
        font = sel;
        ui->Chat->setFont(font);
    }
}

QByteArray Client::encode(const QString &user, const QString &msg) {
    QJsonObject json;
    json.insert("user", user);
    json.insert("message", msg);
    json.insert("font color r", ui->Chat->textColor().red());
    json.insert("font color g", ui->Chat->textColor().green());
    json.insert("font color b", ui->Chat->textColor().blue());

    QJsonDocument doc;
    doc.setObject(json);
    return doc.toJson();
}

void Client::decode(const QByteArray &Info) {
    QJsonParseError error; // Json文档的检错机制
    // https://blog.csdn.net/dengjin20104042056/article/details/102728686
    QJsonDocument doc = QJsonDocument::fromJson(Info, &error);

    if (doc.isNull() || error.error != QJsonParseError::NoError) {
        qDebug() << error.errorString() << '\n';
    } else {
        // 从Json文档中提取出Json对象
        QJsonObject json = doc.object();
        QString user = json.value("user").toString();
        QString message = json.value("message").toString();
        int color_r = json.value("font color r").toInt();
        int color_g = json.value("font color g").toInt();
        int color_b = json.value("font color b").toInt();
        ui->Chat->setTextColor(QColor(color_r, color_g, color_b));
        QTime nowTime = QTime::currentTime();
        QString now_time = nowTime.toString("hh:mm:ss ap");
        ui->Chat->append(now_time + " " + (user + ":\n" + message).toUtf8() + "\n");
        qDebug() << "decode\n";
    }
}

void Client::linkToServer() {
//    qDebug() << "link\n";
    if (ui->user->text().isEmpty()) {
        qDebug() << "username\n";
    } else {
        // 与服务器进行连接
        qDebug() << "start\n";
        socket->connectToHost(QHostAddress(ui->ip->text()), ui->port->text().toShort());
        qDebug() << "end\n";

        // 检查state，是否真正连接上了
        if (socket->state() == QTcpSocket::UnconnectedState) {
            // 连接失败
            qDebug() << "not link\n";
        } else {
            // 连接成功
            qDebug() << "linked\n";
            statusBar()->showMessage("连接成功", 2000);
        }
        connect(socket, &QTcpSocket::readyRead, this, &Client::show_msg, Qt::UniqueConnection);
        socket->write(encode(ui->user->text(), tr("大家好")));

        conn->setEnabled(false);
        disconn->setEnabled(true);
    }
}

void Client::disconnctToServer() {
    socket->disconnectFromHost();
    ui->Chat->clear();
    statusBar()->showMessage("您已断开连接", 2000);
    conn->setEnabled(true);
    disconn->setEnabled(false);
    socket->close();
}

void Client::send() {
    // 把发送的信息放进socket中，传输给服务器
    // 注意socket->write方法只能传二进制流，需要编码变成二进制流
    socket->write(encode(ui->user->text(), ui->submitEdit->toPlainText().toUtf8()));
//    qDebug() << "ui submit edit " << ui->submitEdit->toPlainText().toUtf8() << '\n';
    ui->submitEdit->clear();
}

void Client::clear() {
    ui->submitEdit->clear();
}

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    this->setWindowTitle("简易网络聊天室(客户端)");
    this->setWindowIcon(QIcon(":/Icon_client.jpg"));
    set_menus();


    socket = new QTcpSocket(this);

    connect(ui->submit, &QPushButton::clicked, this, &Client::send);
    connect(ui->clear, &QPushButton::clicked, this, &Client::clear);
    connect(ui->leave, &QPushButton::clicked, this, &Client::close);
    connect(ui->Color, &QToolButton::clicked, this, &Client::chooseColor); // 选择颜色
    connect(ui->bold, &QToolButton::clicked, this, &Client::chooseBold);
    connect(ui->font, &QToolButton::clicked, this, &Client::chooseFontFamily);

    // 测试
    ui->user->setText("服务端");
    ui->ip->setText("10.1.1.144");
    ui->port->setText("1289");
}

Client::~Client()
{
    delete ui;
}
