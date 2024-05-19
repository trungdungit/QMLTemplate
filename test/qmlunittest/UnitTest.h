#pragma once

#include <QObject>
#include <QtTest>
#include <QMessageBox>
#include <QFileDialog>

#include "Fact.h"

#define UT_REGISTER_TEST(className)             static UnitTestWrapper<className> className(#className, false);
#define UT_REGISTER_TEST_STANDALONE(className)  static UnitTestWrapper<className> className(#className, true);  // Test will only be run with specifically called to from command line


class UnitTest : public QObject
{
    Q_OBJECT

public:
    UnitTest(void);
    virtual ~UnitTest(void);

    /// @brief Called to run all the registered unit tests
    ///     @param singleTest Name of test to just run a single test
    static int run(QString& singleTest);

    bool standalone(void) const{ return _standalone; }
    void setStandalone(bool standalone) { _standalone = standalone; }

    /// @brief Adds a unit test to the list. Should only be called by UnitTestWrapper.
    static void _addTest(UnitTest* test);

protected slots:

    // These are all pure virtuals to force the derived class to implement each one and in turn
    // call the UnitTest private implementation.

    /// @brief Called before each test.
    ///         Make sure to call UnitTest::init first in your derived class.
    virtual void init(void);

    /// @brief Called after each test.
    ///         Make sure to call UnitTest::cleanup last in your derived class.
    virtual void cleanup(void);

private:
    void _unitTestCalled(void);
    static QList<UnitTest*>& _testList(void);

    bool _unitTestRun   = false;    ///< true: Unit Test was run
    bool _initCalled    = false;    ///< true: UnitTest::_init was called
    bool _cleanupCalled = false;    ///< true: UnitTest::_cleanup was called
    bool _standalone    = false;    ///< true: Only run when requested specifically from command line
};

template <class T>
class UnitTestWrapper {
public:
    UnitTestWrapper(const QString& name, bool standalone)
        : _unitTest(new T)
    {
        _unitTest->setObjectName(name);
        _unitTest->setStandalone(standalone);
        UnitTest::_addTest(_unitTest.data());
    }

private:
    QSharedPointer<T> _unitTest;
};
