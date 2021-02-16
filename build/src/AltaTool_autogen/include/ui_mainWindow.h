/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *altaCmd;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QPushButton *frontLeftButton;
    QPushButton *backPointButton;
    QPushButton *stopButton;
    QPushButton *frontRightButton;
    QWidget *serialManager;
    QGridLayout *gridLayout_5;
    QWidget *managerContainer;
    QGridLayout *gridLayout_4;
    QWidget *logTab;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(727, 739);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        altaCmd = new QWidget();
        altaCmd->setObjectName(QString::fromUtf8("altaCmd"));
        gridLayout_3 = new QGridLayout(altaCmd);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frontLeftButton = new QPushButton(altaCmd);
        frontLeftButton->setObjectName(QString::fromUtf8("frontLeftButton"));

        gridLayout->addWidget(frontLeftButton, 1, 0, 1, 1);

        backPointButton = new QPushButton(altaCmd);
        backPointButton->setObjectName(QString::fromUtf8("backPointButton"));

        gridLayout->addWidget(backPointButton, 0, 1, 1, 1);

        stopButton = new QPushButton(altaCmd);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        gridLayout->addWidget(stopButton, 2, 1, 1, 1);

        frontRightButton = new QPushButton(altaCmd);
        frontRightButton->setObjectName(QString::fromUtf8("frontRightButton"));

        gridLayout->addWidget(frontRightButton, 1, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        tabWidget->addTab(altaCmd, QString());
        serialManager = new QWidget();
        serialManager->setObjectName(QString::fromUtf8("serialManager"));
        gridLayout_5 = new QGridLayout(serialManager);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        managerContainer = new QWidget(serialManager);
        managerContainer->setObjectName(QString::fromUtf8("managerContainer"));
        gridLayout_4 = new QGridLayout(managerContainer);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));

        gridLayout_5->addWidget(managerContainer, 0, 0, 1, 1);

        tabWidget->addTab(serialManager, QString());
        logTab = new QWidget();
        logTab->setObjectName(QString::fromUtf8("logTab"));
        tabWidget->addTab(logTab, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 727, 23));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        frontLeftButton->setText(QApplication::translate("MainWindow", "Front Left", nullptr));
        backPointButton->setText(QApplication::translate("MainWindow", "Back", nullptr));
        stopButton->setText(QApplication::translate("MainWindow", "STOP !!!", nullptr));
        frontRightButton->setText(QApplication::translate("MainWindow", "Front Right", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(altaCmd), QApplication::translate("MainWindow", "Alta command", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(serialManager), QApplication::translate("MainWindow", "Serial Manager", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(logTab), QApplication::translate("MainWindow", "Logs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
