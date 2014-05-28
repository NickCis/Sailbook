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

import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: page
    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("Quit")
                //onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
            }

            MenuItem {
                text: qsTr("Logout")
                //onClicked: pageStack.push(Qt.resolvedUrl("WebView.qml"))
            }
        }

        VerticalScrollDecorator {}

        SearchField {
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }
            //text: qsTr("Search")
            id: searchField
        }

        SilicaListView {
            id: menu
            anchors {
                top: searchField.bottom
                bottom: parent.bottom
            }
            width: parent.width
            model: ListModel {
                ListElement {
                    name: "Profile"
                    link: ""
                }
                ListElement {
                    name: "News"
                    link: "NewsFeed.qml"
                    section: "Favorites"
                }

                ListElement {
                    name: "Get Token"
                    link: "TokenGetter.qml"
                    section: "Favorites"
                }

                ListElement {
                    name: "Test Page"
                    link: ""
                    section: "Pages"
                }

                ListElement {
                    name: "Test Group"
                    link: ""
                    section: "Groups"
                }
            }

            delegate: ListItem {
                id: delegateFavList
                Label {
                    text: qsTr(name)
                    anchors {
                        margins: Theme.paddingLarge
                        left: parent.left
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                    }
                    color: delegateFavList.highlighted ? Theme.highlightColor : Theme.primaryColor
                }
                onClicked: pageStack.push(Qt.resolvedUrl(link))
            }

            section {
                property: 'section'
                delegate: SectionHeader {
                    text: qsTr(section)
                    height: Theme.itemSizeExtraSmall
                }
            }
        }
    }
}


