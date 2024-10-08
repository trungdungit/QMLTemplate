import QtQuick          2.11
import QtQuick.Controls 2.4

import QMLTemplate 1.0
import QMLTemplate.ScreenTools 1.0
import QMLTemplate.SettingsManager 1.0

/// @brief Native QML top level window
/// All properties defined here are visible to all QML pages.
ApplicationWindow {
    id:         mainWindow
    width:	    1280
    height:	    720
    visible:    true

    Rectangle {
        width: 200
        height: 200
        color: UIConstants.recordIconBg
    }

    Component.onCompleted: {
        console.log("Name = " + QMLTemplate.settingsManager.appSettings.appName.rawValue)
    }
}
