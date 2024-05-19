#ifndef QMLGLOBAL
#define QMLGLOBAL

#include "QMLToolbox.h"
#include "QMLApplication.h"
#include "QMLLoggingCategory.h"
#include "AppSettings.h"
#include "DeviceManager.h"
#include "QmlPalette.h"

class QMLToolbox;

class QmlGlobal : public QMLTool
{
    Q_OBJECT
public:
    QmlGlobal(QMLApplication* app, QMLToolbox* toolbox);
    ~QmlGlobal();

    Q_PROPERTY(QString              appName                 READ    appName                 CONSTANT)
    Q_PROPERTY(DeviceManager*       deviceManager           READ    deviceManager           CONSTANT)
    Q_PROPERTY(QMLCorePlugin*       corePlugin              READ    corePlugin              CONSTANT)
    Q_PROPERTY(SettingsManager*     settingsManager         READ    settingsManager         CONSTANT)

    // Property accesors
    QString                 appName             ()  { return qmlApp()->applicationName(); }
    DeviceManager*          deviceManager       ()  { return _deviceManager; }
    QMLCorePlugin*          corePlugin          ()  { return _corePlugin; }
    SettingsManager*        settingsManager     ()  { return _settingsManager; }

    // Overrides from QMLTool
    virtual void setToolbox(QMLToolbox* toolbox);

private:
    DeviceManager*          _deviceManager          = nullptr;
    QMLCorePlugin*          _corePlugin             = nullptr;
    SettingsManager*        _settingsManager        = nullptr;
};

#endif
