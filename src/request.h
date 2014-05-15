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
    Q_PROPERTY(QString locale READ locale WRITE setLocale)
    Q_PROPERTY(RequestType type READ getType WRITE setType)
    Q_ENUMS(RequestType)
public:
    enum RequestType {
        Get = 0,
        Post,
        Delete
    };

    explicit Request(QObject *parent = 0);
    Q_INVOKABLE void send();

    Q_INVOKABLE Request* createRequest(){
        return new Request();
    }

    Q_INVOKABLE void destroy();

    LoginManager* loginManager() const;
    void setLoginManager(LoginManager* l);

    QString query() const;
    void setQuery(const QString &query);

    QString locale() const;
    void setLocale(const QString &l);

    RequestType getType() const;
    void setType(const RequestType &t);


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
    QString loc;
    RequestType type;


};

#endif // REQUEST_H
