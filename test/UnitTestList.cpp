#include "UnitTestList.h"
#include "UnitTest.h"

#include "DeviceManagerTest.h"
#include "MainWindowTest.h"

namespace UnitTestList
{
int runTests(bool stress, QStringView unitTestOptions)
{
    UT_REGISTER_TEST(DeviceManagerTest)
    UT_REGISTER_TEST(MainWindowTest)

    int result = 0;

    for (int i=0; i < (stress ? 20 : 1); i++) {
        // Run the test
        const int failures = UnitTest::run(unitTestOptions);
        if (failures == 0) {
            qDebug() << "All tests passed";
            result = 0;
        } else {
            qDebug() << failures << " tests failed!";
            result = -failures;
            break;
        }
    }

    return result;
}
}