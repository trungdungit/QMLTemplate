/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "QMLApplication.h"
#include "QMLCorePlugin.h"
#include "QMLOptions.h"
#include "QmlComponentInfo.h"
#include "FactMetaData.h"
#include "SettingsManager.h"
#include "QmlObjectListModel.h"

#include <QtQml>
#include <QQmlEngine>

/// @file
///     @brief Core Plugin Interface for QGroundControl - Default Implementation
///     @author Gus Grubba <gus@auterion.com>

class QMLCorePlugin_p
{
public:
    QMLCorePlugin_p()
    {
    }

    ~QMLCorePlugin_p()
    {
    }

    QMLOptions*  defaultOptions          = nullptr;
};

QMLCorePlugin::~QMLCorePlugin()
{
    if(_p) {
        delete _p;
    }
}

QMLCorePlugin::QMLCorePlugin(QMLApplication *app, QMLToolbox* toolbox)
    : QMLTool(app, toolbox)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    _p = new QMLCorePlugin_p;
}

void QMLCorePlugin::setToolbox(QMLToolbox *toolbox)
{
    QMLTool::setToolbox(toolbox);

    qmlRegisterUncreatableType<QMLCorePlugin>       ("QMLTemplate", 1, 0, "QMLCorePlugin",       "Reference only");
    qmlRegisterUncreatableType<QMLOptions>          ("QMLTemplate", 1, 0, "QMLOptions",          "Reference only");
}

int QMLCorePlugin::defaultSettings()
{
    return 0;
}

bool QMLCorePlugin::adjustSettingMetaData(const QString& settingsGroup, FactMetaData& metaData) {
    if (settingsGroup == AppSettings::settingsGroup) {
        //-- Default Palette
        if (metaData.name() == ""/*AppSettings::indoorPaletteName*/) {
            QVariant outdoorPalette;
#if defined (__mobile__)
            outdoorPalette = 0;
#else
            outdoorPalette = 1;
#endif
            metaData.setRawDefaultValue(outdoorPalette);
            return true;
        }

#if defined (__mobile__)
        if (metaData.name() == AppSettings::telemetrySaveName) {
            // Mobile devices have limited storage so don't turn on telemtry saving by default
            metaData.setRawDefaultValue(false);
            return true;
        }
#endif
    }

    return true; // Show setting in ui
}

QMLOptions* QMLCorePlugin::options()
{
    if (!_p->defaultOptions) {
        _p->defaultOptions = new QMLOptions(this);
    }
    return _p->defaultOptions;
}

QQmlApplicationEngine* QMLCorePlugin::createQmlApplicationEngine(QObject* parent)
{
    QQmlApplicationEngine* qmlEngine = new QQmlApplicationEngine(parent);
    qmlEngine->addImportPath("qrc:/qml");
    return qmlEngine;
}

void QMLCorePlugin::createRootWindow(QQmlApplicationEngine* qmlEngine)
{
    qmlEngine->load(QUrl(QStringLiteral("qrc:/qml/MainRootWindow.qml")));
}

void QMLCorePlugin::paletteOverride(QString /*colorName*/, QMLPalette::PaletteColorInfo_t& /*colorInfo*/)
{

}
