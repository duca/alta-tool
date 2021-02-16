// =====================================================================
// Copyright (c) 2020 Oceaneering International, Inc.  All rights reserved.
// =====================================================================
// This software is proprietary to Oceaneering International, Inc.
// This software may not be duplicated or transferred to other parties
// without the express written consent of Oceaneering International, Inc.
//
// Utilization of the contents hereof by a third party in any manner
// shall in and of itself constitute an acknowledgment of and
// agreement to the foregoing.

#pragma once

#include "serialWidget.hpp"

#include <QByteArray>
#include <QLayout>
#include <QMutex>
#include <QObject>
#include <QSerialPort>
#include <QTimer>

class serial_t : public QObject
{
    Q_OBJECT
public:
    serial_t (QString portName_ = "", QWidget *parent_ = nullptr);
    ~serial_t ();
    void addToLayout (QLayout *layout_);
    void open ();
    void close();
    void write (QByteArray payload_);

signals:
    void onNewData (QString name_, QByteArray data_);
    void onConnStatus (QString name_, bool status_);
    void onNewTimestamp (QString timestamp_);
    void onError (QString msg_);
    void onLogMessage (QString msg_);

private:
    qint64 m_lastMsgTimestamp;
    QByteArray m_buffer;
    QSerialPort *m_serial;
    serialWidget_t *m_widget;
    bool m_logEnabled;
    QMutex m_mutex;
    QTimer m_updateTimestamp;

    void handleError (QSerialPort::SerialPortError error);
    void readData ();
    void config();
};
