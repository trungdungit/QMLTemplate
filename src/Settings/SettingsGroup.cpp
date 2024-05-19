#include "SettingsGroup.h"
// #include "QMLCorePlugin.h"
#include "QMLApplication.h"

#include <QQmlEngine>
#include <QtQml>

static const char* kJsonFile = ":/json/%1.SettingsGroup.json";

SettingsGroup::SettingsGroup(const QString& name, const QString& settingsGroup, QObject* parent)
    : QObject       (parent)
    , _visible      (true)
    , _name         (name)
    , _settingsGroup(settingsGroup)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    _nameToMetaDataMap = FactMetaData::createMapFromJsonFile(QString(kJsonFile).arg(name), this);
}

SettingsFact* SettingsGroup::_createSettingsFact(const QString& factName)
{
    FactMetaData* m = _nameToMetaDataMap[factName];
    if(!m) {
        qCritical() << "Fact name " << factName << "not found in" << QString(kJsonFile).arg(_name);
        exit(-1);
    }
    return new SettingsFact(_settingsGroup, m, this);
}

