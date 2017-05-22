TEMPLATE = app

QT += qml quick
CONFIG += c++14

SOURCES += main.cpp \
    restserver.cpp \
    controller.cpp \
    dictionary.cpp \
    all_dictionary.cpp \
    fifo_dictionary.cpp \
    lru_dictionary.cpp \
    swap_dictionary.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = /usr/lib/x86_64-linux-gnu/qt5/qml
QML2_IMPORT_PATH = /usr/lib/x86_64-linux-gnu/qt5/qml

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    restserver.h \
    controller.h \
    memorystrategy.h \
    dictionary.h \
    all_dictionary.h \
    fifo_dictionary.h \
    lru_dictionary.h \
    swap_dictionary.h


unix|win32: LIBS += -lcpprest -lboost_system -lcrypto -lssl -lpthread
