TEMPLATE = app

QT += qml quick
CONFIG += c++14

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)



unix|win32: LIBS += -lcpprest -lboost_system -lcrypto -lssl -lpthread

