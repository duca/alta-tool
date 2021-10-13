#include "stateMachine.hpp"

#include <string>
#include <variant>
#include <QTimer>
#include <QVector>

namespace {
QVector<QString> const BEGIN_CALIB{"G28", "G90"};
QVector<QString> const END_CALIB{"G28", "M114"};

QString const TURN_COOLER_ON = "M106 S255";
QString const TURN_COOLER_OFF = "M107";

QString const REPORT_TEMPERATURE = "M105";
QString const EXTRUSION_CMD{"G1 E"};
QString const HOTEND_MELT_PLA {"M109 S200"};
QString const HOTEND_COOLDOWN{"M104 S10"};
QString const POLL_TEMPERATURE_CMD{"M155 S4"};

QString const ABS_POS_MOVES{"G90"};
QString const REL_POS_MOVES{"G91"};
QString const HOVER_IN_PLACE{"G1 Z10 F3000"};
QString const TOUCH_PLATE{"G1 Z0 F1000"};

QString const FRONT_LEFT_POINT{"G1 X-50 Y-30 Z5 F3000"};
QString const FRONT_RIGHT_POINT{"G1 X50 Y-30 Z5 F3000"};
QString const BACK_POINT{"G1 X0 Y50 F3000"};
QString const CENTER_POINT{"G1 X0 Y0 Z10 F3000"};
QString const UNLOAD_POINT {"G1 X0 Y-71 Z100 F1000"};

constexpr int REPORT_TEMPERATURE_TIMEOUT = 8000;

enum class tablePoint_t {
    FRONT_LEFT,
    FRONT_RIGHT,
    BACK,
    CENTER,
    TOUCH,
    HOVER,
    UNLOAD,
    CUSTOM,
    NONE
};

std::map<tablePoint_t, QString> POINT_LUT {{tablePoint_t::FRONT_LEFT, FRONT_LEFT_POINT},
                                           {tablePoint_t::FRONT_RIGHT, FRONT_RIGHT_POINT},
                                           {tablePoint_t::BACK, BACK_POINT},
                                           {tablePoint_t::CENTER, CENTER_POINT},
                                           {tablePoint_t::TOUCH, TOUCH_PLATE},
                                           {tablePoint_t::HOVER, HOVER_IN_PLACE},
                                           {tablePoint_t::UNLOAD, UNLOAD_POINT},
                                           {tablePoint_t::CUSTOM, ""},
                                           {tablePoint_t::NONE, ""}};

struct movingState_t
{
    explicit movingState_t (tablePoint_t point_, stateMachine_t &sm_) : m_point (point_)
    {
        emit sm_.onNewCommand (ABS_POS_MOVES);
        emit sm_.onNewCommand (POINT_LUT[point_]);
    }
    tablePoint_t point () const { return m_point; }

private:
    tablePoint_t m_point{tablePoint_t::NONE};
};

struct touchedState_t
{
    explicit touchedState_t (stateMachine_t &sm_) { movingState_t (tablePoint_t::TOUCH, sm_); }
};

struct unloadState_t
{
    explicit unloadState_t (stateMachine_t &sm_)
    {
        movingState_t (tablePoint_t::UNLOAD, sm_);
        emit sm_.onNewCommand (POLL_TEMPERATURE_CMD);
        emit sm_.onNewCommand (HOTEND_MELT_PLA);
    }
};

struct waitingOkState_t
{};

struct idleState_t
{};

struct invalidState_t
{};

using state_t
    = std::variant<movingState_t, touchedState_t, unloadState_t, idleState_t, invalidState_t>;

struct moveToPoint_t
{
    explicit moveToPoint_t (tablePoint_t const point_, stateMachine_t &sm_)
        : m_point (point_), m_sm (sm_)
    {}
    state_t operator() (movingState_t &state_) { return state_; }
    state_t operator() (invalidState_t &state_) { return state_; }

    template<class T>
    state_t operator() (T const &)
    {
        movingState_t{tablePoint_t::HOVER, m_sm};
        return movingState_t{m_point, m_sm};
    }

private:
    tablePoint_t m_point{tablePoint_t::NONE};
    stateMachine_t &m_sm;
};

struct touchPoint_t
{
    explicit touchPoint_t (stateMachine_t &sm) : m_sm (sm) {}
    state_t operator() (touchedState_t &state_) { return state_; }

