#pragma once

#include <memory>
#include <QObject>

class stateMachine_t : public QObject
{
    Q_OBJECT

public:
    explicit stateMachine_t (QObject *parent = nullptr);

    ~stateMachine_t ();
    void begin ();
    void end ();
    void moveToFrontLeftPoint ();
    void moveToFrontRightPoint ();
    void moveToBackPoint ();
    void moveToDispenser ();
    void moveToCustom (int x_, int y_, int z_);
    void touchTable ();
    void reset ();
    void loadFilament (float length_ = 0);
    void unloadFilament (float length_ = 0);
    void coolDownExtruder (bool state_);
    void reportTemperature ();

signals:
    void onNewCommand (QString command);

private:
    struct privateData_t;
    std::unique_ptr<privateData_t> m_d;
};

