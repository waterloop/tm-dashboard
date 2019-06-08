#ifndef BRAKEHANDLER_H
#define BRAKEHANDLER_H

#include <QObject>
#include "websockets.h"
#include "commandlogger.h"

class BrakeHandler : public QObject
{
    Q_OBJECT 
public:
    explicit BrakeHandler(QObject *parent = nullptr);

signals:

public slots:
    void sendBrake(Websockets *websockets, CommandLogger *commandLogger);

private:
    uint8_t m_brake;
};

#endif // BRAKEHANDLER_H
