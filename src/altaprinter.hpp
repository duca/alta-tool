/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */
#pragma once

#include "stateMachine.hpp"

#include <QObject>
#include <QSharedPointer>
#include <QTimer>

#include <memory>

class altaPrinter_t : public QObject
{
    Q_OBJECT

public:
    explicit altaPrinter_t(QObject *parent_ = nullptr);
    ~altaPrinter_t();

    void handleFrontLeftPoint ();
    void handleFrontRightPoint ();
    void handleBackPoint ();
    void handleEmergencyStop ();
    void handleSerialData (QString portName_, QByteArray data_);
    void handleCalibrationCommand (bool state_);
    void handleTransitionAction (QString action_);
    void handleCooldownExtruder (bool state_);
    void handleMoveToDispenser ();
    void handleLoadFilament (float length_);
    void handleUnloadFilament (float length_);

signals:
    void onNewCommand (QByteArray command_) const;
    void onError (QString message_) const;
    void onNewTemperatureValue (int const value_) const;

private:
    inline QByteArray prepareCommand (std::string const &command_) const;

    stateMachine_t m_sm;
};
