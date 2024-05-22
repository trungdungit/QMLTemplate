#pragma once

#include "UnitTest.h"
#include <QQmlApplicationEngine>

class MainWindowTest : public UnitTest {
    Q_OBJECT
public:
    MainWindowTest(void);

protected:
    void init(void) final;
    void cleanup(void) final;

private slots:
    void showWindow_test();

private:
    QQmlApplicationEngine* qmlEngine;
};

