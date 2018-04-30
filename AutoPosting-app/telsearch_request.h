#ifndef TELSEARCH_REQUEST_H
#define TELSEARCH_REQUEST_H

#include <QObject>
#include <QXmlDefaultHandler>
#include <QUrl>
#include <QUrlQuery>
#include <QString>
#include <QtNetwork>
#include <QtNetwork/QNetworkRequest>
#include <QNetworkAccessManager>
#include <QDebug>
#include <QDomDocument>

#include <QXmlSimpleReader>
#include <QXmlInputSource>

#include "telsearch_entry.h"

class telsearch_request : public QObject//Von QObject Erben um Signal&Slots zu nutzen
{
    Q_OBJECT                     //für Signal&Slots

    enum class Http_Result
    {
          _NONE,
          _UNKNOW_ERROR,
          _200_OK = 200,
          _400_BAD_REQUEST = 400,
          _401_BAD_REQUEST = 401,
          _403_FORBIDDEN = 403,
          _404_NOT_FOUND = 404
     };

private:

    QString     base_url;
    QUrl        adress;
    QUrlQuery   query;

    QNetworkAccessManager *restclient;
    QNetworkReply *reply;

    Http_Result result = Http_Result::_NONE;
    QString     xml_data;

public:
    telsearch_request();
    void setQueryElement(QString name, QString value);
    bool startRequest();
    Http_Result get_result();
    void set_baseURL(QString url);

private:
    void ParseXML();

signals:
    void request_error(telsearch_request *request);
    void received_adresses(QList<telsearch_entry> adresses, telsearch_request *request);

private slots:
    void getNetworkReply(QNetworkReply * ptr);

};

#endif // TELSEARCH_H
