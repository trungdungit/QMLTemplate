#pragma once

#include <QApplication>
#include <QQuickStyle>
#include <QSettings>
#include <QQuickWindow>
#include <QMetaMethod>
#include <QMetaObject>
#include <QMessageBox>
#include <QTranslator>
#include <QQmlContext>

#include "DeviceManager.h"

class QQmlApplicationEngine;
class QMLToolbox;

/**
 * @brief The main application and management class.
 *
 * This class is started by the main method and provides
 * the central management unit of the groundstation application.
 *
 * Needs QApplication base to support QtCharts module. This way
 * we avoid application crashing on 5.12 when using the module.
 *
 * Note: `lastWindowClosed` will be sent by MessageBox popups and other
 * dialogs, that are spawned in QML, when they are closed
**/

class QMLApplication : public QApplication {
    Q_OBJECT
public:
    QMLApplication(int &argc, char *argv[], bool unitTesting);
    ~QMLApplication();

    /// @brief Returns true if unit tests are being run
    bool runningUnitTests(void) const{ return _runningUnitTests; }

    /// @brief Returns true if Qt debug output should be logged to a file
    bool logOutput(void) const{ return _logOutput; }

    QMLToolbox *toolbox(void) { return _toolbox; }

    QTranslator& qmlJSONTranslator(void) { return _qmlTranslatorJSON; }

    QQuickWindow*   mainWindow();

    bool event(QEvent *e) override;

public slots:
    /// Show modal application message to the user
    void showAppMessage(const QString& message, const QString& title = QString());

public:
    // Although public, these methods are internal and should only be called by UnitTest code

    /// @brief Perform initialize which is common to both normal application running and unit tests.
    ///         Although public should only be called by main.
    void _initCommon();

    /// @brief Initialize the application for normal application boot. Or in other words we are not going to run
    ///         unit tests. Although public should only be called by main.
    bool _initForNormalAppBoot();

    /// @brief Initialize the application for normal application boot. Or in other words we are not going to run
    ///         unit tests. Although public should only be called by main.
    bool _initForUnitTests();

    static QMLApplication*  _app;   ///< Our own singleton. Should be reference directly by qmlApp

    bool    isErrorState() const { return _error; }

    QQmlApplicationEngine* qmlAppEngine() { return _qmlAppEngine; }

public:
    // Although public, these methods are internal and should only be called by UnitTest code

    /// Shutdown the application object
    void _shutdown();

private:
    QObject*    _rootQmlObject          ();
    void        _checkForNewVersion     ();
    void        _exitWithError          (QString errorMessage);

    // Overrides from QApplication
    bool compressEvent(QEvent *event, QObject *receiver, QPostEventList *postedEvents) override;

private:
    bool                _runningUnitTests;
    bool                _logOutput;
    QQmlApplicationEngine* _qmlAppEngine        = nullptr;
    QMLToolbox*         _toolbox                = nullptr;
    QQuickWindow*       _mainWindow             = nullptr;
    QLocale             _locale;
    QTranslator         _qmlTranslatorJSON;
    bool                _error                  = false;

    /// Unit Test have access to creating and destroying singletons
    friend class UnitTest;
};

/// @brief Returns the QMLApplication object singleton.
QMLApplication* qmlApp(void);
