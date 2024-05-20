#include <QtGlobal>
#include <QApplication>
#include <QQuickStyle>
#include <QQuickWindow>

#include "QMLApplication.h"
#include "QML.h"
#include "RunGuard.h"

#ifdef UNITTEST_BUILD
#include "UnitTestList.h"
#endif

#ifdef QT_DEBUG
#include "CmdLineOptParser.h"
#endif

#ifdef Q_OS_WIN

#include <windows.h>

/// @brief CRT Report Hook installed using _CrtSetReportHook. We install this hook when
/// we don't want asserts to pop a dialog on windows.
int WindowsCrtReportHook(int reportType, char* message, int* returnValue)
{
    Q_UNUSED(reportType);

    std::cerr << message << std::endl;  // Output message to stderr
    *returnValue = 0;                   // Don't break into debugger
    return true;                        // We handled this fully ourselves
}

#endif

// To shut down on Ctrl+C on Linux
#ifdef Q_OS_LINUX
#include <csignal>

void sigHandler(int s)
{
    std::signal(s, SIG_DFL);
    qmlApp()->mainRootWindow()->close();
    QEvent event{QEvent::Quit};
    qmlApp()->event(&event);
}

#endif /* Q_OS_LINUX */

//-----------------------------------------------------------------------------
/**
 * @brief Starts the application
 *
 * @param argc Number of commandline arguments
 * @param argv Commandline arguments
 * @return exit code, 0 for normal exit and !=0 for error cases
 */

int main(int argc, char *argv[])
{
#ifndef __mobile__
    // We make the runguard key different for custom and non custom
    // builds, so they can be executed together in the same device.
    // Stable and Daily have same QML_APPLICATION_NAME so they would
    // not be able to run at the same time
    QString runguardString(QML_APPLICATION_NAME);
    runguardString.append("RunGuardKey");

    RunGuard guard(runguardString);
    if (!guard.tryToRun()) {
        // QApplication is necessary to use QMessageBox
        QApplication errorApp(argc, argv);
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("A second instance of %1 is already running. Please close the other instance and try again.").arg(QML_APPLICATION_NAME)
        );
        return -1;
    }
#endif
    // Record boot timer
    QML::initTimer();

#ifdef Q_OS_MAC
#ifndef Q_OS_IOS
    // Prevent Apple's app nap from screwing us over
    // tip: the domain can be cross-checked on the command line with <defaults domains>
    QProcess::execute("defaults", {"write org.qgroundcontrol.qgroundcontrol NSAppSleepDisabled -bool YES"});
#endif
#endif

#ifdef Q_OS_WIN
    // Set our own OpenGL buglist
    qputenv("QT_OPENGL_BUGLIST", ":/opengl/resources/opengl/buglist.json");

    // Allow for command line override of renderer
    for (int i = 0; i < argc; i++) {
        const QString arg(argv[i]);
        if (arg == QStringLiteral("-angle")) {
            QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
            break;
        } else if (arg == QStringLiteral("-swrast")) {
            QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
            break;
        }
    }
#endif

#ifdef Q_OS_LINUX
    std::signal(SIGINT, sigHandler);
    std::signal(SIGTERM, sigHandler);
#endif /* Q_OS_LINUX */

// We statically link our own QtLocation plugin

#ifdef Q_OS_WIN
    // In Windows, the compiler doesn't see the use of the class created by Q_IMPORT_PLUGIN
#pragma warning( disable : 4930 4101 )
#endif

    bool runUnitTests = false;          // Run unit tests

#ifdef QT_DEBUG
    // We parse a small set of command line options here prior to QMLApplication in order to handle the ones
    // which need to be handled before a QApplication object is started.

    bool stressUnitTests = false;       // Stress test unit tests
    bool quietWindowsAsserts = false;   // Don't let asserts pop dialog boxes

    QString unitTestOptions;
    CmdLineOpt_t rgCmdLineOptions[] = {
        { "--unittest",             &runUnitTests,          &unitTestOptions },
        { "--unittest-stress",      &stressUnitTests,       &unitTestOptions },
        { "--no-windows-assert-ui", &quietWindowsAsserts,   nullptr },
        // Add additional command line option flags here
    };

    ParseCmdLineOptions(argc, argv, rgCmdLineOptions, sizeof(rgCmdLineOptions)/sizeof(rgCmdLineOptions[0]), false);
    if (stressUnitTests) {
        runUnitTests = true;
    }

    if (quietWindowsAsserts) {
#ifdef Q_OS_WIN
        _CrtSetReportHook(WindowsCrtReportHook);
#endif
    }

#ifdef Q_OS_WIN
    if (runUnitTests) {
        // Don't pop up Windows Error Reporting dialog when app crashes. This prevents TeamCity from
        // hanging.
        DWORD dwMode = SetErrorMode(SEM_NOGPFAULTERRORBOX);
        SetErrorMode(dwMode | SEM_NOGPFAULTERRORBOX);
    }
#endif
#endif // QT_DEBUG

#ifdef Q_OS_DARWIN
    // Gstreamer video playback requires OpenGL
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
#endif

    QMLApplication* app = new QMLApplication(argc, argv, runUnitTests);
    Q_CHECK_PTR(app);
    QQuickStyle::setStyle("Basic");
    if(app->isErrorState()) {
        app->exec();
        return -1;
    }

#ifdef Q_OS_LINUX
    QApplication::setWindowIcon(QIcon(":/res/icons/sample.ico"));
#endif /* Q_OS_LINUX */
    app->_initCommon();

    int exitCode = 0;

#ifdef UNITTEST_BUILD
    if (runUnitTests) {
        exitCode = runTests(stressUnitTests, unitTestOptions);
    } else
#endif
    {

#ifdef Q_OS_ANDROID
        AndroidInterface::checkStoragePermissions();
        QNativeInterface::QAndroidApplication::hideSplashScreen(333);
#endif
        if (!app->_initForNormalAppBoot()) {
            return -1;
        }
        exitCode = app->exec();
    }

    app->_shutdown();
    qDebug() << "After app delete";
    return exitCode;
}
