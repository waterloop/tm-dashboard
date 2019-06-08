#ifndef WEBSOCKETS_H
#define WEBSOCKETS_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class Websockets : public QObject {
    Q_OBJECT

    Q_PROPERTY(int isConnected READ isConnected NOTIFY clientConnectionChanged)

public:
    Websockets(QObject *parent = nullptr);

signals:
    void clientConnectionChanged();

public slots:
    void connectClient(QString url);
    void closeClient();

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
