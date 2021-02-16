/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "serial.hpp"

#include <QDateTime>
#include <QThread>

namespace {
auto constexpr MAX_READ_SIZE = 512; // bytes
auto constexpr LAST_TIMESTAMP_UPDATE = 1000; //ms
}

serial_t::serial_t (QString portName_, QWidget *parent_)
    : QObject (parent_), m_buffer (MAX_READ_SIZE, '\0'),
      m_serial (new QSerialPort (dynamic_cast<QObject *> (this))),
      m_widget (new serialWidget_t (portName_, parent_)), m_updateTimestamp (this)
{
    connect(m_serial, &QSerialPort::errorOccurred, this, &serial_t::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &serial_t::readData);

    connect (m_widget, &serialWidget_t::onClosePort, this, &serial_t::close);
    connect (m_widget, &serialWidget_t::onOpenPort, this, &serial_t::open);
    connect (m_widget, &serialWidget_t::onLogEnableChange, this, [this] (bool status_) {
        m_logEnabled = status_;
    });

    connect (this, &serial_t::onConnStatus, m_widget, &serialWidget_t::handleConnectionStatusChange);
    connect (this, &serial_t::onNewTimestamp, m_widget, &serialWidget_t::handleNewTimestamp);

    m_updateTimestamp.setInterval (LAST_TIMESTAMP_UPDATE);
    m_updateTimestamp.setSingleShot (false);
    m_updateTimestamp.callOnTimeout ([this] () {
        qint64 curTimestamp = QDateTime::currentSecsSinceEpoch ();
        emit onNewTimestamp (QString::number (curTimestamp - m_lastMsgTimestamp) + " seconds");
    });
}

serial_t::~serial_t () = default;

void serial_t::config()
{
    m_serial->setPortName(m_widget->settings().name);
    m_serial->setBaudRate(m_widget->settings().baudRate);
    m_serial->setDataBits(m_widget->settings().dataBits);
    m_serial->setParity(m_widget->settings().parity);
    m_serial->setStopBits(m_widget->settings().stopBits);
    m_serial->setFlowControl(m_widget->settings().flowControl);
}

void serial_t::readData ()
{
    while (m_serial->bytesAvailable () > 1) {
        m_buffer = m_serial->readLine (MAX_READ_SIZE);

        m_lastMsgTimestamp = QDateTime::currentSecsSinceEpoch ();
        emit onNewData (m_serial->portName (), m_buffer);

        if (m_logEnabled) {
            emit onLogMessage(m_serial->portName() + QString(": ") + m_buffer);
        }
    }
}

void serial_t::open()
{
    config();

    m_logEnabled = m_widget->settings().logEnabled;

    auto status = m_serial->open(QIODevice::ReadWrite);
    if (status){
        m_lastMsgTimestamp = QDateTime::currentSecsSinceEpoch ();
        m_updateTimestamp.start ();
        emit onConnStatus (m_serial->portName (), status);
    }
    else
    {
        emit onError("Failed to connect to " + m_serial->portName());
    }
    if (m_logEnabled)
    {
        emit onLogMessage(QString("Serial: ") + m_serial->portName() +
                          QString(" open status: ") + QString::number(status));
    }
}

void serial_t::close()
{
    m_updateTimestamp.stop ();
    m_serial->close();
    emit onConnStatus(m_serial->portName(), false);
}

void serial_t::handleError(QSerialPort::SerialPortError error_)
{
    QString errorStr = m_serial->portName() + ": ";

    switch (error_)
    {
    case QSerialPort::NoError:
        errorStr += "Ok";
        break;
    case QSerialPort::OpenError:
        errorStr += "Failed to open";
        break;
    case QSerialPort::DeviceNotFoundError:
        errorStr += "Not found";
        break;
    case QSerialPort::ReadError:
        errorStr += "unable to read from it";
        break;
    case QSerialPort::NotOpenError:
        errorStr += "not opened";
    case QSerialPort::TimeoutError:
        errorStr += "read timed out";
        break;
    case QSerialPort::UnknownError:
        errorStr += "failed with unknown error";
        break;
    default:
        errorStr += "unsupported error code " +
            QString::number(static_cast<int>(error_));
    };
    emit onError(errorStr);
}

void serial_t::addToLayout(QLayout *layout_)
{
    m_widget->setParent(layout_->widget());
    layout_->addWidget(m_widget);
}

void serial_t::write(QByteArray payload_)
{
    auto count = m_serial->write(payload_);
    if (count != payload_.size())
        emit onError ("Error! Only wrote" + QString::number(count) + " of " +
                     QString::number(payload_.size()));

}
