#include "MainWindowTest.h"
#include <QQmlApplicationEngine>


MainWindowTest::MainWindowTest()
{

}

void MainWindowTest::init()
{
    UnitTest::init();
    qmlEngine = new QQmlApplicationEngine(nullptr);
    Q_CHECK_PTR(qmlEngine);
}

void MainWindowTest::cleanup()
{
    if (qmlEngine != nullptr) {
        qmlEngine = nullptr;
    }
    UnitTest::cleanup();
}

void MainWindowTest::showWindow_test()
{
    qmlEngine->addImportPath("qrc:/qml");

    int argc = 1;
    char *argv[] = {(char*)"/"};

    QApplication app(argc, argv);
    const QUrl url(QStringLiteral("qrc:/qml/MainWindow.qml"));
    QObject::connect(
        qmlEngine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl){
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    qmlEngine->load(url);
    delete qmlEngine;
}
