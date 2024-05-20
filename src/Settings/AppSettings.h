#pragma once

#include "SettingsGroup.h"

/// Application Settings
class AppSettings : public SettingsGroup
{
    Q_OBJECT

public:
    AppSettings(QObject* parent = nullptr);

    DEFINE_SETTING_NAME_GROUP()

    DEFINE_SETTINGFACT(appName)
    DEFINE_SETTINGFACT(darkTheme)
};
