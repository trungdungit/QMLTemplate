/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "JsonHelper.h"
#include "QmlObjectListModel.h"
#include "FactMetaData.h"
#include "QMLApplication.h"

#include <QJsonArray>
#include <QJsonParseError>
#include <QObject>
#include <QFile>

const char* JsonHelper::jsonVersionKey                      = "version";
const char* JsonHelper::jsonGroundStationKey                = "groundStation";
const char* JsonHelper::jsonGroundStationValue              = "QGroundControl";
const char* JsonHelper::jsonFileTypeKey                     = "fileType";
const char* JsonHelper::_translateKeysKey                   = "translateKeys";
const char* JsonHelper::_arrayIDKeysKey                     = "_arrayIDKeys";

bool JsonHelper::validateRequiredKeys(const QJsonObject& jsonObject, const QStringList& keys, QString& errorString)
{
    QString missingKeys;

    foreach(const QString& key, keys) {
        if (!jsonObject.contains(key)) {
            if (!missingKeys.isEmpty()) {
                missingKeys += QStringLiteral(", ");
            }
            missingKeys += key;
        }
    }

    if (missingKeys.length() != 0) {
        errorString = QObject::tr("The following required keys are missing: %1").arg(missingKeys);
        return false;
    }

    return true;
}

bool JsonHelper::validateKeyTypes(const QJsonObject& jsonObject, const QStringList& keys, const QList<QJsonValue::Type>& types, QString& errorString)
{
    for (int i=0; i<types.count(); i++) {
        QString valueKey = keys[i];
        if (jsonObject.contains(valueKey)) {
            const QJsonValue& jsonValue = jsonObject[valueKey];
            if (jsonValue.type() == QJsonValue::Null &&  types[i] == QJsonValue::Double) {
                // Null type signals a NaN on a double value
                continue;
            }
            if (jsonValue.type() != types[i]) {
                errorString  = QObject::tr("Incorrect value type - key:type:expected %1:%2:%3").arg(valueKey).arg(_jsonValueTypeToString(jsonValue.type())).arg(_jsonValueTypeToString(types[i]));
                return false;
            }
        }
    }

    return true;
}

bool JsonHelper::isJsonFile(const QByteArray& bytes, QJsonDocument& jsonDoc, QString& errorString)
{
    QJsonParseError parseError;

    jsonDoc = QJsonDocument::fromJson(bytes, &parseError);

    if (parseError.error == QJsonParseError::NoError) {
        return true;
    } else {
        int startPos = qMax(0, parseError.offset - 100);
        int length = qMin(bytes.length() - startPos, 200);
        qDebug() << QStringLiteral("Json read error '%1'").arg(bytes.mid(startPos, length).constData());
        errorString = parseError.errorString();
        return false;
    }
}

bool JsonHelper::isJsonFile(const QString& fileName, QJsonDocument& jsonDoc, QString& errorString)
{
    QFile jsonFile(fileName);
    if (!jsonFile.open(QFile::ReadOnly)) {
        errorString = tr("File open failed: file:error %1 %2").arg(jsonFile.fileName()).arg(jsonFile.errorString());
        return false;
    }
    QByteArray jsonBytes = jsonFile.readAll();
    jsonFile.close();

    return isJsonFile(jsonBytes, jsonDoc, errorString);
}

bool JsonHelper::validateInternalQMLJsonFile(const QJsonObject& jsonObject,
                                             const QString&     expectedFileType,
                                             int                minSupportedVersion,
                                             int                maxSupportedVersion,
                                             int&               version,
                                             QString&           errorString)
{
    // Validate required keys
    QList<JsonHelper::KeyValidateInfo> requiredKeys = {
        { jsonFileTypeKey,       QJsonValue::String, true },
        { jsonVersionKey,        QJsonValue::Double, true },
    };
    if (!JsonHelper::validateKeys(jsonObject, requiredKeys, errorString)) {
        return false;
    }

    // Make sure file type is correct
    QString fileTypeValue = jsonObject[jsonFileTypeKey].toString();
    if (fileTypeValue != expectedFileType) {
        errorString = QObject::tr("Incorrect file type key expected:%1 actual:%2").arg(expectedFileType).arg(fileTypeValue);
        return false;
    }

    // Version check
    version = jsonObject[jsonVersionKey].toInt();
    if (version < minSupportedVersion) {
        errorString = QObject::tr("File version %1 is no longer supported").arg(version);
        return false;
    }
    if (version > maxSupportedVersion) {
        errorString = QObject::tr("File version %1 is newer than current supported version %2").arg(version).arg(maxSupportedVersion);
        return false;
    }

    return true;
}

