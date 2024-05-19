/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include <QObject>
#include <QString>
#include <QUrl>
#include <QColor>

class QMLOptions;

class QMLOptions : public QObject
{
    Q_OBJECT
public:
    QMLOptions(QObject* parent = nullptr);

};
