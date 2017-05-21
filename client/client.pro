QT += core
QT -= gui

TARGET = client
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++14

TEMPLATE = app

SOURCES += \
    client.cpp


unix|win32: LIBS += -lcpprest -lboost_system -lcrypto -lssl -lpthread
