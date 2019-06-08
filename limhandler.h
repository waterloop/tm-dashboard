#ifndef LIMHANDLER_H
#define LIMHANDLER_H

#include <QObject>
#include "websockets.h"
#include "commandlogger.h"

class LIMHandler : public QObject
{
    Q_OBJECT
public:
    explicit LIMHandler(QObject *parent = nullptr);

signals:

public slots:
    void sendSpeed(Websockets *websockets, CommandLogger *commandLogger, int speed);

private:
    uint8_t m_speed;
};

#endif // LIMHANDLER_H
