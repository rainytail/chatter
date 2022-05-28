/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Server
{
public:
    QAction *monitor;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralWidget;
    QTextBrowser *Chat;
    QTableWidget *Current;
    QLabel *CurrentLable;
    QLabel *TOOL;
    QToolButton *Color;
    QToolButton *Font;
    QToolButton *Bold;
    QToolButton *Italic;
    QTextEdit *SubmitEdit;
    QLabel *label;
    QLineEdit *user;
    QLineEdit *ip;
    QLineEdit *port;
    QPushButton *Submit;
    QPushButton *Clear;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Server)
    {
        if (Server->objectName().isEmpty())
            Server->setObjectName(QStringLiteral("Server"));
        Server->resize(1045, 802);
        Server->setWindowOpacity(0.95);
        Server->setStyleSheet(QStringLiteral(""));
        monitor = new QAction(Server);
        monitor->setObjectName(QStringLiteral("monitor"));
        action_2 = new QAction(Server);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(Server);
        action_3->setObjectName(QStringLiteral("action_3"));
        centralWidget = new QWidget(Server);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Chat = new QTextBrowser(centralWidget);
        Chat->setObjectName(QStringLiteral("Chat"));
        Chat->setGeometry(QRect(20, 10, 661, 441));
        Chat->setContextMenuPolicy(Qt::ActionsContextMenu);
        Chat->setFrameShape(QFrame::Box);
        Chat->setFrameShadow(QFrame::Sunken);
        Chat->setLineWidth(2);
        Current = new QTableWidget(centralWidget);
        Current->setObjectName(QStringLiteral("Current"));
        Current->setGeometry(QRect(700, 50, 271, 401));
        Current->setContextMenuPolicy(Qt::ActionsContextMenu);
        Current->setFrameShape(QFrame::WinPanel);
        Current->setFrameShadow(QFrame::Sunken);
        CurrentLable = new QLabel(centralWidget);
        CurrentLable->setObjectName(QStringLiteral("CurrentLable"));
        CurrentLable->setGeometry(QRect(701, 14, 101, 31));
        CurrentLable->setFrameShape(QFrame::StyledPanel);
        TOOL = new QLabel(centralWidget);
        TOOL->setObjectName(QStringLiteral("TOOL"));
        TOOL->setGeometry(QRect(20, 470, 91, 41));
        TOOL->setFrameShape(QFrame::StyledPanel);
        Color = new QToolButton(centralWidget);
        Color->setObjectName(QStringLiteral("Color"));
        Color->setGeometry(QRect(220, 470, 51, 41));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Color.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Color->setIcon(icon);
        Font = new QToolButton(centralWidget);
        Font->setObjectName(QStringLiteral("Font"));
        Font->setGeometry(QRect(300, 470, 51, 41));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/tty.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Font->setIcon(icon1);
        Bold = new QToolButton(centralWidget);
        Bold->setObjectName(QStringLiteral("Bold"));
        Bold->setGeometry(QRect(140, 470, 51, 41));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Bold.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Bold->setIcon(icon2);
        Italic = new QToolButton(centralWidget);
        Italic->setObjectName(QStringLiteral("Italic"));
        Italic->setGeometry(QRect(380, 470, 51, 41));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Italic.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Italic->setIcon(icon3);
        SubmitEdit = new QTextEdit(centralWidget);
        SubmitEdit->setObjectName(QStringLiteral("SubmitEdit"));
        SubmitEdit->setGeometry(QRect(20, 530, 661, 171));
        SubmitEdit->setFrameShape(QFrame::WinPanel);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(480, 470, 71, 41));
        label->setFrameShape(QFrame::StyledPanel);
        user = new QLineEdit(centralWidget);
        user->setObjectName(QStringLiteral("user"));
        user->setGeometry(QRect(570, 470, 113, 41));
        ip = new QLineEdit(centralWidget);
        ip->setObjectName(QStringLiteral("ip"));
        ip->setGeometry(QRect(700, 470, 113, 41));
        port = new QLineEdit(centralWidget);
        port->setObjectName(QStringLiteral("port"));
        port->setGeometry(QRect(830, 470, 113, 41));
        Submit = new QPushButton(centralWidget);
        Submit->setObjectName(QStringLiteral("Submit"));
        Submit->setGeometry(QRect(710, 550, 159, 41));
        Clear = new QPushButton(centralWidget);
        Clear->setObjectName(QStringLiteral("Clear"));
        Clear->setGeometry(QRect(710, 620, 159, 41));
        Server->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Server);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1045, 26));
        Server->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Server);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Server->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Server);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Server->setStatusBar(statusBar);

        retranslateUi(Server);

        QMetaObject::connectSlotsByName(Server);
    } // setupUi

    void retranslateUi(QMainWindow *Server)
    {
        Server->setWindowTitle(QApplication::translate("Server", "Server", Q_NULLPTR));
        monitor->setText(QApplication::translate("Server", "\345\274\200\345\220\257\347\233\221\345\220\254", Q_NULLPTR));
        action_2->setText(QApplication::translate("Server", "\345\205\263\351\227\255\347\233\221\345\220\254", Q_NULLPTR));
        action_3->setText(QApplication::translate("Server", "\345\205\250\345\221\230\347\246\201\350\250\200", Q_NULLPTR));
        CurrentLable->setText(QApplication::translate("Server", "\345\275\223\345\211\215\345\234\250\347\272\277\357\274\232", Q_NULLPTR));
        TOOL->setText(QApplication::translate("Server", "TOOL", Q_NULLPTR));
        Color->setText(QApplication::translate("Server", "...", Q_NULLPTR));
        Font->setText(QApplication::translate("Server", "...", Q_NULLPTR));
        Bold->setText(QApplication::translate("Server", "...", Q_NULLPTR));
        Italic->setText(QApplication::translate("Server", "...", Q_NULLPTR));
        SubmitEdit->setPlaceholderText(QApplication::translate("Server", "\346\255\244\345\244\204\350\276\223\345\205\245\345\217\221\351\200\201\347\232\204\344\277\241\346\201\257......", Q_NULLPTR));
        label->setText(QApplication::translate("Server", "\347\224\250\346\210\267", Q_NULLPTR));
        user->setPlaceholderText(QApplication::translate("Server", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        ip->setPlaceholderText(QApplication::translate("Server", "IP", Q_NULLPTR));
        port->setPlaceholderText(QApplication::translate("Server", "Port", Q_NULLPTR));
        Submit->setText(QApplication::translate("Server", "\345\217\221\351\200\201", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        Submit->setShortcut(QApplication::translate("Server", "Alt+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        Clear->setText(QApplication::translate("Server", "\346\270\205\351\231\244", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        Clear->setShortcut(QApplication::translate("Server", "Alt+L", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class Server: public Ui_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
