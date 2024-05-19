#pragma once

#include "QMLToolbox.h"
#include "QmlPalette.h"
#include "QmlObjectListModel.h"

#include <QQmlApplicationEngine>

class QMLApplication;
class QMLOptions;
class QMLSettings;
class QMLCorePlugin_p;
class FactMetaData;
class QQuickItem;

class QMLCorePlugin : public QMLTool
{
    Q_OBJECT
public:
    QMLCorePlugin(QMLApplication* app, QMLToolbox* toolbox);
    ~QMLCorePlugin();

    /// The default settings panel to show
    /// @return The settings index
    virtual int defaultSettings();

    /// Global options
    /// @return An instance of QMLOptions
    virtual QMLOptions* options();

    /// Allows the core plugin to override the setting meta data before the setting fact is created.
    ///     @param settingsGroup - QSettings group which contains this item
    ///     @param metaData - MetaData for setting fact
    /// @return true: Setting should be visible in ui, false: Setting should not be shown in ui
    virtual bool adjustSettingMetaData(const QString& settingsGroup, FactMetaData& metaData);

    /// Allows the plugin to override or get access to the QmlApplicationEngine to do things like add import
    /// path or stuff things into the context prior to window creation.
    virtual QQmlApplicationEngine* createQmlApplicationEngine(QObject* parent);

    /// Allows the plugin to override the creation of the root (native) window.
    virtual void createRootWindow(QQmlApplicationEngine* qmlEngine);

    /// Allows a plugin to override the specified color name from the palette
    virtual void paletteOverride(QString colorName, QMLPalette::PaletteColorInfo_t& colorInfo);

    // Override from QMLTool
    void                            setToolbox              (QMLToolbox* toolbox);

private:
    QMLCorePlugin_p*    _p;
};
