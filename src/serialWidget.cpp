/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */


#include "serialWidget.hpp"
#include "ui_serialWidget.h"

#include <QIntValidator>
#include <QLineEdit>
#include <QSerialPortInfo>

static const char blankString[] = QT_TRANSLATE_NOOP("serialPortWidget", "N/A");

serialWidget_t::serialWidget_t(QString portName_, QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::serialPortWidget),
    m_intValidator(new QIntValidator(0, 4000000, this)),
    m_portName(portName_)
{
    m_ui->setupUi(this);

    m_ui->baudRateBox->setInsertPolicy(QComboBox::NoInsert);

    connect (m_ui->baudRateBox,
             QOverload<int>::of (&QComboBox::currentIndexChanged),
             this,
             &serialWidget_t::checkCustomBaudRatePolicy);

    connect (m_ui->showSerialPortButton, &QPushButton::toggled, [this] (bool checked_){
            if (checked_)
                m_ui->showSerialPortButton->setText (tr("Hide") + " " + m_portName);
            else
                m_ui->showSerialPortButton->setText (tr("Show") + " " + m_portName);
            m_ui->portConfigWidget->setVisible(checked_);});

    connect (m_ui->openPortButton, &QPushButton::clicked,
            [this]() {
                updateSettings();
                emit onOpenPort();
            });

    connect (m_ui->closePortButton, &QPushButton::clicked, this, &serialWidget_t::onClosePort);

    connect (m_ui->enableLogCheckbox, &QCheckBox::clicked, this, &serialWidget_t::onLogEnableChange);

    fillPortsParameters();
    fillPortsInfo();

    updateSettings();
    m_ui->portConfigWidget->setVisible(false);
}

serialWidget_t::~serialWidget_t()
{
    delete m_ui;
}

serialWidget_t::Settings const& serialWidget_t::settings()
{
    updateSettings ();
    return m_currentSettings;
}

void serialWidget_t::checkCustomBaudRatePolicy(int idx)
{
    const bool isCustomBaudRate = !m_ui->baudRateBox->itemData(idx).isValid();
    m_ui->baudRateBox->setEditable(isCustomBaudRate);
    if (isCustomBaudRate) {
        m_ui->baudRateBox->clearEditText();
        QLineEdit *edit = m_ui->baudRateBox->lineEdit();
        edit->setValidator(m_intValidator);
    }
}

void serialWidget_t::fillPortsParameters()
{
    m_ui->showSerialPortButton->setText("Show " + m_portName);

    m_ui->baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    m_ui->baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    m_ui->baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    m_ui->baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    m_ui->baudRateBox->addItem(tr("Custom"));

    m_ui->dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    m_ui->dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    m_ui->dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    m_ui->dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    m_ui->dataBitsBox->setCurrentIndex(3);

    m_ui->parityBox->addItem(tr("None"), QSerialPort::NoParity);
    m_ui->parityBox->addItem(tr("Even"), QSerialPort::EvenParity);
    m_ui->parityBox->addItem(tr("Odd"), QSerialPort::OddParity);
    m_ui->parityBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    m_ui->parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    m_ui->stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    m_ui->stopBitsBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    m_ui->stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    m_ui->flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    m_ui->flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    m_ui->flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void serialWidget_t::fillPortsInfo()
{
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {

        if (info.portName() != m_portName)
            continue;
        QString description = info.description();
        QString manufacturer = info.manufacturer();
        QString serial = info.serialNumber();
        QString location = info.systemLocation();

        m_ui->descriptionLabel->setText(tr("Description: %1").arg(description.size() > 1 ? description : tr(blankString)));
        m_ui->manufacturerLabel->setText(tr("Manufacturer: %1").arg(manufacturer.size() > 1 ? manufacturer : tr(blankString)));
        m_ui->serialNumberLabel->setText(tr("Serial number: %1").arg(serialNumber.size() > 1 ? serialNumber : tr(blankString)));
        m_ui->locationLabel->setText(tr("Location: %1").arg(location.size() > 4 ? location : tr(blankString)));
    }
}

void serialWidget_t::updateSettings()
{
    if (m_ui->baudRateBox->currentIndex() == 4) {
        m_currentSettings.baudRate = m_ui->baudRateBox->currentText().toInt();
    } else {
        m_currentSettings.baudRate = static_cast<QSerialPort::BaudRate>(
                    m_ui->baudRateBox->itemData(m_ui->baudRateBox->currentIndex()).toInt());
    }
    m_currentSettings.stringBaudRate = QString::number(m_currentSettings.baudRate);

    m_currentSettings.dataBits = static_cast<QSerialPort::DataBits>(
                m_ui->dataBitsBox->itemData(m_ui->dataBitsBox->currentIndex()).toInt());
    m_currentSettings.stringDataBits = m_ui->dataBitsBox->currentText();

    m_currentSettings.parity = static_cast<QSerialPort::Parity>(
                m_ui->parityBox->itemData(m_ui->parityBox->currentIndex()).toInt());
    m_currentSettings.stringParity = m_ui->parityBox->currentText();

    m_currentSettings.stopBits = static_cast<QSerialPort::StopBits>(
                m_ui->stopBitsBox->itemData(m_ui->stopBitsBox->currentIndex()).toInt());
    m_currentSettings.stringStopBits = m_ui->stopBitsBox->currentText();

    m_currentSettings.flowControl = static_cast<QSerialPort::FlowControl>(
                m_ui->flowControlBox->itemData(m_ui->flowControlBox->currentIndex()).toInt());
    m_currentSettings.stringFlowControl = m_ui->flowControlBox->currentText();
    m_currentSettings.name = m_portName;
    m_currentSettings.logEnabled = m_ui->enableLogCheckbox->isChecked();
}

void serialWidget_t::handleConnectionStatusChange (QString portName_, bool status_)
{
    Q_UNUSED(portName_);
    if (status_)
    {
        m_ui->openPortButton->setEnabled(false);
        m_ui->closePortButton->setEnabled(true);
        m_ui->closePortButton->setChecked(false);
        m_ui->timeMessageLabel->setText ("Port Opened");
    } else
    {
        m_ui->openPortButton->setChecked(false);
        m_ui->openPortButton->setEnabled(true);
        m_ui->closePortButton->setEnabled(false);
        m_ui->timeMessageLabel->setText ("Port Closed");
    }
}

void serialWidget_t::handleNewTimestamp (QString timestamp_)
{
    m_ui->timeMessageLabel->setText (timestamp_);
}
