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
    ../app/src/can_frame_config.cpp \
    ../app/src/config.cpp \
    ../app/src/map_sensor.cpp \
    ../app/src/ntc.cpp \
    ../app/src/units.cpp

INCLUDEPATH += \
    ../app/

HEADERS += \
    ../app/inc/map_sensor.h\
    ../app/inc/config.h\
    ../app/inc/ntc.h\
    ../app/inc/sensor.h\
    ../app/inc/sensor_source.h\
    compare_float.h \
    map_test.h \
    config_test.h \
    ntc_test.h \
    sensor_test.h \
    sensor_utils_test.h
