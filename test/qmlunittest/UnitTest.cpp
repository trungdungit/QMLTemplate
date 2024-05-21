/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "UnitTest.h"
#include "QMLApplication.h"
#include "AppSettings.h"
#include "SettingsManager.h"
#include "QMLUtilities.h"


UnitTest::UnitTest(void)
{

}

UnitTest::~UnitTest()
{
    if (_unitTestRun) {
        // Derived classes must call base class implementations
        Q_ASSERT(_initCalled);
        Q_ASSERT(_cleanupCalled);
    }
}

void UnitTest::_addTest(UnitTest* test)
{
    QList<UnitTest*>& tests = _testList();

    Q_ASSERT(!tests.contains(test));

    tests.append(test);
}

void UnitTest::_unitTestCalled(void)
{
    _unitTestRun = true;
}

/// @brief Returns the list of unit tests.
QList<UnitTest*>& UnitTest::_testList(void)
{
    static QList<UnitTest*> tests;
    return tests;
}

int UnitTest::run(QStringView& singleTest)
{
    int ret = 0;

    for (UnitTest* test: _testList()) {
        if (singleTest.isEmpty() || singleTest == test->objectName()) {
            if (test->standalone() && singleTest.isEmpty()) {
                continue;
            }
            QStringList args;
            args << "*" << "-maxwarnings" << "0";
            ret += QTest::qExec(test, args);
        }
    }

    return ret;
}

/// @brief Called before each test.
///         Make sure to call first in your derived class
void UnitTest::init(void)
{
    _initCalled = true;
}

/// @brief Called after each test.
///         Make sure to call first in your derived class
void UnitTest::cleanup(void)
{
    _cleanupCalled = true;

    // Don't let any lingering signals or events cross to the next unit test.
    // If you have a failure whose stack trace points to this then
    // your test is leaking signals or events. It could cause use-after-free or
    // segmentation faults from wild pointers.
    qmlApp()->processEvents();
}
