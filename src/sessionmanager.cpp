#include "sessionmanager.h"
#include <QUrl>
#include <QUrlQuery>
#include <QtCore/QDebug>
#include <QJsonDocument>
#include <QtCore/QDebug>
#include <QtCore/QRegExp>

#define LOGIN_URL "https://m.facebook.com/dialog/oauth?client_id=%1&redirect_uri=https://www.facebook.com/connect/login_success.html&response_type=token"
#define FB_SCHEME "https"
#define FB_HOST "graph.facebook.com"
#define FB_BASE_PATH "/v2.0"


SessionManager::SessionManager(QString id, QObject *parent) :
    QObject(parent), appId(id), token(""){
}

SessionManager::SessionManager(QString id, QString t, QObject *parent) :
    QObject(parent), appId(id), token(t){
}

QString SessionManager::getAuthUrl(){
    QString url(LOGIN_URL);
    url = url.arg(this->appId);

    if(!this->permissions.empty()){
        url += "&scope="+ this->permissions.join(",");
    }

    return url;
}

QString SessionManager::getToken(){
    return this->token;
}

void SessionManager::checkUrl(const QUrl &url){
    QString urlToString = url.toString();
    //qDebug() << "url: " << urlToString;
    // Check if the URL is not good
    if (!urlToString.contains(this->appId)) {
        if (urlToString.contains("https://www.facebook.com/connect/login_success.html")) {
            // Get the token
            QRegExp tokenRegExp ("access_token=([^&]*)&");
            if (url.fragment().indexOf(tokenRegExp) != -1) {
                this->token = tokenRegExp.cap(1);

                qDebug() << "Login succeded token:" << this->token;
                emit newToken(this->token);
                return;
            } else {
                qDebug() << "Login failed";
                emit apiError();
                return;
            }
        }

        // Allow oauth
        if (urlToString.contains("oauth")) {
            return;
        }

        qDebug() << "The user clicked on a wrong link !";
        //login();
    }
}

void SessionManager::setExtendedPermission(SessionManager::ExtendedPermissions extendedPermissions){
    if (extendedPermissions.testFlag(SessionManager::Email)) {
        this->permissions.append("email");
    }
    if (extendedPermissions.testFlag(SessionManager::ManageNotifications)) {
        this->permissions.append("manage_notifications");
    }
    if (extendedPermissions.testFlag(SessionManager::ManagePages)) {
        this->permissions.append("manage_pages");
    }
    if (extendedPermissions.testFlag(SessionManager::PublishActions)) {
        this->permissions.append("publish_actions");
    }
    if (extendedPermissions.testFlag(SessionManager::ReadFriendList)) {
        this->permissions.append("read_friendlists");
    }
    if (extendedPermissions.testFlag(SessionManager::ReadInsights)) {
        this->permissions.append("read_insights");
    }
    if (extendedPermissions.testFlag(SessionManager::ReadMailbox)) {
        this->permissions.append("read_mailbox");
    }
    if (extendedPermissions.testFlag(SessionManager::ReadPageMailboxes)) {
        this->permissions.append("read_page_mailboxes");
    }
    if (extendedPermissions.testFlag(SessionManager::ReadStream)) {
        this->permissions.append("read_stream");
    }
    if (extendedPermissions.testFlag(SessionManager::RsvpEvent)) {
        this->permissions.append("rsvp_event");
    }
}

