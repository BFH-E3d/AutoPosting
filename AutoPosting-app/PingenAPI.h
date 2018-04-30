#ifndef PINGENAPI_H
#define PINGENAPI_H

#include <QtNetwork>
#include <letter.h>

class PingenAPI
{
public:
    static const qint8 SPEED_PRIORITY = 1;
    static const qint8 SPEED_ECONOMY = 2;
    static const qint8 COLOR_BW = 0;
    static const qint8 COLOR_COLOR = 1;

    PingenAPI(QString token);
    QJsonObject sendRequest(QJsonObject json);
    QJsonObject getLastJsonObj(void);
    QString addLetter(Letter &l);
    QString sendLetter(qint32 id, qint8 speed = SPEED_ECONOMY, qint8 color = COLOR_BW);
    QString deleteLetter(qint32 id);
private:
    QString token;
    QString url;
    QJsonObject lastJsonObj;
};

#endif // PINGENAPI_H