    state_t operator() (movingState_t const &) { return touchedState_t{m_sm}; }
    state_t operator() (idleState_t &state_) { return state_; }

    /// \brief do nothing when in unload state, extruder might be hot
    state_t operator() (unloadState_t &state_) { return state_; }
    state_t operator() (invalidState_t &state_) { return state_; }

private:
    stateMachine_t &m_sm;
}; // namespace

struct unload_t
{
    explicit unload_t (float length_, stateMachine_t &sm) : m_sm (sm), m_length (length_) {}

    state_t operator() (unloadState_t &state_)
    {
        m_sm.onNewCommand (REL_POS_MOVES);
        m_sm.onNewCommand (EXTRUSION_CMD + QString::number (m_length) + "F600");
        m_sm.onNewCommand (ABS_POS_MOVES);

        return state_;
    }

    template<class STATE>
    state_t operator() (STATE const &)
    {
        m_sm.reportTemperature ();
        return unloadState_t{m_sm};
    }
    state_t operator() (invalidState_t &state_) { return state_; }

private:
    stateMachine_t &m_sm;
    float m_length;
};
} // namespace

struct stateMachine_t::privateData_t
{
    state_t currentState{invalidState_t{}};
    QTimer pollTempeatureTimer;
};

stateMachine_t::~stateMachine_t () = default;

stateMachine_t::stateMachine_t (QObject *parent) : QObject (parent), m_d (new privateData_t)
{
    m_d->pollTempeatureTimer.setInterval (REPORT_TEMPERATURE_TIMEOUT);
    m_d->pollTempeatureTimer.callOnTimeout ([this] () { reportTemperature (); });
}

void stateMachine_t::moveToFrontLeftPoint ()
{
    m_d->currentState = std::visit (moveToPoint_t{tablePoint_t::FRONT_LEFT, *this},
                                    m_d->currentState);
    touchTable ();
}

void stateMachine_t::moveToFrontRightPoint ()
{
    m_d->currentState = std::visit (moveToPoint_t{tablePoint_t::FRONT_RIGHT, *this},
                                    m_d->currentState);
    touchTable ();
}

void stateMachine_t::moveToBackPoint ()
{
    m_d->currentState = std::visit (moveToPoint_t{tablePoint_t::BACK, *this}, m_d->currentState);
    touchTable ();
}

void stateMachine_t::moveToDispenser ()
{
    m_d->currentState = std::visit (moveToPoint_t{tablePoint_t::UNLOAD, *this}, m_d->currentState);
    touchTable ();
}

void stateMachine_t::touchTable ()
{
    m_d->currentState = std::visit (touchPoint_t{*this}, m_d->currentState);
}

void stateMachine_t::reset ()
{
    begin ();
}

void stateMachine_t::begin ()
{
    for (auto const &cmd : BEGIN_CALIB) {
        emit onNewCommand (cmd);
        m_d->pollTempeatureTimer.start ();
    }
    m_d->currentState = idleState_t{};
}

void stateMachine_t::end ()
{
    for (auto const &cmd : END_CALIB) {
        emit onNewCommand (cmd);
    }
}

void stateMachine_t::unloadFilament (float length_)
{
    m_d->currentState = std::visit (unload_t{-length_, *this}, m_d->currentState);
}

void stateMachine_t::loadFilament (float length_)
{
    m_d->currentState = std::visit (unload_t{length_, *this}, m_d->currentState);
}

void stateMachine_t::coolDownExtruder (bool state_)
{
    if (state_) {
        emit onNewCommand (HOTEND_COOLDOWN);
        emit onNewCommand (TURN_COOLER_ON);

        m_d->currentState = std::visit (moveToPoint_t{tablePoint_t::FRONT_LEFT, *this},
                                        m_d->currentState);
    } else {
        emit onNewCommand (TURN_COOLER_OFF);
    }
}

void stateMachine_t::reportTemperature ()
{
    emit onNewCommand (REPORT_TEMPERATURE);
}

void
stateMachine_t::moveToCustom (int x_, int y_, int z_)
{
    m_d->currentState = std::visit (moveToPoint_t {tablePoint_t::CUSTOM, *this}, m_d->currentState);
    emit onNewCommand (ABS_POS_MOVES);
    emit onNewCommand (QString ("G1 X%1 Y%2 Z%3 F3000").arg (x_).arg (y_).arg (z_));
}
