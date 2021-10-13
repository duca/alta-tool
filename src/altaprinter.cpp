/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */
#include "altaprinter.hpp"

#include <string>

namespace {
auto const RADIUS = 127;
auto const HEIGHT = 167;
} // namespace

altaPrinter_t::~altaPrinter_t () = default;

altaPrinter_t::altaPrinter_t (QObject *parent_) : QObject (parent_)
{
    connect (&m_sm, &stateMachine_t::onNewCommand, this, &altaPrinter_t::handleTransitionAction);
}

void altaPrinter_t::handleFrontLeftPoint ()
{
    m_sm.moveToFrontLeftPoint ();
}

void altaPrinter_t::handleFrontRightPoint ()
{
    m_sm.moveToFrontRightPoint ();
}

void altaPrinter_t::handleBackPoint ()
{
    m_sm.moveToBackPoint ();
}

void altaPrinter_t::handleEmergencyStop ()
{
    emit onNewCommand("G28\n");
}

void altaPrinter_t::handleSerialData (QString portName_, QByteArray data_)
{
    auto initialTempPos = data_.indexOf ("T:");
    if (initialTempPos >= 0) {
        auto dotPos = data_.indexOf (".", initialTempPos);
        QString rawTemp = data_.mid (initialTempPos + 2, dotPos - initialTempPos - 2);
        emit onNewTemperatureValue (rawTemp.toInt ());
    }
    qDebug ("%s:%s %d", portName_.toStdString().c_str(), data_.toStdString().c_str(),
           data_.size());
}

QByteArray altaPrinter_t::prepareCommand (std::string const &command_) const
{
    return QByteArray::fromStdString(command_ + "\n");
}

void altaPrinter_t::handleCalibrationCommand (bool state_)
{
    if (state_)
        m_sm.begin ();
    else
        m_sm.end ();
}

void altaPrinter_t::handleTransitionAction (QString action_)
{
    qDebug ("%s New command: %s", __PRETTY_FUNCTION__, action_.toStdString ().c_str ());
    emit onNewCommand (prepareCommand (action_.toStdString ()));
}

void altaPrinter_t::handleCooldownExtruder (bool state_)
{
    m_sm.coolDownExtruder (state_);
}
void altaPrinter_t::handleMoveToDispenser ()
{
    m_sm.moveToDispenser ();
}
void altaPrinter_t::handleLoadFilament (float length_)
{
    m_sm.loadFilament (length_);
}
void altaPrinter_t::handleUnloadFilament (float length_)
{
    m_sm.unloadFilament (length_);
}

void
altaPrinter_t::goToCoordinates (int x_, int y_, int z_)
{
    if (std::abs (x_) < RADIUS && std::abs (y_) < RADIUS && z_ > 0 && z_ < HEIGHT)
        m_sm.moveToCustom (x_, y_, z_);
}
