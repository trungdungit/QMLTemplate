#include "SettingsManager.h"

#include <QQmlEngine>
#include <QtQml>

SettingsManager::SettingsManager(QMLApplication* app, QMLToolbox* toolbox)
    : QMLTool(app, toolbox)
    , _appSettings(nullptr)
    , _unitsSettings(nullptr)
{

}

void SettingsManager::setToolbox(QMLToolbox *toolbox)
{
    QMLTool::setToolbox(toolbox);
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    qmlRegisterUncreatableType<SettingsManager>("QMLTemplate.SettingsManager", 1, 0, "SettingsManager", "Reference only");

    _appSettings =                  new AppSettings                 (this);
    _unitsSettings =                new UnitsSettings               (this);
}
