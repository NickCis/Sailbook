function request(parent, props, complete, error) {
    var component = Qt.createComponent("../components/Request.qml"),
            req = component.createObject(parent, props);

    if(typeof(complete) == "function")
        req.complete.connect(complete);

    if(typeof(error) == "function")
        req.error.connect(error);

    return req;
}

function getUserData(parent, cb){
    var req = request(appwin, {
        query: "/me",
    },function(json){
        Configurator.setValue("user", json);
        Configurator.save();
        req.destroy();
        if(typeof(cb) == "function")
            cb(json);
    });
}
