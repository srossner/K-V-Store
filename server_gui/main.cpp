#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "restserver.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    RestServer myServer = RestServer::getInstance();

    myServer.start();

    int return_t = app.exec();

    myServer.stop();

    return  return_t;


}

