#include "configurator.h"
#include <QtDebug>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QJsonDocument>

Configurator::Configurator(QObject *parent) :
    QObject(parent), filePath("")
{
    this->filePath = QDir::homePath()+"/.sailbook/config.json";
}

bool Configurator::load(){
    QFile file(this->filePath);
    if(! file.open(QIODevice::ReadOnly)){
        qWarning() << "Couldn't open config file: '" << this->filePath << "'.";
        return false;
    }

    QByteArray val = file.readAll();
    file.close();

    QJsonDocument data(QJsonDocument::fromJson(val));
    this->config = data.object();
    return true;
}

bool Configurator::save(){
    QFile saveFile(this->filePath);

    QFileInfo fileInfo(this->filePath);
    QDir dir(fileInfo.absoluteDir());

    if(!dir.exists()){
        //if(!dir.mkdir(".")){
        if(!dir.mkpath(fileInfo.absolutePath())){
            qWarning()<< "Couldn't create folder: '" << dir << "'.";
        }
    }

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning()<< "Couldn't open save file: '" << this->filePath << "'.";
        return false;
    }

    QJsonDocument saveDoc(this->config);
    saveFile.write(saveDoc.toJson());

    return true;
}

void Configurator::setValue(QString name, QVariant value){
    this->config[name] = QJsonValue::fromVariant(value);
}

QVariant Configurator::getValue(QString name){
    //return this->config[name].toString();
    QJsonValue val = this->config[name];
    return val.toVariant();
}
