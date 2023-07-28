/********************************************************************************
** Form generated from reading UI file 'gameoverwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEOVERWINDOW_H
#define UI_GAMEOVERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GameOverWindow
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_3;

    void setupUi(QDialog *GameOverWindow)
    {
        if (GameOverWindow->objectName().isEmpty())
            GameOverWindow->setObjectName(QString::fromUtf8("GameOverWindow"));
        GameOverWindow->resize(557, 355);
        label = new QLabel(GameOverWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 481, 131));
        QFont font;
        font.setFamily(QString::fromUtf8("Arcade"));
        font.setPointSize(76);
        label->setFont(font);
        label_2 = new QLabel(GameOverWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 90, 471, 101));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arimo"));
        font1.setPointSize(26);
        label_2->setFont(font1);
        pushButton = new QPushButton(GameOverWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(90, 220, 131, 41));
        pushButton_2 = new QPushButton(GameOverWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(250, 220, 131, 41));
        label_3 = new QLabel(GameOverWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(390, 170, 151, 171));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/images/gameover.png")));

        retranslateUi(GameOverWindow);

        QMetaObject::connectSlotsByName(GameOverWindow);
    } // setupUi

    void retranslateUi(QDialog *GameOverWindow)
    {
        GameOverWindow->setWindowTitle(QCoreApplication::translate("GameOverWindow", "Game Over", nullptr));
        label->setText(QCoreApplication::translate("GameOverWindow", "GAME OVER", nullptr));
        label_2->setText(QCoreApplication::translate("GameOverWindow", "Would you like to play again?", nullptr));
#if QT_CONFIG(tooltip)
        pushButton->setToolTip(QCoreApplication::translate("GameOverWindow", "Continue", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton->setText(QCoreApplication::translate("GameOverWindow", "Yes", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_2->setToolTip(QCoreApplication::translate("GameOverWindow", "Quit", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_2->setText(QCoreApplication::translate("GameOverWindow", "No", nullptr));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameOverWindow: public Ui_GameOverWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEOVERWINDOW_H
