/********************************************************************************
** Form generated from reading UI file 'ara_sound_manager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARA_SOUND_MANAGER_H
#define UI_ARA_SOUND_MANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ara_Sound_Manager
{
public:

    void setupUi(QWidget *Ara_Sound_Manager)
    {
        if (Ara_Sound_Manager->objectName().isEmpty())
            Ara_Sound_Manager->setObjectName(QString::fromUtf8("Ara_Sound_Manager"));
        Ara_Sound_Manager->resize(400, 300);

        retranslateUi(Ara_Sound_Manager);

        QMetaObject::connectSlotsByName(Ara_Sound_Manager);
    } // setupUi

    void retranslateUi(QWidget *Ara_Sound_Manager)
    {
        Ara_Sound_Manager->setWindowTitle(QCoreApplication::translate("Ara_Sound_Manager", "Ara_Sound_Manager", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Ara_Sound_Manager: public Ui_Ara_Sound_Manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARA_SOUND_MANAGER_H
