#pragma once

#include <QByteArray>
#include <QVector>
#include <QWidget>
#include <memory>

class serialManager_t : public QWidget
{
    Q_OBJECT

public:
    explicit serialManager_t(QWidget *parent_ = nullptr);
    ~serialManager_t();

    void writeToSerial (QByteArray data_);
    void updateSerialsList ();


signals:
    void onNewSerialData (QString portName_, QByteArray data_);

    void onLogMessage (QString message_);
    void onError (QString error_);

private:
    struct privateData_t;
    std::unique_ptr<privateData_t> m_d;

    void handleConnStatus (QString portName_, bool status_);
};
