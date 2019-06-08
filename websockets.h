#ifndef WEBSOCKETS_H
#define WEBSOCKETS_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <ProtoBufObject.pb.h>
#include "commandlogger.h"

class Websockets : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool isConnected READ isConnected NOTIFY clientConnectionChanged)

public:
    Websockets(QObject *parent = nullptr);

signals:
    void clientConnectionChanged();

public slots:
    void connectClient(QString url, CommandLogger *commandLogger);
    void closeClient(CommandLogger *commandLogger);
    void sendPacket(ProtoBufObject *protoObject);

private slots:
    void onConnected();
    void onClosed();
    void onBinaryMessageReceived(QByteArray message);

private:
    QWebSocket m_webSocket;
    bool m_connected;

    bool isConnected();
};

#endif // WEBSOCKETS_H
