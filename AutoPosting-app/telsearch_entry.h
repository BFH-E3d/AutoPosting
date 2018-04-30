#ifndef TELSEARCH_ENTRY_H
#define TELSEARCH_ENTRY_H

#include <QString>
#include <QDebug>

class telsearch_entry
{

private:
    QString name;           //Nachname
    QString subname;        //Hilfsname
    QString firstname;      //Vorname
    QString occupation;     //Beruf
    QString street;         //Strasse
    QString streetno;       //Stassennummer
    QString zip;            //Postleitzahl
    QString city;           //Ort
    QString canton;         //Kanton
    QString country;        //Land
    QString phone;          //Telefon
    QString fax;            //Fax
    QString email;          //Email
    QString website;         //Website
    QString nopromo;        //Wünscht keine Werbung

public:
    telsearch_entry();

    void printAdress();

    //Get
    QString get_name();
    QString get_subname();
    QString get_firstname();
    QString get_occupation();
    QString get_street();
    QString get_streetno();
    QString get_zip();
    QString get_city();
    QString get_canton();
    QString get_country();
    QString get_phone();
    QString get_fax();
    QString get_email();
    QString get_website();
    QString get_nopromo();

    //Set
    void set_name(QString value);
    void set_subname(QString value);
    void set_firstname(QString value);
    void set_occupation(QString value);
    void set_street(QString value);
    void set_streetno(QString value);
    void set_zip(QString value);
    void set_city(QString value);
    void set_canton(QString value);
    void set_country(QString value);
    void set_phone(QString value);
    void set_fax(QString value);
    void set_email(QString value);
    void set_website(QString value);
    void set_nopromo(QString value);

};

#endif // TELSEARCH_ENTRY_H
