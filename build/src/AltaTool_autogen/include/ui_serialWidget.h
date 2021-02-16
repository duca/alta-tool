/********************************************************************************
** Form generated from reading UI file 'serialWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALWIDGET_H
#define UI_SERIALWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serialPortWidget
{
public:
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout;
    QPushButton *showSerialPortButton;
    QWidget *portConfigWidget;
    QGridLayout *gridLayout;
    QLabel *timeMessageLabel;
    QLabel *label;
    QGroupBox *selectBox;
    QGridLayout *gridLayout_3;
    QLabel *locationLabel;
    QLabel *descriptionLabel;
    QLabel *manufacturerLabel;
    QLabel *serialNumberLabel;
    QGroupBox *parametersBox;
    QGridLayout *gridLayout_2;
    QComboBox *dataBitsBox;
    QComboBox *stopBitsBox;
    QLabel *stopBitsLabel;
    QComboBox *flowControlBox;
    QLabel *flowControlLabel;
    QComboBox *parityBox;
    QComboBox *baudRateBox;
    QLabel *baudRateLabel;
    QLabel *dataBitsLabel;
    QLabel *parityLabel;
    QCheckBox *enableLogCheckbox;
    QHBoxLayout *horizontalLayout;
    QPushButton *openPortButton;
    QPushButton *closePortButton;

    void setupUi(QWidget *serialPortWidget)
    {
        if (serialPortWidget->objectName().isEmpty())
            serialPortWidget->setObjectName(QString::fromUtf8("serialPortWidget"));
        serialPortWidget->resize(409, 407);
        gridLayout_4 = new QGridLayout(serialPortWidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        showSerialPortButton = new QPushButton(serialPortWidget);
        showSerialPortButton->setObjectName(QString::fromUtf8("showSerialPortButton"));
        showSerialPortButton->setCheckable(true);
        showSerialPortButton->setAutoDefault(false);

        verticalLayout->addWidget(showSerialPortButton);

        portConfigWidget = new QWidget(serialPortWidget);
        portConfigWidget->setObjectName(QString::fromUtf8("portConfigWidget"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(portConfigWidget->sizePolicy().hasHeightForWidth());
        portConfigWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(portConfigWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        timeMessageLabel = new QLabel(portConfigWidget);
        timeMessageLabel->setObjectName(QString::fromUtf8("timeMessageLabel"));
        timeMessageLabel->setEnabled(false);

        gridLayout->addWidget(timeMessageLabel, 2, 1, 1, 1);

        label = new QLabel(portConfigWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        selectBox = new QGroupBox(portConfigWidget);
        selectBox->setObjectName(QString::fromUtf8("selectBox"));
        gridLayout_3 = new QGridLayout(selectBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        locationLabel = new QLabel(selectBox);
        locationLabel->setObjectName(QString::fromUtf8("locationLabel"));

        gridLayout_3->addWidget(locationLabel, 3, 0, 1, 1);

        descriptionLabel = new QLabel(selectBox);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));

        gridLayout_3->addWidget(descriptionLabel, 0, 0, 1, 1);

        manufacturerLabel = new QLabel(selectBox);
        manufacturerLabel->setObjectName(QString::fromUtf8("manufacturerLabel"));

        gridLayout_3->addWidget(manufacturerLabel, 1, 0, 1, 1);

        serialNumberLabel = new QLabel(selectBox);
        serialNumberLabel->setObjectName(QString::fromUtf8("serialNumberLabel"));

        gridLayout_3->addWidget(serialNumberLabel, 2, 0, 1, 1);


        gridLayout->addWidget(selectBox, 0, 0, 1, 1);

        parametersBox = new QGroupBox(portConfigWidget);
        parametersBox->setObjectName(QString::fromUtf8("parametersBox"));
        gridLayout_2 = new QGridLayout(parametersBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        dataBitsBox = new QComboBox(parametersBox);
        dataBitsBox->setObjectName(QString::fromUtf8("dataBitsBox"));

        gridLayout_2->addWidget(dataBitsBox, 1, 1, 1, 1);

        stopBitsBox = new QComboBox(parametersBox);
        stopBitsBox->setObjectName(QString::fromUtf8("stopBitsBox"));

        gridLayout_2->addWidget(stopBitsBox, 3, 1, 1, 1);

        stopBitsLabel = new QLabel(parametersBox);
        stopBitsLabel->setObjectName(QString::fromUtf8("stopBitsLabel"));

        gridLayout_2->addWidget(stopBitsLabel, 3, 0, 1, 1);

        flowControlBox = new QComboBox(parametersBox);
        flowControlBox->setObjectName(QString::fromUtf8("flowControlBox"));

        gridLayout_2->addWidget(flowControlBox, 4, 1, 1, 1);

        flowControlLabel = new QLabel(parametersBox);
        flowControlLabel->setObjectName(QString::fromUtf8("flowControlLabel"));

        gridLayout_2->addWidget(flowControlLabel, 4, 0, 1, 1);

        parityBox = new QComboBox(parametersBox);
        parityBox->setObjectName(QString::fromUtf8("parityBox"));

        gridLayout_2->addWidget(parityBox, 2, 1, 1, 1);

        baudRateBox = new QComboBox(parametersBox);
        baudRateBox->setObjectName(QString::fromUtf8("baudRateBox"));

        gridLayout_2->addWidget(baudRateBox, 0, 1, 1, 1);

        baudRateLabel = new QLabel(parametersBox);
        baudRateLabel->setObjectName(QString::fromUtf8("baudRateLabel"));

        gridLayout_2->addWidget(baudRateLabel, 0, 0, 1, 1);

        dataBitsLabel = new QLabel(parametersBox);
        dataBitsLabel->setObjectName(QString::fromUtf8("dataBitsLabel"));

        gridLayout_2->addWidget(dataBitsLabel, 1, 0, 1, 1);

        parityLabel = new QLabel(parametersBox);
        parityLabel->setObjectName(QString::fromUtf8("parityLabel"));

        gridLayout_2->addWidget(parityLabel, 2, 0, 1, 1);

        enableLogCheckbox = new QCheckBox(parametersBox);
        enableLogCheckbox->setObjectName(QString::fromUtf8("enableLogCheckbox"));

        gridLayout_2->addWidget(enableLogCheckbox, 5, 0, 1, 2);


        gridLayout->addWidget(parametersBox, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        openPortButton = new QPushButton(portConfigWidget);
        openPortButton->setObjectName(QString::fromUtf8("openPortButton"));
        openPortButton->setCheckable(true);

        horizontalLayout->addWidget(openPortButton);

        closePortButton = new QPushButton(portConfigWidget);
        closePortButton->setObjectName(QString::fromUtf8("closePortButton"));
        closePortButton->setEnabled(false);
        closePortButton->setCheckable(true);

        horizontalLayout->addWidget(closePortButton);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 2);


        verticalLayout->addWidget(portConfigWidget);


        gridLayout_4->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(serialPortWidget);

        showSerialPortButton->setDefault(false);


        QMetaObject::connectSlotsByName(serialPortWidget);
    } // setupUi

    void retranslateUi(QWidget *serialPortWidget)
    {
        serialPortWidget->setWindowTitle(QApplication::translate("serialPortWidget", "Serial Port", nullptr));
        showSerialPortButton->setText(QApplication::translate("serialPortWidget", "Serial Port", nullptr));
        timeMessageLabel->setText(QApplication::translate("serialPortWidget", "port closed", nullptr));
        label->setText(QApplication::translate("serialPortWidget", "Time since last message:", nullptr));
        selectBox->setTitle(QApplication::translate("serialPortWidget", "Serial Port Info", nullptr));
        locationLabel->setText(QApplication::translate("serialPortWidget", "Location:", nullptr));
        descriptionLabel->setText(QApplication::translate("serialPortWidget", "Description:", nullptr));
        manufacturerLabel->setText(QApplication::translate("serialPortWidget", "Manufacturer:", nullptr));
        serialNumberLabel->setText(QApplication::translate("serialPortWidget", "Serial number:", nullptr));
        parametersBox->setTitle(QApplication::translate("serialPortWidget", "Select Parameters", nullptr));
        stopBitsLabel->setText(QApplication::translate("serialPortWidget", "Stop bits:", nullptr));
        flowControlLabel->setText(QApplication::translate("serialPortWidget", "Flow control:", nullptr));
        baudRateLabel->setText(QApplication::translate("serialPortWidget", "BaudRate:", nullptr));
        dataBitsLabel->setText(QApplication::translate("serialPortWidget", "Data bits:", nullptr));
        parityLabel->setText(QApplication::translate("serialPortWidget", "Parity:", nullptr));
        enableLogCheckbox->setText(QApplication::translate("serialPortWidget", "Enable Log", nullptr));
        openPortButton->setText(QApplication::translate("serialPortWidget", "Open Port", nullptr));
        closePortButton->setText(QApplication::translate("serialPortWidget", "Close Port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serialPortWidget: public Ui_serialPortWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALWIDGET_H
