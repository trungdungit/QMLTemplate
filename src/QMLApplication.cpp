#include "QMLApplication.h"
#include "QmlGlobal.h"
#include "CmdLineOptParser.h"
#include "QMLCorePlugin.h"

QMLApplication* QMLApplication::_app = nullptr;

static QObject* qmlGlobalSingletonFactory(QQmlEngine*, QJSEngine*)
{
    // We create this object as a QMLTool even though it isn't in the toolbox
    QmlGlobal* qmlGlobal = new QmlGlobal(qmlApp(), qmlApp()->toolbox());
    qmlGlobal->setToolbox(qmlApp()->toolbox());

    return qmlGlobal;
}


QMLApplication::QMLApplication(int &argc, char* argv[], bool unitTesting)
    : QApplication          (argc, argv)
    , _runningUnitTests     (unitTesting)
{
    _app = this;

    // Parse command line options

    bool fClearSettingsOptions = false; // Clear stored settings
    bool fClearCache = false;           // Clear parameter/airframe caches
    bool logging = false;               // Turn on logging
    QString loggingOptions;

    CmdLineOpt_t rgCmdLineOptions[] = {
        { "--clear-settings",   &fClearSettingsOptions, nullptr },
        { "--clear-cache",      &fClearCache,           nullptr },
        { "--logging",          &logging,               &loggingOptions },
        // Add additional command line option flags here
    };

    ParseCmdLineOptions(argc, argv, rgCmdLineOptions, sizeof(rgCmdLineOptions)/sizeof(rgCmdLineOptions[0]), false);

    // Set application information
    QString applicationName = QStringLiteral("%1").arg(QML_APPLICATION_NAME);

    setApplicationName(applicationName);
    setOrganizationName(QML_ORG_NAME);
    setOrganizationDomain(QML_ORG_DOMAIN);

    this->setApplicationVersion(QString(APP_VERSION_STR));

    // Set settings format
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings settings;
    qDebug() << "Settings location" << settings.fileName() << "Is writable?:" << settings.isWritable();

    _toolbox = new QMLToolbox(this);
    _toolbox->setChildToolboxes();

    _checkForNewVersion();
}

void QMLApplication::_exitWithError(QString errorMessage)
{
    _error = true;
    QQmlApplicationEngine* pEngine = new QQmlApplicationEngine(this);
    pEngine->addImportPath("qrc:/qml");
    pEngine->rootContext()->setContextProperty("errorMessage", errorMessage);
    pEngine->load(QUrl(QStringLiteral("qrc:/qml/ExitWithErrorWindow.qml")));
    // Exit main application when last window is closed
    connect(this, &QMLApplication::lastWindowClosed, this, QMLApplication::quit);
}

void QMLApplication::_shutdown()
{
    // Close out all Qml before we delete toolbox. This way we don't get all sorts of null reference complaints from Qml.
    delete _qmlAppEngine;
    delete _toolbox;
}

QObject *QMLApplication::_rootQmlObject()
{
    if (_qmlAppEngine && _qmlAppEngine->rootObjects().size())
        return _qmlAppEngine->rootObjects()[0];
    return nullptr;
}

QMLApplication::~QMLApplication()
{
    // Place shutdown code in _shutdown
    _app = nullptr;
}

void QMLApplication::_initCommon()
{
    static const char* kQMLTemplate = "QMLTemplate";

    qmlRegisterSingletonType<QmlGlobal>(kQMLTemplate, 1, 0, kQMLTemplate, qmlGlobalSingletonFactory);
}

bool QMLApplication::_initForNormalAppBoot()
{
    QSettings settings;

    _qmlAppEngine = toolbox()->corePlugin()->createQmlApplicationEngine(this);
    toolbox()->corePlugin()->createRootWindow(_qmlAppEngine);

    return true;
}

bool QMLApplication::_initForUnitTests()
{
    return true;
}

/// @brief Returns the QMLApplication object singleton.
QMLApplication* qmlApp(void)
{
    return QMLApplication::_app;
}

void QMLApplication::showAppMessage(const QString& message, const QString& title)
{
    QString dialogTitle = title.isEmpty() ? applicationName() : title;

    QObject* rootQmlObject = _rootQmlObject();
    if (rootQmlObject) {
        QVariant varReturn;
        QVariant varMessage = QVariant::fromValue(message);
        QMetaObject::invokeMethod(_rootQmlObject(), "_showMessageDialog", Q_RETURN_ARG(QVariant, varReturn), Q_ARG(QVariant, dialogTitle), Q_ARG(QVariant, varMessage));
    } else if (runningUnitTests()) {
        // Unit tests can run without UI
        qDebug() << "QMLApplication::showAppMessage unittest title:message" << dialogTitle << message;
    } else {
        // UI isn't ready yet

    }
}

void QMLApplication::_checkForNewVersion()
{
    if (!_runningUnitTests) {


    }
}

QQuickWindow* QMLApplication::mainRootWindow()
{
    if(!_mainRootWindow) {
        _mainRootWindow = qobject_cast<QQuickWindow*>(_rootQmlObject());
    }
    return _mainRootWindow;
}


bool QMLApplication::compressEvent(QEvent*event, QObject* receiver, QPostEventList* postedEvents)
{
    if (event->type() != QEvent::MetaCall) {
        return QApplication::compressEvent(event, receiver, postedEvents);
    }

    return false;
}

bool QMLApplication::event(QEvent *e)
{
    if (e->type() == QEvent::Quit) {

    }
    return QApplication::event(e);
}