bool JsonHelper::validateExternalQMLJsonFile(const QJsonObject& jsonObject,
                                             const QString&     expectedFileType,
                                             int                minSupportedVersion,
                                             int                maxSupportedVersion,
                                             int&               version,
                                             QString&           errorString)
{
    // Validate required keys
    QList<JsonHelper::KeyValidateInfo> requiredKeys = {
        { jsonGroundStationKey, QJsonValue::String, true },
    };
    if (!JsonHelper::validateKeys(jsonObject, requiredKeys, errorString)) {
        return false;
    }

    return validateInternalQMLJsonFile(jsonObject, expectedFileType, minSupportedVersion, maxSupportedVersion, version, errorString);
}

QStringList JsonHelper::_addDefaultLocKeys(QJsonObject& jsonObject)
{
    QString translateKeys;
    QString fileType = jsonObject[jsonFileTypeKey].toString();
    if (!fileType.isEmpty()) {
        if (fileType == "") {
            if (jsonObject.contains(_translateKeysKey)) {
                translateKeys = jsonObject[_translateKeysKey].toString();
            } else {
                translateKeys = "label,enumStrings,friendlyName,description,category";
                jsonObject[_translateKeysKey] = translateKeys;
            }
            if (!jsonObject.contains(_arrayIDKeysKey)) {
                jsonObject[_arrayIDKeysKey] = "rawName,comment";
            }
        } else if (fileType == FactMetaData::qmlFileType) {
            if (jsonObject.contains(_translateKeysKey)) {
                translateKeys = jsonObject[_translateKeysKey].toString();
            } else {
                translateKeys = "shortDescription,longDescription,enumStrings";
                jsonObject[_translateKeysKey] = "shortDescription,longDescription,enumStrings";
            }
            if (!jsonObject.contains(_arrayIDKeysKey)) {
                jsonObject[_arrayIDKeysKey] = "name";
            }
        }
    }
    return translateKeys.split(",");
}

QJsonObject JsonHelper::_translateObject(QJsonObject& jsonObject, const QString& translateContext, const QStringList& translateKeys)
{
    for (const QString& key: jsonObject.keys()) {
        if (jsonObject[key].isString()) {
            QString locString = jsonObject[key].toString();
            if (translateKeys.contains(key)) {
                QString disambiguation;
                QString disambiguationPrefix("#loc.disambiguation#");

                if (locString.startsWith(disambiguationPrefix)) {
                    locString = locString.right(locString.length() - disambiguationPrefix.length());
                    int commentEndIndex = locString.indexOf("#");
                    if (commentEndIndex != -1) {
                        disambiguation = locString.left(commentEndIndex);
                        locString = locString.right(locString.length() - disambiguation.length() - 1);
                    }
                }

                QString xlatString = qmlApp()->qmlJSONTranslator().translate(translateContext.toUtf8().constData(), locString.toUtf8().constData(), disambiguation.toUtf8().constData());
                if (!xlatString.isNull()) {
                    jsonObject[key] = xlatString;
                }
            }
        } else if (jsonObject[key].isArray()) {
            QJsonArray childJsonArray = jsonObject[key].toArray();
            jsonObject[key] = _translateArray(childJsonArray, translateContext, translateKeys);
        } else if (jsonObject[key].isObject()) {
            QJsonObject childJsonObject = jsonObject[key].toObject();
            jsonObject[key] = _translateObject(childJsonObject, translateContext, translateKeys);
        }
    }

    return jsonObject;
}

