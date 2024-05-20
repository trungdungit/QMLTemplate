#include "DeviceManagerTest.h"

DeviceManagerTest::DeviceManagerTest()
{

}

void DeviceManagerTest::init(void) {
    UnitTest::init();
}

void DeviceManagerTest::cleanup(void) {
    UnitTest::cleanup();
}

void DeviceManagerTest::device_test()
{
    qDebug() << "Device test successfully";
}
