#include "serialManager.hpp"
#include "serial.hpp"

#include "ui_serialManager.h"

#include <QSerialPortInfo>
#include <QMap>
#include <QString>

#include <string>


struct serialManager_t::privateData_t
{
    Ui::serialManagerWidget_t *ui;
    QMap<QString, serial_t*> serials;
    QString activePort;
    bool onlyOneActive = true;
};

serialManager_t::serialManager_t(QWidget *parent_):
    QWidget(parent_),
    m_d (new serialManager_t::privateData_t)
{
    m_d->ui = new Ui::serialManagerWidget_t;
    m_d->ui->setupUi(this);
}

serialManager_t::~serialManager_t()
{
    delete m_d->ui;
}

void serialManager_t::updateSerialsList ()
{
    std::vector <std::string> names;
    const auto infos = QSerialPortInfo::availablePorts();

    for (auto i = 0; i < infos.size(); i++)
    {
        auto name = infos[i].portName();
        auto port = new serial_t (name, this);
        port->addToLayout(m_d->ui->mainLayout);

        connect (port, &serial_t::onConnStatus, this, &serialManager_t::handleConnStatus);
        connect (port, &serial_t::onError, this, &serialManager_t::onError);
        connect (port, &serial_t::onLogMessage, this, &serialManager_t::onLogMessage);
        connect (port, &serial_t::onNewData, this, &serialManager_t::onNewSerialData);

        m_d->serials[name] = port;
    }
}

void serialManager_t::handleConnStatus (QString portName_, bool status_)
{
    if (status_ && m_d->onlyOneActive)
    {
        m_d->activePort = portName_;
        for (auto const &key : m_d->serials.keys ())
        {
            if (key != portName_)
                m_d->serials[key]->close();
        }
    }
}

void serialManager_t::writeToSerial(QByteArray data_)
{
    if (m_d->serials.keys().indexOf(m_d->activePort) >= 0)
        m_d->serials[m_d->activePort]->write (data_);
    else
    {
        emit onError("Port " + data_ + " does not exist.");
    }
}
