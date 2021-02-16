/********************************************************************************
** Form generated from reading UI file 'serialManager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALMANAGER_H
#define UI_SERIALMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serialManagerWidget_t
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *mainLayout;

    void setupUi(QWidget *serialManagerWidget_t)
    {
        if (serialManagerWidget_t->objectName().isEmpty())
            serialManagerWidget_t->setObjectName(QString::fromUtf8("serialManagerWidget_t"));
        serialManagerWidget_t->resize(639, 543);
        gridLayout = new QGridLayout(serialManagerWidget_t);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mainLayout = new QVBoxLayout();
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));

        gridLayout->addLayout(mainLayout, 0, 0, 1, 1);


        retranslateUi(serialManagerWidget_t);

        QMetaObject::connectSlotsByName(serialManagerWidget_t);
    } // setupUi

    void retranslateUi(QWidget *serialManagerWidget_t)
    {
        serialManagerWidget_t->setWindowTitle(QApplication::translate("serialManagerWidget_t", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serialManagerWidget_t: public Ui_serialManagerWidget_t {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALMANAGER_H
