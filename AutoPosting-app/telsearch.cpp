#include "telsearch.h"

telsearch::telsearch()
{ 
    //Event happend when Request ended successfull or on error
   connect(&tel_request, SIGNAL(received_adresses(QList<telsearch_entry>, telsearch_request*)), this, SLOT(received_adresses(QList<telsearch_entry>, telsearch_request *)));
   connect(&tel_request, SIGNAL(request_error(telsearch_request*)), this, SLOT(request_error(telsearch_request*)));

}
void telsearch::search(QString what, QString where)
{
    QString language;
    QString companies = search_for_companies ?  "1" : "0";  //Bool zu String -> "1" oder "0" anstatt true oder false
    QString privat    = search_for_private   ?  "1" : "0";  //Bool zu String -> "1" oder "0" anstatt true oder false

    search_done = false;  //Reset
    search_error = false; //Reset

    switch(selected_language)
    {
        case LANG_DE: language = "de"; break;
        case LANG_FR: language = "fr"; break;
        case LANG_IT: language = "it"; break;
        case LANG_EN: language = "en"; break;
    }

    //Query zusammenstellen,  Doku https://tel.search.ch/api/help
    tel_request.setQueryElement("was", what);
    tel_request.setQueryElement("wo", where);
    tel_request.setQueryElement("key", api_key);
    tel_request.setQueryElement("lang", language);
    tel_request.setQueryElement("firma", companies);
    tel_request.setQueryElement("privat", privat);

    tel_request.set_baseURL(base_url);   //Telsearch url

    tel_request.startRequest();         //Request abschicken -> Callbackfunktionen: request_error oder received_adresses
}

void telsearch::request_error(telsearch_request *request)
{
    QList<telsearch_entry> void_list;
    results = void_list;
    search_error = true;
    search_done = true;

     //qDebug() << "error! something strange happend!";
}

void telsearch::received_adresses(QList<telsearch_entry> adresses, telsearch_request *request)
{
    results = adresses;
    search_error = false;
    search_done = true;

    emit send_adr(adresses);

    //qDebug() << adresses.count() << "Results found";
    //for(int i =0; i<adresses.count(); i++)
    //{
    //    adresses[i].printAdress();
    //}
}

bool telsearch::isDone()  {return search_done;}
bool telsearch::hasError(){return search_error;}
