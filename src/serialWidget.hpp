/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */


#pragma once

#include <QDialog>
#include <QSerialPort>

QT_BEGIN_NAMESPACE

namespace Ui {
class serialPortWidget;
}

class QIntValidator;

QT_END_NAMESPACE

class serialWidget_t : public QWidget
{
    Q_OBJECT

public:

    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool logEnabled;
    };

    explicit serialWidget_t(QString portName_ = "", QWidget *parent = nullptr);
    ~serialWidget_t();

    Settings const& settings();

    void handleConnectionStatusChange (QString portName_, bool status_);
    void handleNewTimestamp (QString timestamp_);

signals:
    void onOpenPort();
    void onClosePort ();
    void onLogEnableChange (bool status_);

private slots:
    void checkCustomBaudRatePolicy(int idx);
//    void checkCustomDevicePathPolicy(int idx);

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

private:
    Ui::serialPortWidget *m_ui = nullptr;
    Settings m_currentSettings;
    QIntValidator *m_intValidator = nullptr;

    QString m_portName;
};
