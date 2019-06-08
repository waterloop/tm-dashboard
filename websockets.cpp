#include "websockets.h"
#include <QtCore/QDebug>


Websockets::Websockets(QObject *parent) :
    QObject(parent) {
     m_connected = false;

    connect(&m_webSocket, &QWebSocket::connected, this, &Websockets::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Websockets::onClosed);
}

void Websockets::connectClient(QString url) {
    qDebug() << "WebSocket client:" << url;

    m_webSocket.open(QUrl(url));
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

void Websockets::closeClient() {
    m_connected = false;
    m_webSocket.close();

    emit clientConnectionChanged();
}

bool Websockets::isConnected() {
    return m_connected;
}

void Websockets::onBinaryMessageReceived(QByteArray message)
{
    qDebug() << "Message received:" << message;
}
