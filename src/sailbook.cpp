/*
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QtDebug>

#include "sessionmanager.h"
#include "request.h"
#include "configurator.h"

#define APPID "191282437574280"

int main(int argc, char *argv[]) {
    QGuiApplication* app = SailfishApp::application(argc, argv);
    QQuickView* view = SailfishApp::createView();

    Configurator config;
    config.load();

    //qmlRegisterType<Request>("Sailbook.Request", 1, 0, "Request");
    qmlRegisterUncreatableType<Request>("App.Sailbook", 1, 0, "Request", QStringLiteral("Error"));
    //qmlRegisterInterface<SessionManager>("SessionManager");

    SessionManager session(QStringLiteral(APPID), config.getValue(QStringLiteral("token")).toString());
    session.setExtendedPermission(SessionManager::ExtendedPermissions(
        SessionManager::Email |
        SessionManager::ManageNotifications |
        SessionManager::ManagePages |
        SessionManager::PublishActions |
        SessionManager::ReadFriendList |
        SessionManager::ReadInsights |
        SessionManager::ReadMailbox |
        SessionManager::ReadPageMailboxes |
        SessionManager::ReadStream |
        SessionManager::RsvpEvent
    ));

    session.setUserDataPermission(SessionManager::UserDataPermissions(
        SessionManager::UserAboutMe |
        SessionManager::UserActionsBooks |
        SessionManager::UserActionsMusic |
        SessionManager::UserActionsNews |
        SessionManager::UserActionsVideo |
        SessionManager::UserActivities |
        SessionManager::UserBirthday |
        SessionManager::UserEducationHistory |
        SessionManager::UserEvents |
        SessionManager::UserFriends |
        SessionManager::UserGamesActivity |
        SessionManager::UserGroups |
        SessionManager::UserHometown |
        SessionManager::UserInterests |
        SessionManager::UserLikes |
        SessionManager::UserLocation |
        SessionManager::UserPhotos |
        SessionManager::UserRelationshipDetails |
        SessionManager::UserRelationships |
        SessionManager::UserReligionPolitics |
        SessionManager::UserStatus |
        SessionManager::UserTaggedPlaces |
        SessionManager::UserVideos |
        SessionManager::UserWebsite |
        SessionManager::UserWorkHistory
    ));

    view->rootContext()->setContextProperty("SessionManager", &session);
    view->rootContext()->setContextProperty("Configurator", &config);
    view->setSource(SailfishApp::pathTo("qml/sailbook.qml"));
    view->show();

    return app->exec();
}

