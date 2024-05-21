#include "UnitTestList.h"
#include "UnitTest.h"

#include "DeviceManagerTest.h"
#include "MainWindowTest.h"

int runTests(bool stress, QStringView unitTestOptions)
{
    UT_REGISTER_TEST(DeviceManagerTest)
    UT_REGISTER_TEST(MainWindowTest)

    int result = 0;

    for (int i=0; i < (stress ? 20 : 1); i++) {
        // Run the test
        const int failures = UnitTest::run(unitTestOptions);
        if (failures == 0) {
            qDebug() << "ALL TESTS PASSED";
            result = 0;
        } else {
            qDebug() << failures << " TESTS FAILED!";
            result = -failures;
            break;
        }
    }

    return result;
}
