#pragma once

#include "QMLToolbox.h"

class DeviceManager : public QMLTool {
    Q_OBJECT
public:
    DeviceManager(QMLApplication* app, QMLToolbox* toolbox);
    ~DeviceManager();

    void setToolbox(QMLToolbox* toolbox) override;
};
