/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */
#pragma once

#include "altaprinter.hpp"
#include "serialManager.hpp"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class mainWindow_t : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow_t(QWidget *parent_ = nullptr);
    ~mainWindow_t ();

private:
    void handleTemperatureUpdate (int value);

    Ui::MainWindow *m_ui;

    serialManager_t *m_serialManager;
    altaPrinter_t m_alta;
};
