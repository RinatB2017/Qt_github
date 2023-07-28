/********************************************************************************
** Form generated from reading UI file 'about_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_DIALOG_H
#define UI_ABOUT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_About_Dialog
{
public:

    void setupUi(QDialog *About_Dialog)
    {
        if (About_Dialog->objectName().isEmpty())
            About_Dialog->setObjectName(QString::fromUtf8("About_Dialog"));
        About_Dialog->resize(400, 300);

        retranslateUi(About_Dialog);

        QMetaObject::connectSlotsByName(About_Dialog);
    } // setupUi

    void retranslateUi(QDialog *About_Dialog)
    {
        About_Dialog->setWindowTitle(QCoreApplication::translate("About_Dialog", "About_Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About_Dialog: public Ui_About_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_DIALOG_H
