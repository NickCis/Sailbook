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
    if (extendedPermissions.testFlag(LoginManager::ReadFriendList)) {
        this->permissions.append("read_friendlists");
    }
    if (extendedPermissions.testFlag(LoginManager::ReadInsights)) {
        this->permissions.append("read_insights");
    }
    if (extendedPermissions.testFlag(LoginManager::ReadMailbox)) {
        this->permissions.append("read_mailbox");
    }
    if (extendedPermissions.testFlag(LoginManager::ReadRequests)) {
        this->permissions.append("read_requests");
    }
    if (extendedPermissions.testFlag(LoginManager::ReadStream)) {
        this->permissions.append("read_stream");
    }
    if (extendedPermissions.testFlag(LoginManager::XmppLogin)) {
        this->permissions.append("xmpp_login");
    }
    if (extendedPermissions.testFlag(LoginManager::CreateEvent)) {
        this->permissions.append("create_event");
    }
    if (extendedPermissions.testFlag(LoginManager::ManageFriendList)) {
        this->permissions.append("manage_friendlists");
    }
    if (extendedPermissions.testFlag(LoginManager::ManageNotifications)) {
        this->permissions.append("manage_notifications");
    }
    if (extendedPermissions.testFlag(LoginManager::UserOnlinePresence)) {
        this->permissions.append("user_online_presence");
    }
    if (extendedPermissions.testFlag(LoginManager::FriendsOnlinePresence)) {
        this->permissions.append("friends_online_presence");
    }
    if (extendedPermissions.testFlag(LoginManager::PublishCheckins)) {
        this->permissions.append("publish_checkins");
    }
    if (extendedPermissions.testFlag(LoginManager::PublishStream)) {
        this->permissions.append("publish_stream");
    }
    if (extendedPermissions.testFlag(LoginManager::RsvpEvent)) {
        this->permissions.append("rsvp_event");
    }
}

void LoginManager::setUserPermission(LoginManager::UserPermissions userPermissions){
    if (userPermissions.testFlag(LoginManager::UserAboutMe)) {
        this->permissions.append("user_about_me");
    }
    if (userPermissions.testFlag(LoginManager::UserActivities)) {
        this->permissions.append("user_activities");
    }
    if (userPermissions.testFlag(LoginManager::UserBirthday)) {
        this->permissions.append("user_birthday");
    }
    if (userPermissions.testFlag(LoginManager::UserEducationHistory)) {
        this->permissions.append("user_education_history");
    }
    if (userPermissions.testFlag(LoginManager::UserEvents)) {
        this->permissions.append("user_events");
    }
    if (userPermissions.testFlag(LoginManager::UserGroups)) {
        this->permissions.append("user_groups");
    }
    if (userPermissions.testFlag(LoginManager::UserHometown)) {
        this->permissions.append("user_hometown");
    }
    if (userPermissions.testFlag(LoginManager::UserInterests)) {
        this->permissions.append("user_interests");
    }
    if (userPermissions.testFlag(LoginManager::UserLikes)) {
        this->permissions.append("user_likes");
    }
    if (userPermissions.testFlag(LoginManager::UserLocation)) {
        this->permissions.append("user_location");
    }
    if (userPermissions.testFlag(LoginManager::UserNotes)) {
        this->permissions.append("user_notes");
    }
    if (userPermissions.testFlag(LoginManager::UserPhotos)) {
        this->permissions.append("user_photos");
    }
    if (userPermissions.testFlag(LoginManager::UserQuestions)) {
        this->permissions.append("user_questions");
    }
    if (userPermissions.testFlag(LoginManager::UserRelationships)) {
        this->permissions.append("user_relationships");
    }
    if (userPermissions.testFlag(LoginManager::UserRelationshipDetails)) {
        this->permissions.append("user_relationship_details");
    }
    if (userPermissions.testFlag(LoginManager::UserReligionPolitics)) {
        this->permissions.append("user_religion_politics");
    }
    if (userPermissions.testFlag(LoginManager::UserStatus)) {
        this->permissions.append("user_status");
    }
    if (userPermissions.testFlag(LoginManager::UserSubscriptions)) {
        this->permissions.append("user_subscriptions");
    }
    if (userPermissions.testFlag(LoginManager::UserVideos)) {
        this->permissions.append("user_videos");
    }
    if (userPermissions.testFlag(LoginManager::UserWebsite)) {
        this->permissions.append("user_website");
    }
    if (userPermissions.testFlag(LoginManager::UserWorkHistory)) {
        this->permissions.append("user_work_history");
    }
    if (userPermissions.testFlag(LoginManager::Email)) {
        this->permissions.append("email");
    }
}

void LoginManager::setFriendsPermission(LoginManager::FriendsPermissions friendsPermissions){
    if (friendsPermissions.testFlag(LoginManager::FriendsAboutMe)) {
        this->permissions.append("friends_about_me");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsActivities)) {
        this->permissions.append("friends_activities");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsBirthday)) {
        this->permissions.append("friends_birthday");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsEducationHistory)) {
        this->permissions.append("friends_education_history");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsEvents)) {
        this->permissions.append("friends_events");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsGroups)) {
        this->permissions.append("friends_groups");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsHometowm)) {
        this->permissions.append("friends_hometown");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsInterests)) {
        this->permissions.append("friends_interests");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsLikes)) {
        this->permissions.append("friends_likes");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsLocation)) {
        this->permissions.append("friends_location");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsNotes)) {
        this->permissions.append("friends_notes");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsPhotos)) {
        this->permissions.append("friends_photos");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsQuestions)) {
        this->permissions.append("friends_questions");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsRelationships)) {
        this->permissions.append("friends_relationships");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsRelationshipDetails)) {
        this->permissions.append("friends_relationship_details");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsReligionPolitics)) {
        this->permissions.append("friends_religion_politics");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsStatus)) {
        this->permissions.append("friends_status");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsSubscriptions)) {
        this->permissions.append("friends_subscriptions");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsVideos)) {
        this->permissions.append("friends_videos");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsWebsite)) {
        this->permissions.append("friends_website");
    }
    if (friendsPermissions.testFlag(LoginManager::FriendsWorkHistory)) {
        this->permissions.append("friends_work_history");
    }
}

void LoginManager::clearPermissions(){
    this->permissions.clear();
}
