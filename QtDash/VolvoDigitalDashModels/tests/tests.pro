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
    ../app/src/config/can_frame_config.cpp \
    ../app/src/config/config.cpp \
    ../app/src/sensor/map_sensor.cpp \
    ../app/src/sensor/ntc.cpp \
    ../app/src/utils/units.cpp \
    ../app/src/utils/sensor_utils.cpp

INCLUDEPATH += \
    ../app/ \
    ../app/inc/config \
    ../app/inc/dash \
    ../app/inc/gauge \
    ../app/inc/ll \
    ../app/inc/model \
    ../app/inc/sensor \
    ../app/inc/sensor_source \
    ../app/inc/utils

HEADERS += \
    ../app/inc/sensor/map_sensor.h\
    ../app/inc/config/config.h\
    ../app/inc/sensor/ntc.h\
    ../app/inc/sensor/sensor.h\
    ../app/inc/sensor_source/sensor_source.h\
    compare_float.h \
    map_test.h \
    config_test.h \
    ntc_test.h \
    sensor_test.h \
    sensor_utils_test.h
