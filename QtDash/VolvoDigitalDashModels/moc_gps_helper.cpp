/****************************************************************************
** Meta object code from reading C++ file 'gps_helper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "gps_helper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gps_helper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GpsHelper_t {
    QByteArrayData data[16];
    char stringdata0[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GpsHelper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GpsHelper_t qt_meta_stringdata_GpsHelper = {
    {
QT_MOC_LITERAL(0, 0, 9), // "GpsHelper"
QT_MOC_LITERAL(1, 10, 22), // "speedUpdateMeterPerSec"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 3), // "mps"
QT_MOC_LITERAL(4, 38, 23), // "speedUpdateMilesPerHour"
QT_MOC_LITERAL(5, 62, 3), // "mph"
QT_MOC_LITERAL(6, 66, 14), // "speedUpdateKph"
QT_MOC_LITERAL(7, 81, 3), // "kph"
QT_MOC_LITERAL(8, 85, 19), // "headingUpdateDegree"
QT_MOC_LITERAL(9, 105, 7), // "heading"
QT_MOC_LITERAL(10, 113, 13), // "headingUpdate"
QT_MOC_LITERAL(11, 127, 4), // "stop"
QT_MOC_LITERAL(12, 132, 14), // "positionUpdate"
QT_MOC_LITERAL(13, 147, 16), // "QGeoPositionInfo"
QT_MOC_LITERAL(14, 164, 4), // "data"
QT_MOC_LITERAL(15, 169, 5) // "close"

    },
    "GpsHelper\0speedUpdateMeterPerSec\0\0mps\0"
    "speedUpdateMilesPerHour\0mph\0speedUpdateKph\0"
    "kph\0headingUpdateDegree\0heading\0"
    "headingUpdate\0stop\0positionUpdate\0"
    "QGeoPositionInfo\0data\0close"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GpsHelper[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    1,   60,    2, 0x06 /* Public */,
       8,    1,   63,    2, 0x06 /* Public */,
      10,    1,   66,    2, 0x06 /* Public */,
      11,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   70,    2, 0x0a /* Public */,
      15,    0,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal,    3,
    QMetaType::Void, QMetaType::QReal,    5,
    QMetaType::Void, QMetaType::QReal,    7,
    QMetaType::Void, QMetaType::QReal,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,

       0        // eod
};

void GpsHelper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GpsHelper *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->speedUpdateMeterPerSec((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->speedUpdateMilesPerHour((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 2: _t->speedUpdateKph((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 3: _t->headingUpdateDegree((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 4: _t->headingUpdate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->stop(); break;
        case 6: _t->positionUpdate((*reinterpret_cast< QGeoPositionInfo(*)>(_a[1]))); break;
        case 7: _t->close(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGeoPositionInfo >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GpsHelper::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpsHelper::speedUpdateMeterPerSec)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GpsHelper::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpsHelper::speedUpdateMilesPerHour)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GpsHelper::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpsHelper::speedUpdateKph)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GpsHelper::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpsHelper::headingUpdateDegree)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GpsHelper::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpsHelper::headingUpdate)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GpsHelper::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpsHelper::stop)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GpsHelper::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GpsHelper.data,
    qt_meta_data_GpsHelper,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GpsHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GpsHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GpsHelper.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GpsHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void GpsHelper::speedUpdateMeterPerSec(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GpsHelper::speedUpdateMilesPerHour(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GpsHelper::speedUpdateKph(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GpsHelper::headingUpdateDegree(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GpsHelper::headingUpdate(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GpsHelper::stop()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
