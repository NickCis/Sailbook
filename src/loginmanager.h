#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <QObject>
#include <QtCore/QUrl>
#include <QtCore/QStringList>

class LoginManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(ExtendedPermission)
    Q_ENUMS(UserDataPermission)
public:
    explicit LoginManager(QString id, QObject *parent = 0);
    explicit LoginManager(QString id, QString t, QObject *parent = 0);
    Q_INVOKABLE QString getAuthUrl();
    Q_INVOKABLE QString getToken();

    /** Flags taken from QFB project and modified to facebook graph V2. See the QFB licence. **/
    /**
         * @brief Extended permissions
         *
         * This enumeration provides a list of extended permissions
         * that can be combined as flags.
         */
    enum ExtendedPermission {
        /**
             * @short Provides \e email
             *
             * Provides access to the user's primary email address in the email property. Do not spam
             *users. Your use of email must comply both with Facebook policies and with the
             * CAN-SPAM Act.
             */
        Email = 0x1,
        /**
             * @short Provides \e manage_notifications
             *
             * Enables your app to read notifications and mark them as read.
             * <b>Intended usage</b>: This permission should be used to let users read and act on
             * their notifications; it should not be used to for the purposes of modeling
             * user behavior or data mining. Apps that misuse this permission may be banned
             * from requesting it.
             */
        ManageNotifications = 0x2,
        /**
             * @short Provides \e manage_pages
             *
             */
        ManagePages = 0x4,
        /**
             * @short Provides \e publish_actions
             *
             */
        PublishActions = 0x8,
        /**
             * @short Provides \e read_friendlists
             *
             * Provides access to any friend lists the user created. All user's friends are
             * provided as part of basic data, this extended permission grants access to the
             * lists of friends a user has created, and should only be requested if your
             * application utilizes lists of friends.
             */
        ReadFriendList = 0x10,

        /**
             * @short Provides \e read_insights
             *
             * Provides read access to the Insights data for pages, applications, and domains
             * the user owns.
             */
        ReadInsights = 0x20,
        /**
             * @short Provides \e read_mailbox
             *
             * Provides the ability to read from a user's Facebook Inbox.
             */
        ReadMailbox = 0x40,
        /**
             * @short Provides \e read_page_mailbox
             *
             */
        ReadPageMailboxes = 0x80,
        /**
             * @short Provides \e read_stream
             *
             * Provides access to all the posts in the user's News Feed and enables your
             * application to perform searches against the user's News Feed.
             */
        ReadStream = 0x100,
        /**
             * @short Provides \e rsvp_event
             *
             * Enables your application to RSVP to events on the user's behalf.
             */
        RsvpEvent = 0x200
    };
    Q_DECLARE_FLAGS(ExtendedPermissions, ExtendedPermission)
    Q_FLAGS(ExtendedPermissions)
    /**
         * @brief User permissions
         *
         * This enumeration provides a list of permissions about the user
         * that can be combined as flags.
         */
    enum UserDataPermission {
        /**
             * @short Provides \e user_about_me
             *
             * Provides access to the "About Me" section of the profile in the about property.
             */
        UserAboutMe = 0x1,
       /**
             * @short Provides \e user_actions.books
             *
             *
             */
        UserActionsBooks = 0x2,
       /**
             * @short Provides \e user_actions.music
             *
             *
             */
        UserActionsMusic = 0x4,
       /**
             * @short Provides \e user_actions.news
             *
             *
             */
        UserActionsNews = 0x8,
       /**
             * @short Provides \e user_actions.video
             *
             *
             */
        UserActionsVideo = 0x10,
        /**
             * @short Provides \e user_activities
             *
             * Provides access to the user's list of activities as the activities connection.
             */
        UserActivities = 0x20,
        /**
             * @short Provides \e user_birthday
             *
             * Provides access to the birthday with year as the birthday property.
             */
        UserBirthday = 0x40,
        /**
             * @short Provides \e user_education_history
             *
             * Provides access to education history as the education property.
             */
        UserEducationHistory = 0x80,
        /**
             * @short Provides \e user_events
             *
             * Provides access to the list of events the user is attending as the events connection.
             */
        UserEvents = 0x100,
        /**
             * @short Provides \e user_friends
             *
             *
             */
        UserFriends = 0x200,
        /**
             * @short Provides \e user_games_activity
             *
             *
             */
        UserGamesActivity = 0x400,
        /**
             * @short Provides \e user_groups
             *
             * Provides access to the list of groups the user is a member of as the groups connection.
             */
        UserGroups = 0x800,
        /**
             * @short Provides \e user_hometown
             *
             * Provides access to the user's hometown in the hometown property.
             */
        UserHometown = 0x1000,
        /**
             * @short Provides \e user_interests
             *
             * Provides access to the user's list of interests as the interests connection.
             */
        UserInterests = 0x2000,
        /**
             * @short Provides \e user_likes
             *
             * Provides access to the list of all of the pages the user has liked as the likes
             * connection.
             */
        UserLikes = 0x4000,
        /**
             * @short Provides \e user_location
             *
             * Provides access to the user's current location as the location property.
             */
        UserLocation = 0x8000,
        /**
             * @short Provides \e user_photos
             *
             * Provides access to the photos the user has uploaded, and photos the user has been
             * tagged in.
             */
        UserPhotos = 0x10000,
        /**
             * @short Provides \e user_relationship_details
             *
             * Provides access to the user's relationship preferences
             */
        UserRelationshipDetails = 0x20000,
       /**
             * @short Provides \e user_relationships
             *
             * Provides access to the user's family and personal relationships and relationship status
             */
        UserRelationships = 0x40000,
        /**
             * @short Provides \e user_religion_politics
             *
             * Provides access to the user's religious and political affiliations.
             */
        UserReligionPolitics = 0x80000,
        /**
             * @short Provides \e user_status
             *
             * Provides access to the user's status messages and checkins. Please see the documentation
             * for the location_post table for information on how this permission may affect retrieval
             * of information about the locations associated with posts.
             */
        UserStatus = 0x100000,
        /**
             * @short Provides \e user_tagged_places
             *
             */
        UserTaggedPlaces = 0x200000,
        /**
             * @short Provides \e user_videos
             *
             * Provides access to the videos the user has uploaded, and videos the user has been tagged
             * in.
             */
        UserVideos = 0x400000,
        /**
             * @short Provides \e user_website
             *
             * Provides access to the user's web site URL.
             */
        UserWebsite = 0x800000,
        /**
             * @short Provides \e user_work_history
             *
             * Provides access to work history as the work property.
             */
        UserWorkHistory = 0x1000000
    };
    Q_DECLARE_FLAGS(UserDataPermissions, UserDataPermission)
    Q_FLAGS(UserDataPermissions)

    void setExtendedPermission(LoginManager::ExtendedPermissions extendedPermissions);
    void setUserDataPermission(LoginManager::UserDataPermissions userDataPermissions);
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
