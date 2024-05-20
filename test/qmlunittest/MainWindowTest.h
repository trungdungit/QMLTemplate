#pragma once

#include "UnitTest.h"

class MainWindowTest : public UnitTest {
    Q_OBJECT
public:
    MainWindowTest(void);

protected:
    void init(void) final;
    void cleanup(void) final;

private slots:
    void showWindow_test();
};

