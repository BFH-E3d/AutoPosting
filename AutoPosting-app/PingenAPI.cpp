#include "PingenAPI.h"
#include <QTextStream>

PingenAPI::PingenAPI(QString token)
{
    this->token = token;
}

QJsonObject PingenAPI::sendRequest(QJsonObject json){
    QNetworkRequest request;
    request.setUrl(QUrl(this->url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkAccessManager nam;
    QNetworkReply *reply = nam.post(request,QJsonDocument(json).toJson());

    while(!reply->isFinished()){
        qApp->processEvents();
    }

    QByteArray response = reply->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonDocument.object();
    reply->deleteLater();
    this->lastJsonObj = jsonObject;
    return jsonObject;
}

QJsonObject PingenAPI::getLastJsonObj(void){
    return lastJsonObj;
}

QString PingenAPI::addLetter(Letter &l)
{
    this->url = "https://stage-api.pingen.com/letter/add/token/" + this->token;
    QJsonObject jsonLetter;
    jsonLetter.insert("title",l.getTitle());
    jsonLetter.insert("recipient",l.getRecipient());
    jsonLetter.insert("address",l.getAddress());
    jsonLetter.insert("content",l.getContent());
    QJsonObject response = this->sendRequest(jsonLetter);

    if(response.value("error").toBool()){
        return response.value("errormessage").toString();
    } else {
        qint32 id = response.value("id").toInt();
        l.setId(id);
        return "Letter with id: " + QString::number(id) + " added.";
    }
}

QString PingenAPI::sendLetter(qint32 id, qint8 speed, qint8 color)
{
    this->url = "https://stage-api.pingen.com/letter/send/id/" + QString::number(id) + "/token/" + this->token;
    QJsonObject jsonSendLetter;
    jsonSendLetter.insert("speed",speed);
    jsonSendLetter.insert("color",color);
    QJsonObject response = this->sendRequest(jsonSendLetter);

    if(response.value("error").toBool()){
        return response.value("errormessage").toString();
    } else {
        qint32 postId = response.value("id").toInt();
        return "Letter with id: " + QString::number(id) + " sent.\n\rThe id of the Post Object is " + QString::number(postId);
    }
}

QString PingenAPI::deleteLetter(qint32 id)
{
    this->url = "https://stage-api.pingen.com/letter/delete/id/" + QString::number(id) + "/token/" + this->token;
    QJsonObject voidJson;
    QJsonObject response = this->sendRequest(voidJson);

    if(response.value("error").toBool()){
        return response.value("errormessage").toString();
    } else {
        return "Letter with id: " + QString::number(id) + " deleted.";
    }
}


