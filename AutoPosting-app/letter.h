#ifndef LETTER_H
#define LETTER_H

#include <QString>

class Letter
{
private:
    QString title;
    QString recipient;
    QString address;
    QString country;
    QString content;
    qint32 id;
public:
    Letter();
    Letter(QString title, QString recipient, QString streetNo, QString plzCity, QString content, QString country = "Schweiz");
    void setTitle(QString title);
    void setRecipient(QString recipient);
    void setAddress(QString streetNo, QString plzCity, QString country);
    void setContent(QString content);
    void setId(qint32 id);
    QString getTitle();
    QString getRecipient();
    QString getAddress();
    QString getContent();
    qint32 getId();
};

#endif // LETTER_H
