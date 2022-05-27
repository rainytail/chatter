/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

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
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QAction *action;
    QWidget *centralWidget;
    QTextBrowser *Chat;
    QLabel *label_2;
    QToolButton *bold;
    QToolButton *Color;
    QToolButton *font;
    QToolButton *toolButton_4;
    QTextEdit *submitEdit;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *submit;
    QPushButton *clear;
    QPushButton *leave;
    QLabel *label_5;
    QLineEdit *user;
    QLineEdit *ip;
    QLineEdit *port;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QStringLiteral("Client"));
        Client->resize(800, 627);
        action = new QAction(Client);
        action->setObjectName(QStringLiteral("action"));
        centralWidget = new QWidget(Client);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Chat = new QTextBrowser(centralWidget);
        Chat->setObjectName(QStringLiteral("Chat"));
        Chat->setGeometry(QRect(10, 10, 761, 331));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 370, 81, 41));
        label_2->setFrameShape(QFrame::StyledPanel);
        bold = new QToolButton(centralWidget);
        bold->setObjectName(QStringLiteral("bold"));
        bold->setGeometry(QRect(120, 370, 51, 41));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Bold.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        bold->setIcon(icon);
        Color = new QToolButton(centralWidget);
        Color->setObjectName(QStringLiteral("Color"));
        Color->setGeometry(QRect(200, 370, 51, 41));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Color.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Color->setIcon(icon1);
        font = new QToolButton(centralWidget);
        font->setObjectName(QStringLiteral("font"));
        font->setGeometry(QRect(280, 370, 51, 41));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/tty.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        font->setIcon(icon2);
        toolButton_4 = new QToolButton(centralWidget);
        toolButton_4->setObjectName(QStringLiteral("toolButton_4"));
        toolButton_4->setGeometry(QRect(360, 370, 51, 41));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Italic.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_4->setIcon(icon3);
        submitEdit = new QTextEdit(centralWidget);
        submitEdit->setObjectName(QStringLiteral("submitEdit"));
        submitEdit->setGeometry(QRect(10, 430, 531, 111));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(550, 440, 160, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        submit = new QPushButton(verticalLayoutWidget);
        submit->setObjectName(QStringLiteral("submit"));

        verticalLayout->addWidget(submit);

        clear = new QPushButton(verticalLayoutWidget);
        clear->setObjectName(QStringLiteral("clear"));

        verticalLayout->addWidget(clear);

        leave = new QPushButton(centralWidget);
        leave->setObjectName(QStringLiteral("leave"));
        leave->setGeometry(QRect(710, 520, 81, 41));
        leave->setStyleSheet(QStringLiteral("color: rgb(170, 88, 22);"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(430, 374, 81, 31));
        label_5->setFrameShape(QFrame::StyledPanel);
        user = new QLineEdit(centralWidget);
        user->setObjectName(QStringLiteral("user"));
        user->setGeometry(QRect(520, 380, 81, 31));
        ip = new QLineEdit(centralWidget);
        ip->setObjectName(QStringLiteral("ip"));
        ip->setGeometry(QRect(620, 350, 113, 31));
        port = new QLineEdit(centralWidget);
        port->setObjectName(QStringLiteral("port"));
        port->setGeometry(QRect(620, 390, 113, 31));
        Client->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Client);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 26));
        Client->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Client);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Client->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Client);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Client->setStatusBar(statusBar);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Client", Q_NULLPTR));
        action->setText(QApplication::translate("Client", "\350\277\236\346\216\245", Q_NULLPTR));
        label_2->setText(QApplication::translate("Client", "TOOL", Q_NULLPTR));
        bold->setText(QApplication::translate("Client", "...", Q_NULLPTR));
        Color->setText(QApplication::translate("Client", "...", Q_NULLPTR));
        font->setText(QApplication::translate("Client", "...", Q_NULLPTR));
        toolButton_4->setText(QApplication::translate("Client", "...", Q_NULLPTR));
        submitEdit->setPlaceholderText(QApplication::translate("Client", "\346\255\244\345\244\204\350\276\223\345\205\245\350\201\212\345\244\251\345\206\205\345\256\271......", Q_NULLPTR));
        submit->setText(QApplication::translate("Client", "\345\217\221\351\200\201", Q_NULLPTR));
        clear->setText(QApplication::translate("Client", "\346\270\205\351\231\244", Q_NULLPTR));
        leave->setText(QApplication::translate("Client", "\347\246\273\345\274\200\350\201\212\345\244\251\345\256\244", Q_NULLPTR));
        label_5->setText(QApplication::translate("Client", "\345\275\223\345\211\215\347\224\250\346\210\267", Q_NULLPTR));
        user->setPlaceholderText(QApplication::translate("Client", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        ip->setPlaceholderText(QApplication::translate("Client", "IP", Q_NULLPTR));
        port->setPlaceholderText(QApplication::translate("Client", "Port", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
