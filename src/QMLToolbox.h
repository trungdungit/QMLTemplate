#pragma once


#include <QObject>

class DeviceManager;
class QMLApplication;
class QMLCorePlugin;
class SettingsManager;

/// This is used to manage all of our top level services/tools
class QMLToolbox : public QObject {
    Q_OBJECT

public:
    QMLToolbox(QMLApplication* app);

    DeviceManager*      deviceManager   () { return _deviceManager; }
    QMLCorePlugin*      corePlugin      () { return _corePlugin; }
    SettingsManager*    settingsManager () { return _settingsManager; }

private:
    void setChildToolboxes(void);
    void _scanAndLoadPlugins(QMLApplication *app);

    DeviceManager*              _deviceManager          = nullptr;
    QMLCorePlugin*              _corePlugin             = nullptr;
    SettingsManager*            _settingsManager        = nullptr;

    friend class QMLApplication;
};

/// This is the base class for all tools
class QMLTool : public QObject {
    Q_OBJECT

public:
    // All tools must be parented to the QMLToolbox and go through a two phase creation. In the constructor the toolbox
    // should only be passed to QMLTool constructor for correct parenting. It should not be referenced or set in the
    // protected member. Then in the second phase of setToolbox calls is where you can reference the toolbox.
    QMLTool(QMLApplication* app, QMLToolbox* toolbox);

    // If you override this method, you must call the base class.
    virtual void setToolbox(QMLToolbox* toolbox);

protected:
    QMLApplication* _app;
    QMLToolbox*     _toolbox;
};
