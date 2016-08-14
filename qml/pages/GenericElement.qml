import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/request.js" as Request

Page {
    id: page;
    property var myData: undefined
    //property bool loading: false
    property bool isLiked: false

    /*function loadData(json){
        data = json;
    }

    function load(url){
        if(url === "")
            return;

        var req = SessionManager.createRequest(url);
        req.complete.connect(function(json){
            page.loadData(json, save);
            page.loading = false;
        });

        //req.downloadProgress.connect(function(bytes, bytesTotal){
        //    if(bytesTotal != -1)
        //        me.loadingProgress = bytes / bytesTotal;
        //});

        req.error.connect(function(){
            page.loading = false;
            Request.errorNotification(qsTr("Error loading"));
        });
    }*/

    SilicaFlickable {
        id: mainFlickable
        anchors.fill: parent
        //contentHeight: height
        //height: contentItem.childrenRect.height
        //property int childHeight:header.height + body.height + commentsList.height + commentInputRow.height + Theme.paddingSmall
        property int childHeight: header.height + rowImgText.height + likesLabel.height + body.height + commentsList.height + commentInputRow.height
        contentHeight: parent.height > childHeight ? parent.height : childHeight
        //contentHeight: contentItem.childrenRect.height

        VerticalScrollDecorator {}

        PullDownMenu {
            MenuItem {
                text: page.isLiked ? qsTr("dislike") : qsTr("like")
                onClicked:{
                    Request["set"+(page.isLiked?"Dislike":"Like")](page.myData.id, function(){
                        page.isLiked = !page.isLiked;
                    });
                }
            }
            MenuItem {
                text: qsTr("share")
                //onClicked: feedList.loadNext()
            }
        }

        Rectangle {
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                bottom: likesLabel.bottom
            }
            color: Theme.rgba(Theme.highlightColor, 0.1)

        }

        PageHeader {
            id: header
            //title: "Loading"
            Image{
                id: profilePic
                height: parent.height - (Theme.paddingSmall * 2)
                width: height
                source: "https://graph.facebook.com/v2.0/"+page.myData.from.id+"/picture?height="+Theme.iconSizeLarge+"&width="+Theme.iconSizeLarge
                anchors {
                    rightMargin: Theme.paddingSmall
                    leftMargin: Theme.paddingSmall
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }
            }
            Column {
                anchors{
                    left: parent.left
                    leftMargin: profilePic.width
                    right: profilePic.left
                    //right: parent.right
                    verticalCenter: parent.verticalCenter
                    rightMargin: Theme.paddingMedium
                }
                //spacing: Theme.paddingSmall
                Label {
                    function title(){
                        if(page.myData.story)
                            return page.myData.story;
                        var txt = page.myData.from.name;
                        if(page.myData.to && page.myData.to.data)
                            txt += " -> "+page.myData.to.data[0].name;

                        return txt;
                    }
                    //text: title()
                    text: page.myData.from.name
                    width: parent.width
                    color: Theme.highlightColor
                    font.pixelSize: Theme.fontSizeMedium
                    horizontalAlignment: Text.AlignRight
                    wrapMode: Text.Wrap
                    truncationMode: TruncationMode.Fade
                }
                Label {
                    width: parent.width
                    text: Format.formatDate(new Date(page.myData.created_time), Formatter.DurationElapsed);
                    color: Theme.secondaryHighlightColor
                    font.pixelSize: Theme.fontSizeTiny
                    horizontalAlignment: Text.AlignRight
                    wrapMode: Text.Wrap
                    truncationMode: TruncationMode.Fade
                }
            }
        }
        Label {
            function buildText(){
                var txt = [];
                if(page.myData.to && page.myData.to.data){
                    var toStr = [];
                    for(var i=0, t; t = page.myData.to.data[i];i++ )
                        toStr.push(t.name);

                    txt.push(qsTr("To")+" "+toStr.join(", "));
                }

                if(page.myData.to)
                    console.log(JSON.stringify(page.myData.to));
                for(var i=0, it, items = [
                        //(page.myData.to || {}).name,
                        page.myData.story,
                        page.myData.message
                    ], len = items.length; (it = items[i]) || i < len; i++){
                    if(it)
                        txt.push(it);
                }

                return txt.join("\n");
            }
            id: rowImgText
            anchors {
                top: header.bottom
                left: parent.left
                right: parent.right
                margins: Theme.paddingMedium
            }
            width: parent.width
            text: buildText()
            wrapMode: Text.WordWrap
            font.pixelSize: Theme.fontSizeExtraSmall
            color: Theme.highlightColor
        }

        Label {
            function myText(){
                if(page.myData.likes && page.myData.likes.data && page.myData.likes.data.length)
                    return page.myData.likes.data.length + " " + qsTr("likes");
                else
                    height = 0;
                return "";
            }

            id: likesLabel
            color: Theme.secondaryHighlightColor
            font.pixelSize: Theme.fontSizeTiny
            anchors {
                top: rowImgText.bottom
                right: parent.right
                margins: Theme.paddingSmall
            }
            text: myText()
            //visible: text != ""? true: false

            //Component.onCompleted: {
            //    if(!visible)
            //        height = 0;
            //}

        }


        Loader {
            function getSource(){
                if(page.myData.picture && page.myData.name && page.myData.description){
                    console.log("pictureWithDesc")
                    return pictureWithDesc;
                }

                if(page.myData.picture){
                    console.log("pictureOnly")
                    return pictureOnly;
                }

                /*if(page.myData.message){
                    console.log("messageOnly")
                    return messageOnly
                }*/

                console.log("undefined")

                return undefined;
            }

            id: body
            sourceComponent: getSource()
            anchors {
                top: likesLabel.bottom
                margins: Theme.paddingSmall
            }
            width: parent.width

        }
        Component {
            id: pictureWithDesc

            Item {
                id: pictureRow
                height: childrenRect.height

                Image {
                    id: pictureImg
                    source: page.myData.picture
                    fillMode: Image.PreserveAspectFit
                    width: Theme.coverSizeSmall.width
                    anchors {
                        left: parent.left
                        leftMargin: Theme.paddingSmall
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
                    text: page.myData.name
                    font.pixelSize: Theme.fontSizeExtraSmall
                    wrapMode: Text.WordWrap
                    truncationMode: TruncationMode.Fade
                }

                Label {
                    anchors {
                        top: labelName.bottom
                        right: parent.right
                        left: pictureImg.right
                        leftMargin: Theme.paddingSmall
                    }

                    text: page.myData.description
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: Theme.secondaryColor
                    wrapMode: Text.WordWrap
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
                    source: page.myData.picture
                    fillMode: Image.PreserveAspectFit
                    width: parent.width
                    height: Theme.coverSizeLarge.height
                    anchors {
                        left: parent.lelft
                        right: parent.right
                        margins: Theme.paddingSmall
                    }
                }

                Label {
                    visible: page.myData.caption ? true : false
                    text: visible ? page.myData.caption : ""
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: Theme.secondaryColor
                    wrapMode: Text.WordWrap
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

        /*Component {
            id: messageOnly
            Label {
                text: page.myData.message
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.secondaryColor
                wrapMode: Text.WordWrap
            }
        }*/

        SilicaListView{
            interactive: false
            id: commentsList
            height: contentItem.childrenRect.height+commentInputRow.height
            anchors {
                //top: body.bottom
                top: body.bottom
                topMargin: Theme.paddingMedium
                bottomMargin: Theme.paddingSmall/*+commentInputRow.height*/
                //bottom: commentInputRow.top
            }

            width: parent.width
            spacing: Theme.paddingSmall
            model: ListModel{
                id: commentListModel
            }
            delegate: ListItem{
                id: item
                width: parent.width
                height: contentItem.childrenRect.height + item.menu.height
                contentHeight: contentItem.childrenRect.height

                Image {
                    id: commentsImage
                    source: "https://graph.facebook.com/v2.0/"+from.id+"/picture?type=square"
                    anchors {
                        left: parent.left
                        margins: Theme.paddingSmall
                    }
                    width: Theme.iconSizeMedium
                    height: Theme.iconSizeMedium
                }
                Label {
                    id: commentsName
                    font.pixelSize: Theme.fontSizeSmall
                    anchors {
                        left: commentsImage.right
                        top: parent.top
                        right: parent.right
                        margins: Theme.paddingSmall
                    }
                    text: from.name
                }
                Label {
                    id: commentsTimestamp
                    anchors {
                        top: commentsName.baseline
                        right: parent.right
                        margins: Theme.paddingSmall
                    }
                    font.pixelSize: Theme.fontSizeTiny
                    color: Theme.secondaryHighlightColor
                    text: Format.formatDate(new Date(created_time), Formatter.DurationElapsed);
                }
                Label {
                    id: commentsMessage
                    anchors {
                        left: commentsImage.right
                        top: commentsTimestamp.bottom
                        right: parent.right
                        margins: Theme.paddingSmall
                    }
                    wrapMode: Text.WordWrap
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: Theme.secondaryColor
                    text: message
                }
                Label {
                    anchors {
                        top: commentsMessage.bottom
                        left: commentsImage.right
                        margins: Theme.paddingSmall
                    }
                    font.pixelSize: Theme.fontSizeTiny
                    color: Theme.secondaryHighlightColor
                    text: like_count + " " + qsTr("likes")
                    visible: like_count > 0
                    Component.onCompleted: {
                        if(!visible)
                            height = 0;
                    }

                }

                menu: ContextMenu {
                    MenuItem {
                        text: user_likes ? qsTr("dislike") : qsTr("like")
                        onClicked:{
                            Request["set"+(user_likes?"Dislike":"Like")](id, function(){
                                user_likes = !user_likes;
                            });
                        }
                    }
                    MenuItem {
                        text: qsTr("edit")
                        onClicked: console.log("edit")
                    }
                    MenuItem {
                        visible: can_remove
                        text: qsTr("erase")
                        onClicked: console.log("erase")
                    }
                }
            }
        }

        Row {
            id:commentInputRow
            width: parent.width
            anchors{
                topMargin: Theme.paddingSmall
                bottom: parent.bottom
            }
            //height: Theme.iconSizeMedium
            height: Theme.itemSizeSmall
            anchors.margins: Theme.paddingSmall
            spacing: Theme.paddingSmall

            Image {
                id: commentImage
                anchors.verticalCenter: parent.verticalCenter
                source: "https://graph.facebook.com/v2.0/me/picture?type=square&access_token="+SessionManager.getToken();
                width: Theme.iconSizeMedium
                height: Theme.iconSizeMedium
            }

            TextField{
                id:commentInput
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width - Theme.iconSizeMedium
                font.pixelSize: Theme.fontSizeSmall
                placeholderText: qsTr("Tap to enter comment")
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-message"
                EnterKey.onClicked:{
                    commentInput.focus = false;
                    Request.sendComment(page.myData.id, commentInput.text, function(Json){
                        var user = Configurator.getValue("user");
                        console.log(JSON.stringify(Json));
                        commentListModel.append({
                            "id": Json.id,
                            "from": {
                                "id": user.id,
                                "name": user.name
                            },
                            "message" : commentInput.text,
                            "created_time" : new Date().getTime(),
                            "like_count":0,
                            "user_likes": false,
                            "can_remove": true
                        });
                        commentInput.text = ""
                    });
                }
                onActiveFocusChanged: mainFlickable.scrollToBottom()
            }
        }
        PushUpMenu {
            id: pushMedia
            _activeHeight: mediaSendRow.height
            Item {
                width: parent.width
                height: Theme.itemSizeMedium

                Row {
                    id: mediaSendRow
                    x: width > parent.width ? 0 : ((parent.width - width) / 2)
                    height: parent.height
                    spacing: Theme.paddingSmall

                    IconButton {
                        icon.source: "image://theme/icon-m-image"
                        onClicked: {
                            console.log("todo add image")
                        }
                    }

                    IconButton {
                        icon.source: "image://theme/icon-camera-shutter-release"
                        onClicked: {
                            console.log("todo take photo")
                        }
                    }

                    IconButton {
                        icon.source: "image://theme/icon-m-gps"
                        onClicked: {
                            console.log("todo add location")
                        }
                    }

                    Item {
                        id: voicePlaceholder
                        width: Theme.itemSizeSmall
                        height: Theme.itemSizeSmall
                    }

                    IconButton {
                        icon.source: "image://theme/icon-m-people"
                        onClicked: {
                            console.log("todo add people")
                        }
                    }
                }
            }
        }

        Component.onCompleted: {
            if(page.myData.comments){
                console.log("agregando comentarios")
                for(var i =0, it; it = page.myData.comments.data[i]; i++)
                    commentListModel.append(it);
            }
        }
    }
}
