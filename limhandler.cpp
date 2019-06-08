#include "limhandler.h"

LIMHandler::LIMHandler(QObject *parent):
    QObject(parent), m_speed(0){}

void LIMHandler::sendSpeed(Websockets *websockets, CommandLogger *commandLogger, int speed) {
    ProtoBufObject protoObject;
    protoObject.set_id(0x1);
    protoObject.set_type(0x0);
    protoObject.set_data(static_cast<uint8_t>(speed));

    websockets->sendPacket(&protoObject);

    commandLogger->setLog("LIM: Command sent as Proto packet");
}
