#include "QmlGlobal.h"
#include "DeviceManager.h"


QmlGlobal::QmlGlobal(QMLApplication* app, QMLToolbox* toolbox)
    : QMLTool               (app, toolbox)
{
    // We clear the parent on this object since we run into shutdown problems caused by hybrid qml app. Instead we let it leak on shutdown.
    setParent(nullptr);
}

QmlGlobal::~QmlGlobal()
{
}

void QmlGlobal::setToolbox(QMLToolbox* toolbox)
{
    QMLTool::setToolbox(toolbox);

    _deviceManager          = toolbox->deviceManager();
    _settingsManager        = toolbox->settingsManager();
    _corePlugin             = toolbox->corePlugin();
}
