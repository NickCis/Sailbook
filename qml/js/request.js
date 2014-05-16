// http://qt-project.org/doc/qt-5/qtqml-javascript-imports.html
.import App.Sailbook 1.0 as Sailbook

/*function Request(c) {
    //var component = Qt.createComponent("../components/Request.qml"),
    //        req = component.createObject(parent, props);
    this.c = c || {};

    this.req = Configurator.createRequest();
    //this.req = SailRequest.Builder.createRequest();
    this.req.query = this.c.query;
    this.req.loginManager = LoginManager;

    if(this.c.type)
        req.type = this.c.type;

    //this.req = Sailbook.Request.createObject(null, {
    //    query: this.c.query,
    //    loginManager: LoginManager,
    //    type: this.c.type || Sailbook.Request.Get
    //});


    this.req.complete.connect(this.onComplete.bind(this));
    this.req.error.connect(this.onError.bind(this));
    this.req.send();
}

Request.prototype.onComplete = function(json){
    this.req.destroy();
    if(typeof(this.c.complete))
        this.c.complete(json);
}

Request.prototype.onError = function(){
    this.req.destroy();
    if(typeof(this.c.error))
        this.c.error();
}*/

function getUserData(parent, cb){
    var req = SessionManager.createRequest("/me");
    req.complete.connect(function(json){
        Configurator.setValue("user", json);
        Configurator.save();
        if(typeof(cb) == "function")
            cb(json);
    });
}

function setLike(id, cb){
    var req = SessionManager.createRequest("/"+id+"/likes", Sailbook.Request.Post);
    req.complete.connect(function(Json){
        errorNotification(qsTr("Success"));
        if(typeof(cb) == 'function')
            cb(Json);
    });
    req.error.connect(function(){
        errorNotification(qsTr("Error while liking"));
    });
}

function setDislike(id, cb){
    var req = SessionManager.createRequest("/"+id+"/likes", Sailbook.Request.Delete);
    req.complete.connect(function(Json){
        errorNotification(qsTr("Success"));
        if(typeof(cb) == 'function')
            cb(Json);
    });

    req.error.connect(function(){
        errorNotification(qsTr("Error while disliking"));
    });
}

function errorNotification(text, cb){
    notification.visible = true;
    notificationLabel.text = text;

    if(typeof(cb) != 'function')
        cb = function() { notification.visible = false; }

    notification.onClose = cb;
}
