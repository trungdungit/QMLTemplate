#pragma once

#include <QObject>
#include <QUrl>

class QMLSettings : public QObject
{
    Q_OBJECT
public:
    QMLSettings(QString title, QUrl url, QUrl icon = QUrl());

    Q_PROPERTY(QString  title       READ title      CONSTANT)
    Q_PROPERTY(QUrl     url         READ url        CONSTANT)
    Q_PROPERTY(QUrl     icon        READ icon       CONSTANT)

    virtual QString     title       () { return _title; }
    virtual QUrl        url         () { return _url;   }
    virtual QUrl        icon        () { return _icon;  }

protected:
    QString _title;
    QUrl    _url;
    QUrl    _icon;
};
