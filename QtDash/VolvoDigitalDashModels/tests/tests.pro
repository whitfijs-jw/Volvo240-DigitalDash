QT += core gui testlib

TARGET = DashUnitTests
TEMPLATE = app

CONFIG += console
CONFIG += c++17

SOURCES += \
    map_test.cpp \

INCLUDEPATH += \
    ../app/

HEADERS += \
    ../app/map_sensor.h\
