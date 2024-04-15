QT += core gui testlib

TARGET = DashUnitTests
TEMPLATE = app

CONFIG += console
CONFIG += c++17

SOURCES += \
    config_test.cpp \
    gear_indicator_test.cpp \
    map_test.cpp \
    ntc_test.cpp \
    sensor_test.cpp \
    sensor_utils_test.cpp \
    test_main.cpp

INCLUDEPATH += \
    ../app/

HEADERS += \
    ../app/map_sensor.h\
    ../app/config.h\
    ../app/ntc.h\
    ../app/sensor.h\
    ../app/sensor_gear_indicator.h \
    ../app/sensor_source.h\
    ../app/sensor_source_tach.h \
    ../app/sensor_source_vss.h \
    compare_float.h \
    gear_indicator_test.h \
    map_test.h \
    config_test.h \
    ntc_test.h \
    sensor_test.h \
    sensor_utils_test.h
