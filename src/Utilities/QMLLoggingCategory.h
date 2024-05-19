/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include <QLoggingCategory>
#include <QStringList>
#include <QObject>

// Add Global logging categories (not class specific) here using Q_DECLARE_LOGGING_CATEGORY
Q_DECLARE_LOGGING_CATEGORY(AppLog)

/// @def QML_LOGGING_CATEGORY
/// This is a QML specific replacement for Q_LOGGING_CATEGORY. It will register the category name into a
/// global list. It's usage is the same as Q_LOGGING_CATEOGRY.
#define QML_LOGGING_CATEGORY(name, ...) \
    static QMLLoggingCategory QMLCategory ## name (__VA_ARGS__); \
    Q_LOGGING_CATEGORY(name, __VA_ARGS__)

class QMLLoggingCategoryRegister : public QObject
{
    Q_OBJECT

public:
    static QMLLoggingCategoryRegister* instance(void);

    /// Registers the specified logging category to the system.
    void registerCategory(const char* category) { _registeredCategories << category; }

    /// Returns the list of available logging category names.
    Q_INVOKABLE QStringList registeredCategories(void);

    /// Turns on/off logging for the specified category. State is saved in app settings.
    Q_INVOKABLE void setCategoryLoggingOn(const QString& category, bool enable);

    /// Returns true if logging is turned on for the specified category.
    Q_INVOKABLE bool categoryLoggingOn(const QString& category);

    /// Sets the logging filters rules from saved settings.
    ///     @param commandLineLogggingOptions Logging options which were specified on the command line
    void setFilterRulesFromSettings(const QString& commandLineLoggingOptions);

private:
    QMLLoggingCategoryRegister(void) { }
    
    QStringList _registeredCategories;
    QString     _commandLineLoggingOptions;

    static const char* _filterRulesSettingsGroup;
};
        
class QMLLoggingCategory
{
public:
    QMLLoggingCategory(const char* category) { QMLLoggingCategoryRegister::instance()->registerCategory(category); }
};
