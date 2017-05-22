#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "restclient.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();

    RestClient myClient;
    context->setContextProperty("rest_client", &myClient);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}

