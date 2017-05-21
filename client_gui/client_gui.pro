TEMPLATE = app

QT += qml quick
CONFIG += c++14

SOURCES += main.cpp \
    restclient.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = /usr/lib/x86_64-linux-gnu/qt5/qml
QML2_IMPORT_PATH = /usr/lib/x86_64-linux-gnu/qt5/qml

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    restclient.h


unix|win32: LIBS += -lcpprest -lboost_system -lcrypto -lssl -lpthread

