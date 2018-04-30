#ifndef TELSEARCH_H
#define TELSEARCH_H

#include <QString>
#include <QObject>

#include "telsearch_request.h"


class telsearch : public QObject//Von QObject Erben um Signal&Slots zu nutzen
{
    Q_OBJECT                     //für Signal&Slots

    enum LANG{LANG_DE,LANG_FR,LANG_IT, LANG_EN}; // supported Languages

private:

    telsearch_request tel_request;

    QString  api_key = "500742daf91ac3ec857cfa0cd267d719";  //The Key is the authentication for telsearch. Generate Key here https://tel.search.ch/api/getkey
    QString  base_url = "https://tel.search.ch/api/";       //Request url Telsearch

    //for Request
    bool search_for_private = true;                         //Search entities from privates
    bool search_for_companies = true;                       //Search entities from companies
    LANG selected_language = LANG_DE;                       //Language setting

    //for Result
     QList<telsearch_entry> results;                        //List of results
    bool search_done = false;                               //Request done?
    bool search_error = false;                              //Happend an error?


 public:
    telsearch();

    void search(QString what, QString where);               //Search function

    QList<telsearch_entry> getResults();                    //Access the Results
    bool isDone();
    bool hasError();

signals:
    void send_adr(QList<telsearch_entry> adresses);

public slots:
    void request_error(telsearch_request *request);
    void received_adresses(QList<telsearch_entry> adresses, telsearch_request *request);

};

#endif // TELSEARCH_H
