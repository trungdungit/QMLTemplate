/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include <QJsonObject>
#include <QVariantList>
#include <QGeoCoordinate>
#include <QCoreApplication>
#include <QFileInfo>

/// @file
/// @author Don Gagne <don@thegagnes.com>

class QmlObjectListModel;

/// @brief Json manipulation helper class.
/// Primarily used for parsing and processing Fact metadata.
class JsonHelper
{
    Q_DECLARE_TR_FUNCTIONS(JsonHelper)

public:
    /// Determines is the specified file is a json file
    /// @return true: file is json, false: file is not json
    static bool isJsonFile(const QString&       fileName,       ///< filename
                           QJsonDocument&       jsonDoc,        ///< returned json document
                           QString&             errorString);   ///< error on parse failure

    /// Determines is the specified data is a json file
    /// @return true: file is json, false: file is not json
    static bool isJsonFile(const QByteArray&    bytes,          ///< json bytes
                           QJsonDocument&       jsonDoc,        ///< returned json document
                           QString&             errorString);   ///< error on parse failure

    /// Saves the standard file header the json object
    static void saveQMLJsonFileHeader(QJsonObject&      jsonObject, ///< root json object
                                      const QString&    fileType,   ///< file type for file
                                      int               version);   ///< version number for file

    /// Validates the standard parts of an external QML json file (Plan file, ...):
    ///     jsonFileTypeKey - Required and checked to be equal to expectedFileType
    ///     jsonVersionKey - Required and checked to be below supportedMajorVersion, supportedMinorVersion
    ///     jsonGroundStationKey - Required and checked to be string type
    /// @return false: validation failed, errorString set
    static bool validateExternalQMLJsonFile(const QJsonObject&  jsonObject,             ///< json object to validate
                                            const QString&      expectedFileType,       ///< correct file type for file
                                            int                 minSupportedVersion,    ///< minimum supported version
                                            int                 maxSupportedVersion,    ///< maximum supported major version
                                            int                 &version,               ///< returned file version
                                            QString&            errorString);           ///< returned error string if validation fails

    /// Validates the standard parts of a internal QML json file (FactMetaData, ...):
    ///     jsonFileTypeKey - Required and checked to be equal to expectedFileType
    ///     jsonVersionKey - Required and checked to be below supportedMajorVersion, supportedMinorVersion
    ///     jsonGroundStationKey - Required and checked to be string type
    /// @return false: validation failed, errorString set
    static bool validateInternalQMLJsonFile(const QJsonObject&  jsonObject,             ///< json object to validate
                                            const QString&      expectedFileType,       ///< correct file type for file
                                            int                 minSupportedVersion,    ///< minimum supported version
                                            int                 maxSupportedVersion,    ///< maximum supported major version
                                            int                 &version,               ///< returned file version
                                            QString&            errorString);           ///< returned error string if validation fails

    // Opens, validates and translates an internal QML json file.
    // @return Json root object for file. Empty QJsonObject if error.
    static QJsonObject openInternalQMLJsonFile(const QString& jsonFilename,             ///< Json file to open
                                               const QString&      expectedFileType,    ///< correct file type for file
                                               int                 minSupportedVersion, ///< minimum supported version
                                               int                 maxSupportedVersion, ///< maximum supported major version
                                               int                 &version,            ///< returned file version
                                               QString&            errorString);        ///< returned error string if validation fails

    /// Validates that the specified keys are in the object
    /// @return false: validation failed, errorString set
    static bool validateRequiredKeys(const QJsonObject& jsonObject, ///< json object to validate
                                     const QStringList& keys,       ///< keys which are required to be present
                                     QString& errorString);         ///< returned error string if validation fails

    /// Validates the types of specified keys are in the object
    /// @return false: validation failed, errorString set
    static bool validateKeyTypes(const QJsonObject& jsonObject,         ///< json object to validate
                                 const QStringList& keys,               ///< keys to validate
                                 const QList<QJsonValue::Type>& types,  ///< required type for each key, QJsonValue::Null specifies double with possible NaN
                                 QString& errorString);                 ///< returned error string if validation fails

    typedef struct {
        const char*         key;        ///< json key name
        QJsonValue::Type    type;       ///< required type for key, QJsonValue::Null specifies double with possible NaN
        bool                required;   ///< true: key must be present
    } KeyValidateInfo;

    static bool validateKeys(const QJsonObject& jsonObject, const QList<KeyValidateInfo>& keyInfo, QString& errorString);

    /// Returns NaN if the value is null, or if not, the double value
    static double possibleNaNJsonValue(const QJsonValue& value);

    static const char* jsonVersionKey;
    static const char* jsonGroundStationKey;
    static const char* jsonGroundStationValue;
    static const char* jsonFileTypeKey;

private:
    static QString _jsonValueTypeToString(QJsonValue::Type type);

    static QStringList _addDefaultLocKeys(QJsonObject& jsonObject);
    static QJsonObject _translateRoot(QJsonObject& jsonObject, const QString& translateContext, const QStringList& translateKeys);
    static QJsonObject _translateObject(QJsonObject& jsonObject, const QString& translateContext, const QStringList& translateKeys);
    static QJsonArray _translateArray(QJsonArray& jsonArray, const QString& translateContext, const QStringList& translateKeys);

    static const char*  _translateKeysKey;
    static const char*  _arrayIDKeysKey;
};
