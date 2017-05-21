QT += core
QT -= gui

TARGET = server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
CONFIG += c++14

SOURCES += \
    server.cpp


unix|win32: LIBS += -lcpprest -lboost_system -lcrypto -lssl -lpthread