void SessionManager::setUserDataPermission(SessionManager::UserDataPermissions userDataPermissions){
    if (userDataPermissions.testFlag(SessionManager::UserAboutMe)) {
        this->permissions.append("user_about_me");
    }
    if (userDataPermissions.testFlag(SessionManager::UserActionsBooks)) {
        this->permissions.append("user_actions.books");
    }
    if (userDataPermissions.testFlag(SessionManager::UserActionsMusic)) {
        this->permissions.append("user_actions.music");
    }
    if (userDataPermissions.testFlag(SessionManager::UserActionsNews)) {
        this->permissions.append("user_actions.news");
    }
    if (userDataPermissions.testFlag(SessionManager::UserActionsVideo)) {
        this->permissions.append("user_actions.video");
    }
    if (userDataPermissions.testFlag(SessionManager::UserActivities)) {
        this->permissions.append("user_activities");
    }
    if (userDataPermissions.testFlag(SessionManager::UserBirthday)) {
        this->permissions.append("user_birthday");
    }
    if (userDataPermissions.testFlag(SessionManager::UserEducationHistory)) {
        this->permissions.append("user_education_history");
    }
    if (userDataPermissions.testFlag(SessionManager::UserEvents)) {
        this->permissions.append("user_events");
    }
    if (userDataPermissions.testFlag(SessionManager::UserFriends)) {
        this->permissions.append("user_friends");
    }
    if (userDataPermissions.testFlag(SessionManager::UserGamesActivity)) {
        this->permissions.append("user_games_activity");
    }
    if (userDataPermissions.testFlag(SessionManager::UserGroups)) {
        this->permissions.append("user_groups");
    }
    if (userDataPermissions.testFlag(SessionManager::UserHometown)) {
        this->permissions.append("user_hometown");
    }
    if (userDataPermissions.testFlag(SessionManager::UserInterests)) {
        this->permissions.append("user_interests");
    }
    if (userDataPermissions.testFlag(SessionManager::UserLikes)) {
        this->permissions.append("user_likes");
    }
    if (userDataPermissions.testFlag(SessionManager::UserLocation)) {
        this->permissions.append("user_location");
    }
    if (userDataPermissions.testFlag(SessionManager::UserPhotos)) {
        this->permissions.append("user_photos");
    }
    if (userDataPermissions.testFlag(SessionManager::UserRelationshipDetails)) {
        this->permissions.append("user_relationship_details");
    }
    if (userDataPermissions.testFlag(SessionManager::UserRelationships)) {
        this->permissions.append("user_relationships");
    }
    if (userDataPermissions.testFlag(SessionManager::UserReligionPolitics)) {
        this->permissions.append("user_religion_politics");
    }
    if (userDataPermissions.testFlag(SessionManager::UserStatus)) {
        this->permissions.append("user_status");
    }
    if (userDataPermissions.testFlag(SessionManager::UserTaggedPlaces)) {
        this->permissions.append("user_tagged_places");
    }
    if (userDataPermissions.testFlag(SessionManager::UserVideos)) {
        this->permissions.append("user_videos");
    }
    if (userDataPermissions.testFlag(SessionManager::UserWebsite)) {
        this->permissions.append("user_website");
    }
    if (userDataPermissions.testFlag(SessionManager::UserWorkHistory)) {
        this->permissions.append("user_work_history");
    }
}

void SessionManager::clearPermissions(){
    this->permissions.clear();
}

Request* SessionManager::createRequest(const QString &reqStr, QObject *parent){
    qDebug() << "createRequest con get default";
    return this->createRequest(reqStr, Request::Get, parent);
}

Request* SessionManager::createRequest(const QString &reqStr, const int &type, QObject *parent){
    return this->createRequest(reqStr, (Request::RequestType) type, parent);
}

Request* SessionManager::createRequest(const QString &reqStr, const Request::RequestType &type, QObject *parent){
    QNetworkRequest request;
    QNetworkReply* reply;
    QUrl url(reqStr);

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
        query.addQueryItem(QStringLiteral("access_token"), this->token);

    //TODO: locale support
    //if(this->loc != "" && !query.hasQueryItem(QStringLiteral("locale")))
    //    query.addQueryItem(QStringLiteral("locale"), this->loc);

    url.setQuery(query);

    qDebug() << "pagina: " << url.toString();
    request.setUrl(url);

    request.setRawHeader("User-Agent", "Sailbook 0.1");

    //connect(&this->m, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
    //connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
    //        this, SLOT(error(QNetworkReply::NetworkError)));
    //connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
    //        this, SLOT(sslErrors(QList<QSslError>)));


    qDebug() << "type " << type;

    if(type == Request::Post){
        QByteArray data;
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        reply = this->man.post(request, data);
    }else if(type == Request::Delete)
        reply = this->man.deleteResource(request);
    else
        reply = this->man.get(request);

    if(!parent)
        parent = reply;

    Request* req = new Request(reply, parent);
    connect(reply, SIGNAL(finished()), req, SLOT(finished()));
    connect(reply, SIGNAL(uploadProgress(qint64, qint64)), req, SLOT(upProg(qint64, qint64)));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), req, SLOT(downProg(qint64,qint64)));

    return req;
}
