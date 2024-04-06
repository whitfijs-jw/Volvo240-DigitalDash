QT += core gui testlib

TARGET = DashUnitTests
TEMPLATE = app

CONFIG += console
CONFIG += c++17

SOURCES += \
    config_test.cpp \
    map_test.cpp \
    ntc_test.cpp \
    sensor_test.cpp \
    sensor_utils_test.cpp \
    test_main.cpp \
    ../app/can_frame_config.cpp \
    ../app/config.cpp \
    ../app/map_sensor.cpp \
    ../app/ntc.cpp

INCLUDEPATH += \
    ../app/

HEADERS += \
    ../app/map_sensor.h\
    ../app/config.h\
    ../app/ntc.h\
    ../app/sensor.h\
    ../app/sensor_source.h\
    compare_float.h \
    map_test.h \
    config_test.h \
    ntc_test.h \
    sensor_test.h \
    sensor_utils_test.h
