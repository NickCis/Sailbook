#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <QObject>
#include <QVariant>
#include <QJsonObject>

class Configurator : public QObject
{
    Q_OBJECT
public:
    explicit Configurator(QObject *parent = 0);
    Q_INVOKABLE bool load();
    Q_INVOKABLE bool save();
    Q_INVOKABLE void setValue(QString name, QVariant value);
    Q_INVOKABLE QVariant getValue(QString name);

signals:

public slots:

protected:
    QString filePath;
    QJsonObject config;

};

#endif // CONFIGURATOR_H
