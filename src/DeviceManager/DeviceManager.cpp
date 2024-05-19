#include "DeviceManager.h"

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
}
