#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>
#include <QVariantMap>

class Request : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString query READ query WRITE setQuery)
    //Q_PROPERTY(QString locale READ locale WRITE setLocale)
    //Q_PROPERTY(RequestType type READ getType WRITE setType)
    Q_ENUMS(RequestType)
public:
    enum RequestType {
        Get = 0,
        Post,
        Delete
    };

    explicit Request(QNetworkReply* r, QObject *parent = 0);
    ~Request();
    //Q_INVOKABLE void send();
    //XXX: hay qe usar deleteLater?
    Q_INVOKABLE void destroy();

    //QString query() const;
    //void setQuery(const QString &query);

    //QString locale() const;
    //void setLocale(const QString &l);

    //RequestType getType() const;
    //void setType(const RequestType &t);


signals:
    void complete(QVariant json);
    void error();
    void apiError();
    void uploadProgress(qint64 bytes, qint64 bytesTotal);
    void downloadProgress(qint64 bytes, qint64 bytesTotal);

public slots:
    void finished();
    void upProg(qint64 bytes, qint64 bytesTotal);
    void downProg(qint64 bytes, qint64 bytesTotal);
    //void error(QNetworkReply::NetworkError err);
    //void sslError(QList<QSslError>);

protected:
    QNetworkReply* reply;
};

#endif // REQUEST_H
