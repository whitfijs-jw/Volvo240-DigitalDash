QT += core gui testlib

TARGET = DashUnitTests
TEMPLATE = app

CONFIG += console
CONFIG += c++17

SOURCES += \
    config_test.cpp \
    map_test.cpp \
    test_main.cpp

INCLUDEPATH += \
    ../app/

HEADERS += \
    ../app/map_sensor.h\
    ../app/config.h\
    map_test.h \
    config_test.h \
