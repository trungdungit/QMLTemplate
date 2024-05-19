/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "AppSettings.h"
#include "QmlPalette.h"
#include "QMLApplication.h"

#include <QQmlEngine>
#include <QtQml>
#include <QStandardPaths>


DECLARE_SETTINGGROUP(App, "")
{
    qmlRegisterUncreatableType<AppSettings>("QMLTemplate.SettingsManager", 1, 0, "AppSettings", "Reference only");
}

DECLARE_SETTINGSFACT(AppSettings, appName)
