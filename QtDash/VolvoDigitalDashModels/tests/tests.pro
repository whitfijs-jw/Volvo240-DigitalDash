QT += core gui testlib

TARGET = DashUnitTests
TEMPLATE = app

CONFIG += console
CONFIG += c++17

SOURCES += \
    can_frame_config_test.cpp \
    config_test.cpp \
    gear_indicator_test.cpp \
    map_test.cpp \
    ntc_test.cpp \
    sensor_test.cpp \
    sensor_utils_test.cpp \
    test_main.cpp \
    ../app/src/config/can_frame_config.cpp \
    ../app/src/config/config.cpp \
    ../app/src/ll/pulse_counter.cpp \
    ../app/src/sensor/map_sensor.cpp \
    ../app/src/sensor/ntc.cpp \
    ../app/src/sensor/sensor_gear_indicator.cpp \
    ../app/src/utils/units.cpp \
    ../app/src/utils/sensor_utils.cpp \

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
    ../app/inc/ll/pulse_counter.h \
    ../app/inc/sensor/ntc.h\
    ../app/inc/sensor/sensor.h\
    ../app/inc/sensor/sensor_gear_indicator.h \
    ../app/inc/sensor_source/sensor_source.h \
    ../app/inc/sensor_source/sensor_source_vss.h \
    ../app/inc/sensor_source/sensor_source_tach.h \
    can_frame_config_test.h \
    compare_float.h \
    gear_indicator_test.h \
    map_test.h \
    config_test.h \
    ntc_test.h \
    sensor_test.h \
    sensor_utils_test.h \
    gear_predictive_filter.h
