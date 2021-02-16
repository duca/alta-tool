/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "mainWindow.hpp"
#include "ui_mainWindow.h"

#include <QSerialPortInfo>

mainWindow_t::mainWindow_t(QWidget *parent_) :
    QMainWindow(parent_),
    m_ui(new Ui::MainWindow),
    m_alta(parent_)
{
    m_ui->setupUi(this);

    m_serialManager = new serialManager_t(m_ui->managerContainer);
    m_serialManager->updateSerialsList();

    connect (m_serialManager, &serialManager_t::onNewSerialData,
            &m_alta, &altaPrinter_t::handleSerialData);

    connect (&m_alta, &altaPrinter_t::onNewCommand, m_serialManager,
            &serialManager_t::writeToSerial);

    connect (m_ui->backPointButton, &QPushButton::clicked, this, [this] (bool enable_) {
        Q_UNUSED (enable_);
        qDebug ("Back Calibration point clicked");
        m_alta.handleBackPoint();
    });

    connect (m_ui->frontLeftButton, &QPushButton::clicked, this, [this] (bool enable_) {
        Q_UNUSED (enable_);
        qDebug ("Front Left Calibration point clicked");
        m_alta.handleFrontLeftPoint();
    });

    connect (m_ui->frontRightButton, &QPushButton::clicked, this, [this] (bool enable_) {
        Q_UNUSED (enable_);
        qDebug ("Front Right Calibration point clicked");
        m_alta.handleFrontRightPoint();
    });

    connect (m_ui->stopButton, &QPushButton::clicked, this, [this] (bool enable_) {
        Q_UNUSED (enable_);
        qDebug ("Emergency Stop point clicked");
        m_alta.handleEmergencyStop();
    });

    connect (m_ui->beginCalibButton,
             &QPushButton::clicked,
             &m_alta,
             &altaPrinter_t::handleCalibrationCommand);

    connect (m_ui->cooldownExtruderButton,
             &QPushButton::clicked,
             &m_alta,
             &altaPrinter_t::handleCooldownExtruder);

    connect (m_ui->loadButton, &QPushButton::clicked, this, [this] (bool clicked_) {
        Q_UNUSED (clicked_)
        m_alta.handleLoadFilament (m_ui->loadLengthSpin->value ());
    });
    connect (m_ui->unloadButton, &QPushButton::clicked, this, [this] (bool clicked_) {
        Q_UNUSED (clicked_)
        m_alta.handleUnloadFilament (m_ui->unloadLengthSpin->value ());
    });
    connect (m_ui->dispenserButton, &QPushButton::clicked, this, [this] (bool clicked_) {
        Q_UNUSED (clicked_)
        m_alta.handleMoveToDispenser ();
    });

    connect (&m_alta,
             &altaPrinter_t::onNewTemperatureValue,
             this,
             &mainWindow_t::handleTemperatureUpdate);
}

mainWindow_t::~mainWindow_t()
{
    delete m_ui;
}

void mainWindow_t::handleTemperatureUpdate (int value_)
{
    m_ui->temperatureLCD->display (value_);
}
