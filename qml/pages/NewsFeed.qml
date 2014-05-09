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
import "../components"

Page {
    id: page

    FeedList {
        id: feedList
        anchors.fill: parent
        spacing: Theme.paddingMedium
        loading: true
        header: PageHeader {
            title: qsTr("News Feed")
        }
        VerticalScrollDecorator {}

        PullDownMenu {
            MenuItem {
                text: qsTr("Reload")
                onClicked: req.send()
            }
        }

        PushUpMenu {
            MenuItem {
                text: qsTr("Get More")
                onClicked: feedList.loadNext()
            }
        }
    }

    Request {
        id: req
        query: "/me/home"
        function cbComplete(json){
            feedList.loadData(json, { next: true, previous: true});
            feedList.loading = false;
        }
    }
}
