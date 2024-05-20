#include "DeviceManager.h"

#include <QQmlEngine>

DeviceManager::DeviceManager(QMLApplication *app, QMLToolbox *toolbox)
    : QMLTool(app, toolbox)
{

}

DeviceManager::~DeviceManager()
{

}

void DeviceManager::setToolbox(QMLToolbox *toolbox)
{
    QMLTool::setToolbox(toolbox);
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    qmlRegisterUncreatableType<DeviceManager>("QMLTemplate.DeviceManager", 1, 0, "DeviceManager", "Reference only");
}
