#include "telsearch_entry.h"

telsearch_entry::telsearch_entry()
{
}
void telsearch_entry::printAdress()
{
     qDebug().noquote() << this->get_name() << this->get_firstname();
     qDebug().noquote()  << this->get_street() << this->get_streetno();
     qDebug().noquote()  << this->get_zip() << this->get_city();
}

//Get
QString telsearch_entry::get_name()                     { return name;      }
QString telsearch_entry::get_subname()                  { return subname;   }
QString telsearch_entry::get_firstname()                { return firstname; }
QString telsearch_entry::get_occupation()               { return occupation;}
QString telsearch_entry::get_street()                   { return street;    }
QString telsearch_entry::get_streetno()                 { return streetno;  }
QString telsearch_entry::get_zip()                      { return zip;       }
QString telsearch_entry::get_city()                     { return city;      }
QString telsearch_entry::get_canton()                   { return canton;    }
QString telsearch_entry::get_country()                  { return country;   }
QString telsearch_entry::get_phone()                    { return phone;     }
QString telsearch_entry::get_fax()                      { return fax;       }
QString telsearch_entry::get_email()                    { return email;     }
QString telsearch_entry::get_website()                  { return website;   }
QString telsearch_entry::get_nopromo()                  { return nopromo;   }

//Set
void telsearch_entry::set_name(QString value)           { name       = value; }
void telsearch_entry::set_subname(QString value)        { subname    = value; }
void telsearch_entry::set_firstname(QString value)      { firstname  = value; }
void telsearch_entry::set_occupation(QString value)     { occupation = value; }
void telsearch_entry::set_street(QString value)         { street     = value; }
void telsearch_entry::set_streetno(QString value)       { streetno   = value; }
void telsearch_entry::set_zip(QString value)            { zip        = value; }
void telsearch_entry::set_city(QString value)           { city       = value; }
void telsearch_entry::set_canton(QString value)         { canton     = value; }
void telsearch_entry::set_country(QString value)        { country    = value; }
void telsearch_entry::set_phone(QString value)          { phone      = value; }
void telsearch_entry::set_fax(QString value)            { fax        = value; }
void telsearch_entry::set_email(QString value)          { email      = value; }
void telsearch_entry::set_website(QString value)        { website    = value; }
void telsearch_entry::set_nopromo(QString value)        { nopromo    = value; }
