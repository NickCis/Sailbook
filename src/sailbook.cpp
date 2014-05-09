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

#include "loginmanager.h"
#include "request.h"
#include "configurator.h"

#define APPID "191282437574280"

int main(int argc, char *argv[]) {
    QGuiApplication* app = SailfishApp::application(argc, argv);
    QQuickView* view = SailfishApp::createView();

    Configurator config;
    config.load();

    qmlRegisterType<Request>("Sailbook.Request", 1, 0, "Request");

    LoginManager login(QStringLiteral(APPID), config.getValue(QStringLiteral("token")).toString());
    login.setExtendedPermission(LoginManager::ExtendedPermissions(
        LoginManager::Email |
        LoginManager::ManageNotifications |
        LoginManager::ManagePages |
        LoginManager::PublishActions |
        LoginManager::ReadFriendList |
        LoginManager::ReadInsights |
        LoginManager::ReadMailbox |
        LoginManager::ReadPageMailboxes |
        LoginManager::ReadStream |
        LoginManager::RsvpEvent
    ));

    login.setUserDataPermission(LoginManager::UserDataPermissions(
        LoginManager::UserAboutMe |
        LoginManager::UserActionsBooks |
        LoginManager::UserActionsMusic |
        LoginManager::UserActionsNews |
        LoginManager::UserActionsVideo |
        LoginManager::UserActivities |
        LoginManager::UserBirthday |
        LoginManager::UserEducationHistory |
        LoginManager::UserEvents |
        LoginManager::UserFriends |
        LoginManager::UserGamesActivity |
        LoginManager::UserGroups |
        LoginManager::UserHometown |
        LoginManager::UserInterests |
        LoginManager::UserLikes |
        LoginManager::UserLocation |
        LoginManager::UserPhotos |
        LoginManager::UserRelationshipDetails |
        LoginManager::UserRelationships |
        LoginManager::UserReligionPolitics |
        LoginManager::UserStatus |
        LoginManager::UserTaggedPlaces |
        LoginManager::UserVideos |
        LoginManager::UserWebsite |
        LoginManager::UserWorkHistory
    ));

    view->rootContext()->setContextProperty("LoginManager", &login);
    view->rootContext()->setContextProperty("Configurator", &config);
    view->setSource(SailfishApp::pathTo("qml/sailbook.qml"));
    view->show();

    return app->exec();
}

