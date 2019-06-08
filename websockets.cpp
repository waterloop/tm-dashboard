#include "websockets.h"
#include <QtCore/QDebug>


Websockets::Websockets(QObject *parent) :
    QObject(parent) {
    m_connected = false;

    connect(&m_webSocket, &QWebSocket::connected, this, &Websockets::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Websockets::onClosed);
}

void Websockets::connectClient(QString url, CommandLogger *commandLogger) {
    qDebug() << "WebSocket client:" << url;

    m_webSocket.open(QUrl(url));
    commandLogger->setLog("Websockets: Connected as client to " + url);
}

void Websockets::onConnected() {
    m_connected = true;

    qDebug() << "WebSocket client connected!" << endl;

    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,
            this, &Websockets::onBinaryMessageReceived);

    emit clientConnectionChanged();
}

void Websockets::onClosed() {
    m_connected = false;

    qDebug() << "WebSocket client closed!" << endl;

    emit clientConnectionChanged();
}

void Websockets::closeClient(CommandLogger *commandLogger) {
    m_connected = false;
    m_webSocket.close();

    emit clientConnectionChanged();
    commandLogger->setLog("Websockets: Disconnected client");
}

void Websockets::sendPacket(ProtoBufObject *protoObject) {
    protoObject->set_timestamp(
                static_cast<uint64_t>
                (std::chrono::duration_cast<std::chrono::microseconds>(
                     std::chrono::system_clock::now().time_since_epoch()).count()));

    auto protoBufSize = protoObject->ByteSize();

    char *protoBuffer = new char[protoBufSize];
    protoObject->SerializeToArray(protoBuffer, protoBufSize);

    QScopedPointer<char> p(protoBuffer);

    m_webSocket.sendBinaryMessage(QByteArray(p.get(), protoBufSize));
}

bool Websockets::isConnected() {
    return m_connected;
}

void Websockets::onBinaryMessageReceived(QByteArray message)
{
    qDebug() << "Message received:" << message;
}
