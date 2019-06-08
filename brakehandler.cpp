#include <ProtoBufObject.pb.h>
#include "brakehandler.h"

BrakeHandler::BrakeHandler(QObject *parent):
    QObject(parent), m_brake(0){}

void BrakeHandler::sendBrake(Websockets *websockets, CommandLogger *commandLogger) {
    ProtoBufObject protoObject;
    protoObject.set_id(0x0);
    protoObject.set_type(0x0);
    protoObject.set_data(m_brake);

    websockets->sendPacket(&protoObject);

    commandLogger->setLog("Braking: Command sent as Proto packet");
}
