/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *Info;
    QPushButton *login;
    QPushButton *quit;
    QLabel *userLabel;
    QLabel *pwdLabel;
    QLineEdit *userEdit;
    QLineEdit *pwdEdit;
    QPushButton *signUp;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(364, 271);
        Info = new QLabel(Login);
        Info->setObjectName(QStringLiteral("Info"));
        Info->setGeometry(QRect(10, 10, 191, 51));
        QFont font;
        font.setFamily(QStringLiteral("Fira Code"));
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        Info->setFont(font);
        Info->setTextFormat(Qt::AutoText);
        login = new QPushButton(Login);
        login->setObjectName(QStringLiteral("login"));
        login->setGeometry(QRect(40, 190, 101, 41));
        login->setStyleSheet(QStringLiteral(""));
        quit = new QPushButton(Login);
        quit->setObjectName(QStringLiteral("quit"));
        quit->setGeometry(QRect(190, 190, 101, 41));
        userLabel = new QLabel(Login);
        userLabel->setObjectName(QStringLiteral("userLabel"));
        userLabel->setGeometry(QRect(30, 70, 72, 31));
        QFont font1;
        font1.setPointSize(12);
        userLabel->setFont(font1);
        pwdLabel = new QLabel(Login);
        pwdLabel->setObjectName(QStringLiteral("pwdLabel"));
        pwdLabel->setGeometry(QRect(30, 130, 72, 31));
        pwdLabel->setFont(font1);
        userEdit = new QLineEdit(Login);
        userEdit->setObjectName(QStringLiteral("userEdit"));
        userEdit->setGeometry(QRect(80, 70, 241, 31));
        pwdEdit = new QLineEdit(Login);
        pwdEdit->setObjectName(QStringLiteral("pwdEdit"));
        pwdEdit->setGeometry(QRect(80, 130, 241, 31));
        signUp = new QPushButton(Login);
        signUp->setObjectName(QStringLiteral("signUp"));
        signUp->setGeometry(QRect(240, 20, 101, 41));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Dialog", Q_NULLPTR));
        Info->setText(QApplication::translate("Login", "\347\256\241\347\220\206\345\221\230\347\231\273\351\231\206\347\263\273\347\273\237", Q_NULLPTR));
        login->setText(QApplication::translate("Login", "\347\231\273\345\275\225", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        login->setShortcut(QApplication::translate("Login", "Alt+Return", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        quit->setText(QApplication::translate("Login", "\351\200\200\345\207\272", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        quit->setShortcut(QApplication::translate("Login", "Alt+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        userLabel->setText(QApplication::translate("Login", "\350\264\246\345\217\267", Q_NULLPTR));
        pwdLabel->setText(QApplication::translate("Login", "\345\257\206\347\240\201", Q_NULLPTR));
        userEdit->setPlaceholderText(QApplication::translate("Login", "\350\257\267\350\276\223\345\205\245\350\264\246\345\217\267", Q_NULLPTR));
        pwdEdit->setPlaceholderText(QApplication::translate("Login", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", Q_NULLPTR));
        signUp->setText(QApplication::translate("Login", "\346\263\250\345\206\214", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        signUp->setShortcut(QApplication::translate("Login", "Alt+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
