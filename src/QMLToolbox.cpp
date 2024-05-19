#include "DeviceManager.h"
#include "SettingsManager.h"
#include "QMLCorePlugin.h"
#include "QMLApplication.h"

QMLToolbox::QMLToolbox(QMLApplication* app)
{
    //-- Scan and load plugins
    _scanAndLoadPlugins(app);

    _settingsManager    = new SettingsManager   (app, this);
    _deviceManager      = new DeviceManager     (app, this);
    _corePlugin         = new QMLCorePlugin     (app, this);
}

void QMLToolbox::setChildToolboxes()
{
    _settingsManager->setToolbox(this);
    _deviceManager->setToolbox(this);
    _corePlugin->setToolbox(this);
}

void QMLToolbox::_scanAndLoadPlugins(QMLApplication *app)
{

}

QMLTool::QMLTool(QMLApplication* app, QMLToolbox* toolbox)
    : QObject(toolbox)
    , _app(app)
    , _toolbox(nullptr)
{
}

void QMLTool::setToolbox(QMLToolbox* toolbox)
{
    _toolbox = toolbox;
}
