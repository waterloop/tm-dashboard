#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QObject>
#include "websockets.h"

class CommandHandler : public QObject
{
    Q_OBJECT
public:
    explicit CommandHandler(Websockets websockets, QObject *parent = nullptr);

signals:

public slots:
    Websockets m_websockets;
    void brake();
    void emergencyStop();
    void sendSpeed(int speed);
};

#endif // COMMANDHANDLER_H
