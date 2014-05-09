#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <QObject>
#include <QtCore/QUrl>
#include <QtCore/QStringList>

class LoginManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(ExtendedPermission)
    Q_ENUMS(UserPermission)
    Q_ENUMS(FriendsPermission)
public:
    explicit LoginManager(QString id, QObject *parent = 0);
    explicit LoginManager(QString id, QString t, QObject *parent = 0);
    Q_INVOKABLE QString getAuthUrl();
    Q_INVOKABLE QString getToken();
    /** Flags taken from QFB project **/
    /**
         * @brief Extended permissions
         *
         * This enumeration provides a list of extended permissions
         * that can be combined as flags.
         */
    enum ExtendedPermission {
        /**
             * @short Provides \e read_friendlists
             *
             * Provides access to any friend lists the user created. All user's friends are
             * provided as part of basic data, this extended permission grants access to the
             * lists of friends a user has created, and should only be requested if your
             * application utilizes lists of friends.
             */
        ReadFriendList = 0x1,
        /**
             * @short Provides \e read_insights
             *
             * Provides read access to the Insights data for pages, applications, and domains
             * the user owns.
             */
        ReadInsights = 0x2,
        /**
             * @short Provides \e read_mailbox
             *
             * Provides the ability to read from a user's Facebook Inbox.
             */
        ReadMailbox = 0x4,
        /**
             * @short Provides \e read_requests
             *
             * Provides read access to the user's friend requests.
             */
        ReadRequests = 0x8,
        /**
             * @short Provides \e read_stream
             *
             * Provides access to all the posts in the user's News Feed and enables your
             * application to perform searches against the user's News Feed.
             */
        ReadStream = 0x10,
        /**
             * @short Provides \e xmpp_login
             *
             * Provides applications that integrate with Facebook Chat the ability to log
             * in users.
             */
        XmppLogin = 0x20,
        /**
             * @short Provides \e ads_management
             *
             * Provides the ability to manage ads and call the Facebook Ads API on behalf
             * of a user.
             */
        AdsManagement = 0x40,
        /**
             * @short Provides \e create_event
             *
             * Enables your application to create and modify events on the user's behalf.
             */
        CreateEvent = 0x80,
        /**
             * @short Provides \e manage_friendlists
             *
             * Enables your app to create and edit the user's friend lists.
             */
        ManageFriendList = 0x100,
        /**
             * @short Provides \e manage_notifications
             *
             * Enables your app to read notifications and mark them as read.
             * <b>Intended usage</b>: This permission should be used to let users read and act on
             * their notifications; it should not be used to for the purposes of modeling
             * user behavior or data mining. Apps that misuse this permission may be banned
             * from requesting it.
             */
        ManageNotifications = 0x200,
        /**
             * @short Provides \e user_online_presence
             *
             * Provides access to the user's online/offline presence.
             */
        UserOnlinePresence = 0x400,
        /**
             * @short Provides \e friends_online_presence
             *
             * Provides access to the user's friend's online/offline presence.
             */
        FriendsOnlinePresence = 0x800,
        /**
             * @short Provides \e publish_checkins
             *
             * Enables your app to perform checkins on behalf of the user.
             */
        PublishCheckins = 0x1000,
        /**
             * @short Provides \e publish_stream
             *
             * Enables your app to post content, comments, and likes to a user's stream and to
             * the streams of the user's friends. This is a superset publishing permission which
             * also includes \e publish_actions. However, please note that Facebook recommends a
             * user-initiated sharing model. Please read the Platform Policies to ensure you
             * understand how to properly use this permission. Note, you do not need to request
             * the \e publish_stream permission in order to use the Feed Dialog, the Requests Dialog
             * or the Send Dialog.
             */
        PublishStream = 0x2000,
        /**
             * @short Provides \e rsvp_event
             *
             * Enables your application to RSVP to events on the user's behalf.
             */
        RsvpEvent = 0x4000
    };
    Q_DECLARE_FLAGS(ExtendedPermissions, ExtendedPermission)
    Q_FLAGS(ExtendedPermissions)
    /**
         * @brief User permissions
         *
         * This enumeration provides a list of permissions about the user
         * that can be combined as flags.
         */
    enum UserPermission {
        /**
             * @short Provides \e user_about_me
             *
             * Provides access to the "About Me" section of the profile in the about property.
             */
        UserAboutMe = 0x1,
        /**
             * @short Provides \e user_activities
             *
             * Provides access to the user's list of activities as the activities connection.
             */
        UserActivities = 0x2,
        /**
             * @short Provides \e user_birthday
             *
             * Provides access to the birthday with year as the birthday property.
             */
        UserBirthday = 0x4,
        /**
             * @short Provides \e user_education_history
             *
             * Provides access to education history as the education property.
             */
        UserEducationHistory = 0x8,
        /**
             * @short Provides \e user_events
             *
             * Provides access to the list of events the user is attending as the events connection.
             */
        UserEvents = 0x10,
        /**
             * @short Provides \e user_groups
             *
             * Provides access to the list of groups the user is a member of as the groups connection.
             */
        UserGroups = 0x20,
        /**
             * @short Provides \e user_hometown
             *
             * Provides access to the user's hometown in the hometown property.
             */
        UserHometown = 0x40,
        /**
             * @short Provides \e user_interests
             *
             * Provides access to the user's list of interests as the interests connection.
             */
        UserInterests = 0x80,
        /**
             * @short Provides \e user_likes
             *
             * Provides access to the list of all of the pages the user has liked as the likes
             * connection.
             */
        UserLikes = 0x100,
        /**
             * @short Provides \e user_location
             *
             * Provides access to the user's current location as the location property.
             */
        UserLocation = 0x200,
        /**
             * @short Provides \e user_notes
             *
             * Provides access to the user's notes as the notes connection.
             */
        UserNotes = 0x400,
        /**
             * @short Provides \e user_photos
             *
             * Provides access to the photos the user has uploaded, and photos the user has been
             * tagged in.
             */
        UserPhotos = 0x800,
        /**
             * @short Provides \e user_questions
             *
             * Provides access to the questions the user or friend has asked.
             */
        UserQuestions = 0x1000,
        /**
             * @short Provides \e user_relationships
             *
             * Provides access to the user's family and personal relationships and relationship status
             */
        UserRelationships = 0x2000,
        /**
             * @short Provides \e user_relationship_details
             *
             * Provides access to the user's relationship preferences
             */
        UserRelationshipDetails = 0x4000,
        /**
             * @short Provides \e user_religion_politics
             *
             * Provides access to the user's religious and political affiliations.
             */
        UserReligionPolitics = 0x8000,
        /**
             * @short Provides \e user_status
             *
             * Provides access to the user's status messages and checkins. Please see the documentation
             * for the location_post table for information on how this permission may affect retrieval
             * of information about the locations associated with posts.
             */
        UserStatus = 0x10000,
        /**
             * @short Provides \e user_subscriptions
             *
             * Provides access to the user's subscribers and subscribees.
             */
        UserSubscriptions = 0x20000,
        /**
             * @short Provides \e user_videos
             *
             * Provides access to the videos the user has uploaded, and videos the user has been tagged
             * in.
             */
        UserVideos = 0x40000,
        /**
             * @short Provides \e user_website
             *
             * Provides access to the user's web site URL.
             */
        UserWebsite = 0x80000,
        /**
             * @short Provides \e user_work_history
             *
             * Provides access to work history as the work property.
             */
        UserWorkHistory = 0x100000,
        /**
             * @short Provides \e email
             *
             * Provides access to the user's primary email address in the email property. Do not spam
             *users. Your use of email must comply both with Facebook policies and with the
             * CAN-SPAM Act.
             */
        Email = 0x200000
    };
    Q_DECLARE_FLAGS(UserPermissions, UserPermission)
    Q_FLAGS(UserPermissions)
    /**
         * @brief User permissions
         *
         * This enumeration provides a list of permissions about friends
         * that can be combined as flags.
         */
    enum FriendsPermission {
        /**
             * @short Provides \e friends_about_me
             *
             * Provides access to the "About Me" section of the profile in the about property.
             */
        FriendsAboutMe = 0x1,
        /**
             * @short Provides \e friends_activities
             *
             * Provides access to the user's list of activities as the activities connection.
             */
        FriendsActivities = 0x2,
        /**
             * @short Provides \e friends_birthday
             *
             * Provides access to the birthday with year as the birthday property.
             */
        FriendsBirthday = 0x4,
        /**
             * @short Provides \e friends_education_history
             *
             * Provides access to education history as the education property.
             */
        FriendsEducationHistory = 0x8,
        /**
             * @short Provides \e friends_events
             *
             * Provides access to the list of events the user is attending as the events connection.
             */
        FriendsEvents = 0x10,
        /**
             * @short Provides \e friends_groups
             *
             * Provides access to the list of groups the user is a member of as the groups connection.
             */
        FriendsGroups = 0x20,
        /**
             * @short Provides \e friends_hometown
             *
             * Provides access to the user's hometown in the hometown property.
             */
        FriendsHometowm = 0x40,
        /**
             * @short Provides \e friends_interests
             *
             * Provides access to the user's list of interests as the interests connection.
             */
        FriendsInterests = 0x80,
        /**
             * @short Provides \e friends_likes
             *
             * Provides access to the list of all of the pages the user has liked as the likes
             * connection.
             */
        FriendsLikes = 0x100,
        /**
             * @short Provides \e friends_location
             *
             * Provides access to the user's current location as the location property.
             */
        FriendsLocation = 0x200,
        /**
             * @short Provides \e friends_notes
             *
             * Provides access to the user's notes as the notes connection.
             */
        FriendsNotes = 0x400,
        /**
             * @short Provides \e friends_photos
             *
             * Provides access to the photos the user has uploaded, and photos the user has been
             * tagged in.
             */
        FriendsPhotos = 0x800,
        /**
             * @short Provides \e friends_questions
             *
             * Provides access to the questions the user or friend has asked.
             */
        FriendsQuestions = 0x1000,
        /**
             * @short Provides \e friends_relationships
             *
             * Provides access to the user's family and personal relationships and relationship status
             */
        FriendsRelationships = 0x2000,
        /**
             * @short Provides \e friends_relationship_details
             *
             * Provides access to the user's relationship preferences
             */
        FriendsRelationshipDetails = 0x4000,
        /**
             * @short Provides \e friends_religion_politics
             *
             * Provides access to the user's religious and political affiliations.
             */
        FriendsReligionPolitics = 0x8000,
        /**
             * @short Provides \e friends_status
             *
             * Provides access to the user's status messages and checkins. Please see the documentation
             * for the location_post table for information on how this permission may affect retrieval
             * of information about the locations associated with posts.
             */
        FriendsStatus = 0x10000,
        /**
             * @short Provides \e friends_subscriptions
             *
             * Provides access to the user's subscribers and subscribees.
             */
        FriendsSubscriptions = 0x20000,
        /**
             * @short Provides \e friends_videos
             *
             * Provides access to the videos the user has uploaded, and videos the user has been tagged
             * in.
             */
        FriendsVideos = 0x40000,
        /**
             * @short Provides \e friends_website
             *
             * Provides access to the user's web site URL.
             */
        FriendsWebsite = 0x80000,
        /**
             * @short Provides \e friends_work_history
             *
             * Provides access to work history as the work property.
             */
        FriendsWorkHistory = 0x100000
    };
    Q_DECLARE_FLAGS(FriendsPermissions, FriendsPermission)
    Q_FLAGS(FriendsPermissions)

    void setExtendedPermission(LoginManager::ExtendedPermissions extendedPermissions);
    void setUserPermission(LoginManager::UserPermissions userPermissions);
    void setFriendsPermission(LoginManager::FriendsPermissions friendsPermissions);
    void clearPermissions();

signals:
    void newToken(QString t);
    void apiError();

public slots:
    void checkUrl(const QUrl &url);

protected:
    QString appId;
    QString token;
    QStringList permissions;

};

#endif // LOGINMANAGER_H
