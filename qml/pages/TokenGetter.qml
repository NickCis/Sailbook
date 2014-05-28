import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    backNavigation: false

    SilicaWebView {
        id: webView

        signal checkUrl(url u);

        /*anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }*/
        anchors.fill: parent

        url: SessionManager.getAuthUrl()
        onUrlChanged: {
            webView.checkUrl(url);
            //urlField.text = url;
        }
        Component.onCompleted: {
            webView.checkUrl.connect(SessionManager.checkUrl);
        }
        Connections {
            target: SessionManager
            onNewToken:{
                Configurator.setValue("token", t);
                Configurator.save();
                pageStack.pop();
            }
        }
    }
}
