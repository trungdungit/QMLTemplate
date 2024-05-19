#ifndef SettingsManager_H
#define SettingsManager_H

#include "QMLToolbox.h"
#include "AppSettings.h"
#include "UnitsSettings.h"

/// Provides access to all app settings
class SettingsManager : public QMLTool
{
    Q_OBJECT

public:
    SettingsManager(QMLApplication* app, QMLToolbox* toolbox);

    Q_PROPERTY(QObject* appSettings                     READ appSettings                    CONSTANT)

    // Override from QMLTool
    virtual void setToolbox(QMLToolbox *toolbox);

    AppSettings*                    appSettings                 (void) { return _appSettings; }
    UnitsSettings*                  unitsSettings               (void) { return _unitsSettings; }

private:
    AppSettings*                    _appSettings;
    UnitsSettings*                  _unitsSettings;
};

#endif
