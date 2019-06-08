#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "websockets.h"
#include "brakehandler.h"
#include "limhandler.h"
#include "commandlogger.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<Websockets>("com.waterloop.websockets", 1, 0, "Websockets");
    qmlRegisterType<BrakeHandler>("com.waterloop.brakehandler", 1, 0, "BrakeHandler");
    qmlRegisterType<LIMHandler>("com.waterloop.limhandler", 1, 0, "LIMHandler");
    qmlRegisterType<CommandLogger>("com.waterloop.commandLogger", 1, 0, "CommandLogger");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
