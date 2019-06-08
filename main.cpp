#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "websockets.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<Websockets>("com.waterloop.websockets", 1, 0, "Websockets");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
