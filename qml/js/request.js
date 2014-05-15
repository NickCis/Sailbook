// http://qt-project.org/doc/qt-5/qtqml-javascript-imports.html
.import Sailbook.Request 1.0 as SailRequest

function Request(c) {
    //var component = Qt.createComponent("../components/Request.qml"),
    //        req = component.createObject(parent, props);
    this.c = c || {};

    this.req = Configurator.createRequest();
    //this.req = SailRequest.Builder.createRequest();
    this.req.query = this.c.query;
    this.req.loginManager = LoginManager;

    if(this.c.type)
        req.type = this.c.type;

    /*this.req = Sailbook.Request.createObject(null, {
        query: this.c.query,
        loginManager: LoginManager,
        type: this.c.type || Sailbook.Request.Get
    });*/


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
}

function getUserData(parent, cb){
    new Request({
        query: "/me",
        complete: function(json){
            Configurator.setValue("user", json);
            Configurator.save();
            if(typeof(cb) == "function")
                cb(json);
        }
    });
}

function setLike(id, cb){
    return new Request({
        query: "/"+id+"/likes",
        type: SailRequest.Request.Post,
        complete: cb
    });
}


function setDislike(id, cb){
    return new Request({
        query: "/"+id+"/likes",
        type: SailRequest.Request.Delete,
        complete: cb
    });
}
