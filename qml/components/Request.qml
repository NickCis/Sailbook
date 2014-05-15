import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailbook.Request 1.0

Request {
    id: me
    //token: LoginManager.getToken()
    property variant userData: Configurator.getValue("user")
    locale: userData && userData.locale ? userData.locale : ""
    loginManager: LoginManager

    Component.onCompleted: {
        if(typeof(me.cbComplete) == 'function')
            me.complete.connect(me.cbComplete);

        if(typeof(me.cbError) == 'function')
            me.error.connect(me.cbError);

        me.send();
    }
}
