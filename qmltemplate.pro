QMAKE_PROJECT_DEPTH = 0 # undocumented qmake flag to force absolute paths in makefiles

exists($${OUT_PWD}/qmltemplate.pro) {
    error("You must use shadow build (e.g. mkdir build; cd build; qmake ../qmltemplate.pro).")
}

message(Qt version $$[QT_VERSION])

!contains(CONFIG, DISABLE_QT_VERSION_CHECK) {
    !versionAtLeast(QT_VERSION, 5.15.2) {
        error("Qt version 5.15.2 or newer required. Found $$QT_VERSION")
    }
}

include(QMLCommon.pri)

TARGET = QMLTemplate
TEMPLATE = app

QML_IMPORT_PATH += $$PWD/UI

MacBuild {
}

LinuxBuild {
    CONFIG += qesp_linux_udev
    system("$$QMAKE_LINK -fuse-ld=gold -Wl,--version &>/dev/null") {
        CONFIG += use_gold_linker
    }
}

WindowsBuild {
}

QML_APP_NAME        = "QMLTemplate"
QML_ORG_NAME        = "QMLTemplate.org"
QML_ORG_DOMAIN      = "org.qmltemplate"
QML_APP_DESCRIPTION = ""
QML_APP_COPYRIGHT   = ""

iOSBuild {
}

LinuxBuild {
    CONFIG += link_pkgconfig
}

# Qt configuration

CONFIG += qt thread silent
CONFIG -= qtquickcompiler

QT += \
    concurrent \
    gui \
    location \
    network \
    opengl \
    positioning \
    qml \
    quick \
    quickcontrols2 \
    quickwidgets \
    sql \
    svg \
    widgets \
    xml \
    texttospeech \
    core-private \
    quick3d

include(QMLExternalLibs.pri)

DEFINES += QML_APPLICATION_NAME=\"\\\"QMLTemplate\\\"\"
DEFINES += QML_ORG_NAME=\"\\\"qmltemplate.org\\\"\"
DEFINES += QML_ORG_DOMAIN=\"\\\"org.qmltemplate\\\"\"
RESOURCES += \
    $$PWD/qmltemplate.qrc \
    $$PWD/resources.qrc \

#
# DeviceManager
#
INCLUDEPATH += \
    src/DeviceManager \
    src/Settings \

HEADERS += \
    src/DeviceManager/DeviceManager.h \

SOURCES += \
    src/DeviceManager/DeviceManager.cpp \

# Fact System code

INCLUDEPATH += \
    src/FactSystem \

HEADERS += \
    src/FactSystem/Fact.h \
    src/FactSystem/FactGroup.h \
    src/FactSystem/FactMetaData.h \
    src/FactSystem/FactSystem.h \
    src/FactSystem/FactValueSliderListModel.h \
    src/FactSystem/SettingsFact.h \

SOURCES += \
    src/FactSystem/Fact.cpp \
    src/FactSystem/FactGroup.cpp \
    src/FactSystem/FactMetaData.cpp \
    src/FactSystem/FactSystem.cpp \
    src/FactSystem/FactValueSliderListModel.cpp \
    src/FactSystem/SettingsFact.cpp \

# api

INCLUDEPATH += \
    src/api \

HEADERS += \
    src/api/QMLCorePlugin.h \
    src/api/QMLOptions.h \
    src/api/QMLSettings.h \
    src/api/QmlComponentInfo.h \

SOURCES += \
    src/api/QMLCorePlugin.cpp \
    src/api/QMLOptions.cpp \
    src/api/QMLSettings.cpp \
    src/api/QmlComponentInfo.cpp \

# Utilities

INCLUDEPATH += \
    src/Utilities \

HEADERS += \
    src/Utilities/JsonHelper.h \
    src/Utilities/QML.h \
    src/Utilities/QMLLoggingCategory.h \

SOURCES += \
    src/Utilities/JsonHelper.cpp \
    src/Utilities/QML.cpp \
    src/Utilities/QMLLoggingCategory.cpp \

# QMLControls

INCLUDEPATH += \
    src/QMLControls \

HEADERS += \
    src/QMLControls/QmlGlobal.h \
    src/QMLControls/QmlObjectListModel.h \
    src/QMLControls/QmlPalette.h \

SOURCES += \
    src/QMLControls/QmlGlobal.cpp \
    src/QMLControls/QmlObjectListModel.cpp \
    src/QMLControls/QmlPalette.cpp \

#
# Main
#
INCLUDEPATH += .
INCLUDEPATH += \
    src \

HEADERS += \
    src/Settings/AppSettings.h \
    src/Settings/UnitsSettings.h \
    src/Settings/SettingsGroup.h \
    src/Settings/SettingsManager.h \
    src/CmdLineOptParser.h \
    src/QMLApplication.h \
    src/QMLConfig.h \
    src/QMLToolbox.h \
    src/RunGuard.h \

SOURCES += \
    src/Settings/AppSettings.cpp \
    src/Settings/UnitsSettings.cpp \
    src/Settings/SettingsGroup.cpp \
    src/Settings/SettingsManager.cpp \
    src/CmdLineOptParser.cpp \
    src/main.cpp \
    src/QMLApplication.cpp \
    src/QMLToolbox.cpp \
    src/RunGuard.cpp \


#-------------------------------------------------------------------------------------
#
# Localization
#

TRANSLATIONS += $$files($$PWD/translations/qml*.ts)
CONFIG+=lrelease embed_translations

WindowsBuild {
    PRECOMPILED_HEADER += src/pch.h
    HEADERS += src/pch.h
    CONFIG -= silent
}

#
# Steps for "install" target on Linux
#
LinuxBuild {
}

include(test/QMLTest.pri)
