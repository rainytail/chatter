/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

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

class Ui_SignUp
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *userEdit;
    QLineEdit *pwdEdit;
    QPushButton *signup;
    QPushButton *quit;

    void setupUi(QDialog *SignUp)
    {
        if (SignUp->objectName().isEmpty())
            SignUp->setObjectName(QStringLiteral("SignUp"));
        SignUp->resize(329, 241);
        label = new QLabel(SignUp);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 171, 61));
        QFont font;
        font.setFamily(QStringLiteral("Fira Code"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("\n"
"color: rgb(255, 168, 117);"));
        label_2 = new QLabel(SignUp);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 70, 91, 41));
        QFont font1;
        font1.setPointSize(12);
        label_2->setFont(font1);
        label_3 = new QLabel(SignUp);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 120, 91, 31));
        label_3->setFont(font1);
        userEdit = new QLineEdit(SignUp);
        userEdit->setObjectName(QStringLiteral("userEdit"));
        userEdit->setGeometry(QRect(70, 70, 221, 31));
        pwdEdit = new QLineEdit(SignUp);
        pwdEdit->setObjectName(QStringLiteral("pwdEdit"));
        pwdEdit->setGeometry(QRect(70, 120, 221, 31));
        signup = new QPushButton(SignUp);
        signup->setObjectName(QStringLiteral("signup"));
        signup->setGeometry(QRect(20, 180, 93, 28));
        quit = new QPushButton(SignUp);
        quit->setObjectName(QStringLiteral("quit"));
        quit->setGeometry(QRect(200, 180, 93, 28));

        retranslateUi(SignUp);

        QMetaObject::connectSlotsByName(SignUp);
    } // setupUi

    void retranslateUi(QDialog *SignUp)
    {
        SignUp->setWindowTitle(QApplication::translate("SignUp", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("SignUp", "\346\263\250\345\206\214\351\241\265\351\235\242", Q_NULLPTR));
        label_2->setText(QApplication::translate("SignUp", "\350\264\246\345\217\267", Q_NULLPTR));
        label_3->setText(QApplication::translate("SignUp", "\345\257\206\347\240\201", Q_NULLPTR));
        userEdit->setPlaceholderText(QApplication::translate("SignUp", "\350\257\267\350\276\223\345\205\245\346\263\250\345\206\214\347\232\204\350\264\246\345\217\267", Q_NULLPTR));
        pwdEdit->setPlaceholderText(QApplication::translate("SignUp", "\350\257\267\350\276\223\345\205\245\346\263\250\345\206\214\347\232\204\345\257\206\347\240\201", Q_NULLPTR));
        signup->setText(QApplication::translate("SignUp", "\346\263\250\345\206\214", Q_NULLPTR));
        quit->setText(QApplication::translate("SignUp", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SignUp: public Ui_SignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
