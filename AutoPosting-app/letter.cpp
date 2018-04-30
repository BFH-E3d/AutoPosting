#include "letter.h"

Letter::Letter()
{

}

Letter::Letter(QString title, QString recipient, QString streetNo, QString plzCity, QString content, QString country)
{
    this->setTitle(title);
    this->setRecipient(recipient);
    this->setAddress(streetNo, plzCity, country);
    this->setContent(content);
}

void Letter::setTitle(QString title)
{
    this->title = title;
}

void Letter::setRecipient(QString recipient)
{
    this->recipient = recipient;
}

void Letter::setAddress(QString streetNo, QString plzCity, QString country)
{
    this->address = streetNo + "\n\r" + plzCity + "\n\r" + country;
}

void Letter::setContent(QString content)
{
    this->content = content;
}

void Letter::setId(qint32 id)
{
    this->id = id;
}

QString Letter::getTitle()
{
    return this->title;
}

QString Letter::getRecipient()
{
    return this->recipient;
}

QString Letter::getAddress()
{
    return this->address;
}

QString Letter::getContent()
{
    return this->content;
}

qint32 Letter::getId()
{
    return this->id;
}
