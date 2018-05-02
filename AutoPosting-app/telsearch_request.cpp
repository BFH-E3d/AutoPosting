#include "telsearch_request.h"

telsearch_request::telsearch_request()
{
    restclient = new QNetworkAccessManager();
    connect(restclient, &QNetworkAccessManager::finished, this, &telsearch_request::getNetworkReply);
}

void telsearch_request::setQueryElement(QString name, QString value)
{
    query.addQueryItem(name, value);
}

bool telsearch_request::startRequest()
{
    QNetworkRequest request;

    if(query.isEmpty() == false)
    {        
        //URL zusammenstellen
        adress.setUrl(base_url);
        adress.setQuery(query);

        //Request vorbereiten
        QNetworkRequest request;
        request.setUrl(adress);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml"); //Die Antwort ist im XML Format

        //qDebug() << request.url() << "Anfrage verschickt";

        reply = restclient->get(request);        //Anfrage verschicken
         return true;
    }
    return false;
}

void telsearch_request::getNetworkReply( QNetworkReply * reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() <<  "Antwort erhalten HTTP_" + QString::number(statusCode);

    xml_data = "";

    switch(statusCode)
    {
        case 200: //No <error
        {
            result = Http_Result::_200_OK;

            QByteArray bytes = reply->readAll();
            xml_data = QString::fromUtf8(bytes.data(), bytes.size());
            break;
        }
        //Error
        case 400: result = Http_Result::_400_BAD_REQUEST;  break;
        case 401: result = Http_Result::_401_BAD_REQUEST;  break;
        case 403: result = Http_Result::_403_FORBIDDEN;    break;
        case 404: result = Http_Result::_404_NOT_FOUND;    break;

        default:  result = Http_Result::_UNKNOW_ERROR;    break;
   }

    if(result == Http_Result::_200_OK)
    {
        ParseXML(); //process received Data
    }
    else
    {
        //Error happed
        emit request_error(this);
    }
}

void telsearch_request::ParseXML()
{
    /* XML Aufbau siehe telsearch_xml.h
    <entry>
        ...
        <tel:name>Götschi</tel:name>
        <tel:firstname>Hanspeter</tel:firstname>
        <tel:street>Bottigenstrasse</tel:street>
        <tel:streetno>37</tel:streetno>
        <tel:zip>3018</tel:zip>
        <tel:city>Bern</tel:city>
        <tel:canton>BE</tel:canton>
        <tel:country>ch</tel:country>
        ...
    </entry> */

   QList<telsearch_entry> list_results;
   QDomDocument xml_doc;

   xml_doc.setContent(xml_data);
   QDomNodeList xml_results = xml_doc.elementsByTagName("entry");

   for(int i=0; i<xml_results.size(); i++)
   {
       telsearch_entry tel_entry;

       QDomNode xml_item = xml_results.item(i);

       tel_entry.set_name(        xml_item.firstChildElement("tel:name").text()        );
       tel_entry.set_subname(     xml_item.firstChildElement("tel:subname").text()     );
       tel_entry.set_firstname(   xml_item.firstChildElement("tel:firstname").text()   );
       tel_entry.set_occupation(  xml_item.firstChildElement("tel:occupation").text()  );
       tel_entry.set_street(      xml_item.firstChildElement("tel:street").text()      );
       tel_entry.set_streetno(    xml_item.firstChildElement("tel:streetno").text()    );
       tel_entry.set_zip(         xml_item.firstChildElement("tel:zip").text()         );
       tel_entry.set_city(        xml_item.firstChildElement("tel:city").text()        );
       tel_entry.set_canton(      xml_item.firstChildElement("tel:canton").text()      );
       tel_entry.set_country(     xml_item.firstChildElement("tel:country").text()     );
       tel_entry.set_phone(       xml_item.firstChildElement("tel:phone").text()       );
       tel_entry.set_fax(         xml_item.firstChildElement("tel:fax").text()         );
       tel_entry.set_email(       xml_item.firstChildElement("tel:email").text()       );
       tel_entry.set_website(     xml_item.firstChildElement("tel:website").text()     );
       tel_entry.set_nopromo(     xml_item.firstChildElement("tel:nopromo").text()     );

       list_results.append(tel_entry);
   }

   if(list_results.isEmpty() == false)
   {
        emit received_adresses(list_results, this);
   }

}
void telsearch_request::set_baseURL(QString url)
{
    base_url = url;
}
