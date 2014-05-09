#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>
#include <QSslError>
#include <QVariantMap>
#include "loginmanager.h"

class Request : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LoginManager* loginManager READ loginManager WRITE setLoginManager)
    Q_PROPERTY(QString query READ query WRITE setQuery)
    Q_PROPERTY(QString token READ token WRITE setToken)
    Q_PROPERTY(QString locale READ locale WRITE setLocale)
public:
    explicit Request(QObject *parent = 0);
    Q_INVOKABLE void send();

    LoginManager* loginManager() const;
    void setLoginManager(LoginManager* l);

    QString query() const;
    void setQuery(const QString &query);

    QString token() const;
    void setToken(const QString &t);

    QString locale() const;
    void setLocale(const QString &l);

signals:
    void complete(QVariant json);
    void error();

public slots:
    void finished(QNetworkReply* reply);
    //void error(QNetworkReply::NetworkError err);
    //void sslError(QList<QSslError>);

protected:
    LoginManager* lm;
    QString req;
    QNetworkAccessManager m;

    QString q;
    QString tok;
    QString loc;


};

#endif // REQUEST_H
