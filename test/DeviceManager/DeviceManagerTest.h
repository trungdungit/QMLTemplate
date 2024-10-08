#pragma once

#include "UnitTest.h"

class DeviceManagerTest : public UnitTest {
    Q_OBJECT
public:
    DeviceManagerTest(void);

protected:
    void init(void) final;
    void cleanup(void) final;

private slots:
    void device_test();
};

