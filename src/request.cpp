#include "request.h"
#include <QtCore/QDebug>
#include <QJsonDocument>
#include <QUrl>
#include <QUrlQuery>

Request::Request(QNetworkReply* r, QObject *parent) :
    QObject(parent) , reply(r)
{
}

Request::~Request(){
    qDebug() << "Request destructor";
}

void Request::finished(){
    QNetworkReply::NetworkError err = this->reply->error();
    if(err != QNetworkReply::NoError){
        qDebug() << "Fallo el request n: " << err << " str: '" << reply->errorString() << "'";
        emit error();
        return;
    }

    QByteArray data = this->reply->readAll();
    qDebug() << "End request -- " /*<< data*/;
    QJsonDocument dataDoc(QJsonDocument::fromJson(data));
    //TODO: check if there is an apiError!
    emit complete(dataDoc.toVariant());
    this->reply->close();
    this->reply->deleteLater();
}

void Request::upProg(qint64 bytes, qint64 bytesTotal){
    emit uploadProgress(bytes, bytesTotal);
}

void Request::downProg(qint64 bytes, qint64 bytesTotal){
    //qDebug() << "bytes " << bytes << " total " << bytesTotal;
    emit downloadProgress(bytes, bytesTotal);
}

/*QString Request::query() const{
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
}*/

//Request* Request::create(){
//    return new Request();
//}

void Request::destroy(){
    delete this;
}

