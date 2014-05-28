import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/request.js" as Request

SilicaListView {
    id: me

    property string pagingPrevious: "";
    property string pagingNext: "";
    property bool loading: false;
    property bool loadingTop: false;
    property bool loadingBottom: false;
    property double loadingProgress: 0;
    property string myId: Configurator.getValue("user").id;

    function getModel(){
        return listModel;
    }

    function loadData(json, save){
        for(var i=0,j; j = json['data'][i]; i++){
            listModel.append(j)
        }

        if(save && save["next"] && json["paging"] && json.paging["next"])
            me.pagingNext = json.paging.next;

        if(save && save["previous"] && json["paging"] && json.paging["previous"])
            me.pagingPrevious = json.paging.previous;
    }

    function load(url, save){
        if(url === "")
            return;

        var req = SessionManager.createRequest(url);
        req.complete.connect(function(json){
            me.loadData(json, save);
            me.loading = false;
            me.loadingTop = false;
            me.loadingBottom = false;
            me.loadingProgress = 0;
        });

        req.downloadProgress.connect(function(bytes, bytesTotal){
            if(bytesTotal != -1)
                me.loadingProgress = bytes / bytesTotal;
        });

        req.error.connect(function(){
            me.loading = false;
            me.loadingTop = false;
            me.loadingBottom = false;
            me.loadingProgress = 0;
            viewPlaceHolder.text = qsTr("Error loading")
            Request.errorNotification(qsTr("Error loading"));
        });
    }

    function loadNext(){
        me.loadingBottom = true;
        me.load(me.pagingNext, { next: true });
    }

    function loadPrevious(){
        me.load(me.pagingPrevious, { previous: true });
    }

    /*anchors {
        bottomPadding: me.loadingBottom ? busyIndicatorBottom.height : Theme.paddingSmall
    }*/

    spacing: Theme.paddingSmall

    model: ListModel{
        id: listModel
    }

    delegate: ListItem {
        id: item
        width: parent.width
        height: contentItem.childrenRect.height + item.menu.height
        contentHeight: contentItem.childrenRect.height
        function isLiked(){
            if(model && model.likes && model.likes.data){
                var likes = model.likes.data;
                for(var i=0, l; l = likes[i]; i++){
                    if(l.id == myId)
                        return true;
                }
            }
            return false;
        }

        property bool liked: isLiked()

        onClicked: {
            console.log("Clicked " + index + " " + model);
            pageStack.push(Qt.resolvedUrl("../pages/GenericElement.qml"), {
                myData: model
            });
        }
        menu: ContextMenu {
            MenuItem {
                text: liked ? qsTr("dislike") : qsTr("like")
                onClicked:{
                    Request["set"+(liked?"Dislike":"Like")](id, function(){
                        liked = !liked;
                    });
                }
            }
            MenuItem {
                text: qsTr("don't show")
                onClicked: console.log("don't show")
            }
        }

        Item {
            id: itemHeader
            height: childrenRect.height
            width: parent.width

            Image {
                id: img
                source: "https://graph.facebook.com/v2.0/"+from["id"]+"/picture?height="+Theme.iconSizeLarge+"&width="+Theme.iconSizeLarge
                width: Theme.iconSizeLarge
                height: Theme.iconSizeLarge
                anchors {
                    left: parent.left
                    top: parent.top
                }
            }
            Label {
                function title(){
                    if(story)
                        return story;
                    var txt = from.name;
                    if(model.to && model.to.data)
                        txt += " > "+model.to.data[0].name;

                    return txt;
                }

                id: origin
                text: title()
                font.pixelSize: Theme.fontSizeSmall
                wrapMode: Text.WordWrap
                maximumLineCount: 2
                truncationMode: TruncationMode.Fade
                anchors {
                    left: img.right
                    leftMargin: Theme.paddingSmall
                    right: parent.right
                }
            }
            Label {
                function timestamp() {
                    return Format.formatDate(new Date(created_time), Formatter.DurationElapsed);
                }
                id: timestampLabel
                text: timestamp()
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.secondaryHighlightColor
                anchors {
                    //top: origin.baseline
                    top: origin.bottom
                    //left: img.right
                    right: parent.right
                    //margins: Theme.paddingSmall
                    leftMargin: Theme.paddingSmall
                    rightMargin: Theme.paddingSmall
                    bottomMargin: Theme.paddingSmall
                }
            }
            Label {
                id: body
                visible: message ? true : false
                text: visible ? message : ""
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                wrapMode: Text.WordWrap
                maximumLineCount: 4
                truncationMode: TruncationMode.Fade
                anchors {
                    top: timestampLabel.bottom
                    left: img.right
                    leftMargin: Theme.paddingSmall
                    right: parent.right
                }
                Component.onCompleted: {
                    if(!visible)
                        height = 0;
                }
            }
        }
        Loader {
            function getSource(){
                if(picture && name && description)
                    return pictureWithDesc;

                if(picture)
                    return pictureOnly;

                return undefined;
            }

            id: changingBody
            sourceComponent: getSource()
            anchors {
                //top: origin.height+timestampLabel.height+body.height > img.height ? body.bottom : img.bottom
                top: itemHeader.bottom
                left: parent.left
                right: parent.right
                margins: Theme.paddingSmall
            }

            Component {
                id: pictureWithDesc
                Item {
                    id: pictureRow
                    height: childrenRect.height
                    /*anchors {
                        top: body.bottom
                        left: img.right
                        right: parent.right
                        topMargin: Theme.paddingSmall
                        leftMargin: Theme.paddingSmall
                        rightMargin: Theme.paddingSmall
                    }*/
                    //anchors.fill: parent
                    Image {
                        id: pictureImg
                        source: picture
                        fillMode: Image.PreserveAspectFit
                        width: Theme.coverSizeSmall.width
                        //height: Theme.coverSizeSmall.height
                        anchors {
                            left: parent.left
                            leftMargin: Theme.paddingSmall
                            //verticalCenter: parent.verticalCenter
                        }
                    }
                    Label {
                        id: labelName
                        anchors {
                            top: parent.top
                            right: parent.right
                            left: pictureImg.right
                            leftMargin: Theme.paddingSmall
                        }
                        text: name
                        font.pixelSize: Theme.fontSizeExtraSmall
                        wrapMode: Text.WordWrap
                        maximumLineCount: 2
                        truncationMode: TruncationMode.Fade
                    }
                    Label {
                        anchors {
                            top: labelName.bottom
                            right: parent.right
                            left: pictureImg.right
                            leftMargin: Theme.paddingSmall
                        }

                        text: description
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: Theme.secondaryColor
                        wrapMode: Text.WordWrap
                        maximumLineCount: 2
                        truncationMode: TruncationMode.Fade
                    }
                }
            }
            Component {
                id: pictureOnly
                Item {
                    height: childrenRect.height
                    Image {
                        id: pictureOnlyImg
                        source: picture
                        fillMode: Image.PreserveAspectFit
                        width: parent.width
                        height: Theme.coverSizeLarge.height
                        anchors {
                            left: parent.lelft
                            right: parent.right
                            margins: Theme.paddingSmall
                        }

                        //anchors.fill: parent
                    }

                    Label {
                        visible: model.caption ? true : false
                        text: visible ? model.caption : ""
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: Theme.secondaryColor
                        wrapMode: Text.WordWrap
                        maximumLineCount: 2
                        truncationMode: TruncationMode.Fade
                        anchors {
                            top: pictureOnlyImg.bottom
                            left: parent.left
                            right: parent.right
                            margins: visible ? Theme.paddingSmall : 0
                            topMargin: 0
                        }
                        Component.onCompleted: {
                            if(!visible)
                                height = 0;
                        }
                    }
                }
            }
        }

        Label {
            function myText(){
                var txt = [];
                if(likes && likes.data && likes.data.length)
                    txt.push(likes.data.length + " " + qsTr("likes"));

                if(model['shares'] && model.shares.count)
                    txt.push(model.shares.count + " " + qsTr("shares"));

                if(comments && comments.data && comments.data.length)
                    txt.push(comments.data.length + " " + qsTr("comments"));

                return txt.join(" · ") || "";
            }
            text: myText()
            visible: text != ""? true: false
            font.pixelSize: Theme.fontSizeTiny
            color: Theme.secondaryHighlightColor
            anchors {
                topMargin: Theme.paddingSmall
                leftMargin: img.width + Theme.paddingSmall
                rightMargin: Theme.paddingSmall
                top: changingBody.bottom
                left: parent.left
                right: parent.right
            }

            Component.onCompleted: {
                if(!visible)
                    height = 0;
            }
        }
    }

    BusyIndicator {
        anchors.centerIn: parent
        running: true
        size: BusyIndicatorSize.Large
        visible: me.loading && me.loadingProgress === 0? true : false
    }

    ProgressCircle {
        anchors.centerIn: parent
        value: me.loadingProgress
        visible: me.loading && me.loadingProgress > 0? true : false
    }

    ViewPlaceholder {
        id: viewPlaceHolder
        enabled: !me.loading && me.count == 0
        text: qsTr("no items");
    }

    BusyIndicator{
        id: busyIndicatorTop
        anchors{
            horizontalCenter: parent.horizontalCenter
            topMargin: Theme.paddingSmall
            bottomMargin: Theme.paddingSmall
            top: parent.top
        }
        running: true
        size: BusyIndicatorSize.Medium
        visible: me.loadingTop
    }

    BusyIndicator{
        id: busyIndicatorBottom
        anchors{
            horizontalCenter: parent.horizontalCenter
            topMargin: Theme.paddingSmall
            bottomMargin: Theme.paddingSmall
            bottom: parent.bottom
        }
        running: true
        size: BusyIndicatorSize.Medium
        visible: me.loadingBottom
    }
}