QJsonArray JsonHelper::_translateArray(QJsonArray& jsonArray, const QString& translateContext, const QStringList& translateKeys)
{
    for (int i=0; i<jsonArray.count(); i++) {
        QJsonObject childJsonObject = jsonArray[i].toObject();
        jsonArray[i] = _translateObject(childJsonObject, translateContext, translateKeys);
    }

    return jsonArray;
}

QJsonObject JsonHelper::_translateRoot(QJsonObject& jsonObject, const QString& translateContext, const QStringList& translateKeys)
{
    return _translateObject(jsonObject, translateContext, translateKeys);
}

QJsonObject JsonHelper::openInternalQMLJsonFile(const QString&  jsonFilename,
                                                const QString&  expectedFileType,
                                                int             minSupportedVersion,
                                                int             maxSupportedVersion,
                                                int             &version,
                                                QString&        errorString)
{
    QFile jsonFile(jsonFilename);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        errorString = tr("Unable to open file: '%1', error: %2").arg(jsonFilename).arg(jsonFile.errorString());
        return QJsonObject();
    }

    QByteArray bytes = jsonFile.readAll();
    jsonFile.close();
    QJsonParseError jsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(bytes, &jsonParseError);
    if (jsonParseError.error != QJsonParseError::NoError) {
        errorString = tr("Unable to parse json file: %1 error: %2 offset: %3").arg(jsonFilename).arg(jsonParseError.errorString()).arg(jsonParseError.offset);
        return QJsonObject();
    }

    if (!doc.isObject()) {
        errorString = tr("Root of json file is not object: %1").arg(jsonFilename);
        return QJsonObject();
    }

    QJsonObject jsonObject = doc.object();
    bool success = validateInternalQMLJsonFile(jsonObject, expectedFileType, minSupportedVersion, maxSupportedVersion, version, errorString);
    if (!success) {
        errorString = tr("Json file: '%1'. %2").arg(jsonFilename).arg(errorString);
        return QJsonObject();
    }

    QStringList translateKeys = _addDefaultLocKeys(jsonObject);
    QString context = QFileInfo(jsonFile).fileName();
    return _translateRoot(jsonObject, context, translateKeys);
}

void JsonHelper::saveQMLJsonFileHeader(QJsonObject&     jsonObject,
                                       const QString&   fileType,
                                       int              version)
{
    jsonObject[jsonGroundStationKey] = jsonGroundStationValue;
    jsonObject[jsonFileTypeKey] = fileType;
    jsonObject[jsonVersionKey] = version;
}

bool JsonHelper::validateKeys(const QJsonObject& jsonObject, const QList<JsonHelper::KeyValidateInfo>& keyInfo, QString& errorString)
{
    QStringList             keyList;
    QList<QJsonValue::Type> typeList;

    for (int i=0; i<keyInfo.count(); i++) {
        if (keyInfo[i].required) {
            keyList.append(keyInfo[i].key);
        }
    }
    if (!validateRequiredKeys(jsonObject, keyList, errorString)) {
        return false;
    }

    keyList.clear();
    for (int i=0; i<keyInfo.count(); i++) {
        keyList.append(keyInfo[i].key);
        typeList.append(keyInfo[i].type);
    }
    return validateKeyTypes(jsonObject, keyList, typeList, errorString);
}

QString JsonHelper::_jsonValueTypeToString(QJsonValue::Type type)
{
    const struct {
        QJsonValue::Type    type;
        const char*         string;
    } rgTypeToString[] = {
    { QJsonValue::Null,         "NULL" },
    { QJsonValue::Bool,         "Bool" },
    { QJsonValue::Double,       "Double" },
    { QJsonValue::String,       "String" },
    { QJsonValue::Array,        "Array" },
    { QJsonValue::Object,       "Object" },
    { QJsonValue::Undefined,    "Undefined" },
};

    for (size_t i=0; i<sizeof(rgTypeToString)/sizeof(rgTypeToString[0]); i++) {
        if (type == rgTypeToString[i].type) {
            return rgTypeToString[i].string;
        }
    }

    return QObject::tr("Unknown type: %1").arg(type);
}

double JsonHelper::possibleNaNJsonValue(const  QJsonValue& value)
{
    if (value.type() == QJsonValue::Null) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return value.toDouble();
    }
}
