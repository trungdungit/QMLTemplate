#  testlib is needed even in release flavor for QSignalSpy support
QT += testlib
ReleaseBuild {
    QT.testlib.CONFIG -= console
} else:DebugBuild {
    # RESOURCES += $$PWD/UnitTest.qrc
    DEFINES += UNITTEST_BUILD

    INCLUDEPATH += \
        $$PWD/DeviceManager \
        $$PWD/qmlunittest \

    HEADERS += \
        $$PWD/DeviceManager/DeviceManagerTest.h \
        $$PWD/qmlunittest/UnitTest.h \

    SOURCES += \
        $$PWD/DeviceManager/DeviceManagerTest.cpp \
        $$PWD/qmlunittest/UnitTest.cpp \
}
