#include "MainWindowTest.h"
#include <QQmlApplicationEngine>


MainWindowTest::MainWindowTest()
{

}

void MainWindowTest::init()
{
    UnitTest::init();
}

void MainWindowTest::cleanup()
{
    UnitTest::cleanup();
}

void MainWindowTest::showWindow_test()
{
    QQmlApplicationEngine* qmlEngine = new QQmlApplicationEngine(nullptr);
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
