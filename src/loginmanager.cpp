#include "loginmanager.h"
#include <QtCore/QDebug>
#include <QtCore/QRegExp>

#define LOGIN_URL "https://m.facebook.com/dialog/oauth?client_id=%1&redirect_uri=https://www.facebook.com/connect/login_success.html&response_type=token"

LoginManager::LoginManager(QString id, QObject *parent) :
    QObject(parent), appId(id), token(""){
}

LoginManager::LoginManager(QString id, QString t, QObject *parent) :
    QObject(parent), appId(id), token(t){
}

QString LoginManager::getAuthUrl(){
    QString url(LOGIN_URL);
    url = url.arg(this->appId);

    if(!this->permissions.empty()){
        url += "&scope="+ this->permissions.join(",");
    }

    return url;
}

QString LoginManager::getToken(){
    return this->token;
}

void LoginManager::checkUrl(const QUrl &url){
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

        //qDebug() << "The user clicked on a wrong link !";
        //login();
    }
}

void LoginManager::setExtendedPermission(LoginManager::ExtendedPermissions extendedPermissions){
    if (extendedPermissions.testFlag(LoginManager::Email)) {
        this->permissions.append("email");
    }
    if (extendedPermissions.testFlag(LoginManager::ManageNotifications)) {
        this->permissions.append("manage_notifications");
    }
    if (extendedPermissions.testFlag(LoginManager::ManagePages)) {
        this->permissions.append("manage_pages");
    }
    if (extendedPermissions.testFlag(LoginManager::PublishActions)) {
        this->permissions.append("publish_actions");
    }
    if (extendedPermissions.testFlag(LoginManager::ReadFriendList)) {
        this->permissions.append("read_friendlists");
    }
    if (extendedPermissions.testFlag(LoginManager::ReadInsights)) {
        this->permissions.append("read_insights");
    }
    if (extendedPermissions.testFlag(LoginManager::ReadMailbox)) {
        this->permissions.append("read_mailbox");
    }
    if (extendedPermissions.testFlag(LoginManager::ReadPageMailboxes)) {
        this->permissions.append("read_page_mailboxes");
    }
    if (extendedPermissions.testFlag(LoginManager::ReadStream)) {
        this->permissions.append("read_stream");
    }
    if (extendedPermissions.testFlag(LoginManager::RsvpEvent)) {
        this->permissions.append("rsvp_event");
    }
}

void LoginManager::setUserDataPermission(LoginManager::UserDataPermissions userDataPermissions){
    if (userDataPermissions.testFlag(LoginManager::UserAboutMe)) {
        this->permissions.append("user_about_me");
    }
    if (userDataPermissions.testFlag(LoginManager::UserActionsBooks)) {
        this->permissions.append("user_actions.books");
    }
    if (userDataPermissions.testFlag(LoginManager::UserActionsMusic)) {
        this->permissions.append("user_actions.music");
    }
    if (userDataPermissions.testFlag(LoginManager::UserActionsNews)) {
        this->permissions.append("user_actions.news");
    }
    if (userDataPermissions.testFlag(LoginManager::UserActionsVideo)) {
        this->permissions.append("user_actions.video");
    }
    if (userDataPermissions.testFlag(LoginManager::UserActivities)) {
        this->permissions.append("user_activities");
    }
    if (userDataPermissions.testFlag(LoginManager::UserBirthday)) {
        this->permissions.append("user_birthday");
    }
    if (userDataPermissions.testFlag(LoginManager::UserEducationHistory)) {
        this->permissions.append("user_education_history");
    }
    if (userDataPermissions.testFlag(LoginManager::UserEvents)) {
        this->permissions.append("user_events");
    }
    if (userDataPermissions.testFlag(LoginManager::UserFriends)) {
        this->permissions.append("user_friends");
    }
    if (userDataPermissions.testFlag(LoginManager::UserGamesActivity)) {
        this->permissions.append("user_games_activity");
    }
    if (userDataPermissions.testFlag(LoginManager::UserGroups)) {
        this->permissions.append("user_groups");
    }
    if (userDataPermissions.testFlag(LoginManager::UserHometown)) {
        this->permissions.append("user_hometown");
    }
    if (userDataPermissions.testFlag(LoginManager::UserInterests)) {
        this->permissions.append("user_interests");
    }
    if (userDataPermissions.testFlag(LoginManager::UserLikes)) {
        this->permissions.append("user_likes");
    }
    if (userDataPermissions.testFlag(LoginManager::UserLocation)) {
        this->permissions.append("user_location");
    }
    if (userDataPermissions.testFlag(LoginManager::UserPhotos)) {
        this->permissions.append("user_photos");
    }
    if (userDataPermissions.testFlag(LoginManager::UserRelationshipDetails)) {
        this->permissions.append("user_relationship_details");
    }
    if (userDataPermissions.testFlag(LoginManager::UserRelationships)) {
        this->permissions.append("user_relationships");
    }
    if (userDataPermissions.testFlag(LoginManager::UserReligionPolitics)) {
        this->permissions.append("user_religion_politics");
    }
    if (userDataPermissions.testFlag(LoginManager::UserStatus)) {
        this->permissions.append("user_status");
    }
    if (userDataPermissions.testFlag(LoginManager::UserTaggedPlaces)) {
        this->permissions.append("user_tagged_places");
    }
    if (userDataPermissions.testFlag(LoginManager::UserVideos)) {
        this->permissions.append("user_videos");
    }
    if (userDataPermissions.testFlag(LoginManager::UserWebsite)) {
        this->permissions.append("user_website");
    }
    if (userDataPermissions.testFlag(LoginManager::UserWorkHistory)) {
        this->permissions.append("user_work_history");
    }
}

void LoginManager::clearPermissions(){
    this->permissions.clear();
}
