#include "request.h"
#include <QtCore/QDebug>
#include <QJsonDocument>
#include <QUrl>
#include <QUrlQuery>

//#define BASE_URL "https://graph.facebook.com/v2.0/"
#define FB_SCHEME "https"
#define FB_HOST "graph.facebook.com"
#define FB_BASE_PATH "/v2.0"


Request::Request(QObject *parent) :
    QObject(parent) , lm(NULL), req(""), m(this), q(""), loc(""), type(Request::Get)
{
}

void Request::send() {
    QNetworkRequest request;
    QUrl url(this->q);

    if(!url.path().startsWith(QStringLiteral(FB_BASE_PATH))){
        QString path(FB_BASE_PATH);
        path += url.path();
        url.setPath(path);
    }

    if(url.scheme() == "")
        url.setScheme(QStringLiteral(FB_SCHEME));

    if(url.host() == "")
        url.setHost(QStringLiteral(FB_HOST));

    QUrlQuery query(url);
    if(! query.hasQueryItem(QStringLiteral("access_token")))
        query.addQueryItem(QStringLiteral("access_token"), this->lm->getToken());

    if(this->loc != "" && !query.hasQueryItem(QStringLiteral("locale")))
        query.addQueryItem(QStringLiteral("locale"), this->loc);

    url.setQuery(query);

    qDebug() << "pagina: " << url.toString();
    request.setUrl(url);

    //request.setRawHeader("User-Agent", "Sailbook 0.1");

    connect(&this->m, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
    //connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
    //        this, SLOT(error(QNetworkReply::NetworkError)));
    //connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
    //        this, SLOT(sslErrors(QList<QSslError>)));

    qDebug() << "type " << this->type;
    if(this->type == Request::Post){
        QByteArray data;
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        this->m.post(request, data);
    }else if(this->type == Request::Delete)
        this->m.deleteResource(request);
    else
        this->m.get(request);

}

void Request::finished(QNetworkReply* reply){
    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError){
        qDebug() << "Fallo el request n: " << err << " str: '" << reply->errorString() << "'";
        emit error();
        return;
    }

    QByteArray data = reply->readAll();
    qDebug() << "End request -- " /*<< data*/;
    QJsonDocument dataDoc(QJsonDocument::fromJson(data));
    emit complete(dataDoc.toVariant());
    reply->close();
    reply->deleteLater();
}

/*void Request::error(QNetworkReply::NetworkError err){
    qDebug() << "Error" << err;
    emit error();
}*/

/*void Request::sslError(QList<QSslError> errs){
}*/

LoginManager* Request::loginManager() const{
    return this->lm;
}

void Request::setLoginManager(LoginManager *l){
    this->lm = l;
}

QString Request::query() const{
    return this->q;
}

void Request::setQuery(const QString &query){
    this->q = query;
}

QString Request::locale() const{
    return this->loc;
}

void Request::setLocale(const QString &l){
    this->loc = l;
}

Request::RequestType Request::getType() const{
    return this->type;
}

void Request::setType(const Request::RequestType &t){
    this->type = t;
}

//Request* Request::create(){
//    return new Request();
//}
void Request::destroy(){
    delete this;
}

