#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "controller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();

    Controller myController;
    context->setContextProperty("controller", &myController);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    myController.start();

    int return_t = app.exec();

    myController.stop();

    return  return_t;

}

