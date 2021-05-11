/****************************************************************************
** Meta object code from reading C++ file 'accessory_gauge_model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "accessory_gauge_model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'accessory_gauge_model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AccessoryGaugeModel_t {
    QByteArrayData data[20];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AccessoryGaugeModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AccessoryGaugeModel_t qt_meta_stringdata_AccessoryGaugeModel = {
    {
QT_MOC_LITERAL(0, 0, 19), // "AccessoryGaugeModel"
QT_MOC_LITERAL(1, 20, 15), // "minValueChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 15), // "maxValueChanged"
QT_MOC_LITERAL(4, 53, 19), // "currentValueChanged"
QT_MOC_LITERAL(5, 73, 12), // "unitsChanged"
QT_MOC_LITERAL(6, 86, 15), // "lowAlarmChanged"
QT_MOC_LITERAL(7, 102, 16), // "highAlarmChanged"
QT_MOC_LITERAL(8, 119, 11), // "setMinValue"
QT_MOC_LITERAL(9, 131, 8), // "minValue"
QT_MOC_LITERAL(10, 140, 11), // "setMaxValue"
QT_MOC_LITERAL(11, 152, 8), // "maxValue"
QT_MOC_LITERAL(12, 161, 15), // "setCurrentValue"
QT_MOC_LITERAL(13, 177, 12), // "currentValue"
QT_MOC_LITERAL(14, 190, 8), // "setUnits"
QT_MOC_LITERAL(15, 199, 5), // "units"
QT_MOC_LITERAL(16, 205, 11), // "setLowAlarm"
QT_MOC_LITERAL(17, 217, 8), // "lowAlarm"
QT_MOC_LITERAL(18, 226, 12), // "setHighAlarm"
QT_MOC_LITERAL(19, 239, 9) // "highAlarm"

    },
    "AccessoryGaugeModel\0minValueChanged\0"
    "\0maxValueChanged\0currentValueChanged\0"
    "unitsChanged\0lowAlarmChanged\0"
    "highAlarmChanged\0setMinValue\0minValue\0"
    "setMaxValue\0maxValue\0setCurrentValue\0"
    "currentValue\0setUnits\0units\0setLowAlarm\0"
    "lowAlarm\0setHighAlarm\0highAlarm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AccessoryGaugeModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       6,   98, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,
       5,    0,   77,    2, 0x06 /* Public */,
       6,    0,   78,    2, 0x06 /* Public */,
       7,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   80,    2, 0x0a /* Public */,
      10,    1,   83,    2, 0x0a /* Public */,
      12,    1,   86,    2, 0x0a /* Public */,
      14,    1,   89,    2, 0x0a /* Public */,
      16,    1,   92,    2, 0x0a /* Public */,
      18,    1,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QReal,    9,
    QMetaType::Void, QMetaType::QReal,   11,
    QMetaType::Void, QMetaType::QReal,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QReal,   17,
    QMetaType::Void, QMetaType::QReal,   19,

 // properties: name, type, flags
       9, QMetaType::QReal, 0x00495103,
      11, QMetaType::QReal, 0x00495103,
      13, QMetaType::QReal, 0x00495103,
      15, QMetaType::QString, 0x00495103,
      17, QMetaType::QReal, 0x00495103,
      19, QMetaType::QReal, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,

       0        // eod
};

void AccessoryGaugeModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AccessoryGaugeModel *_t = static_cast<AccessoryGaugeModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->minValueChanged(); break;
        case 1: _t->maxValueChanged(); break;
        case 2: _t->currentValueChanged(); break;
        case 3: _t->unitsChanged(); break;
        case 4: _t->lowAlarmChanged(); break;
        case 5: _t->highAlarmChanged(); break;
        case 6: _t->setMinValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 7: _t->setMaxValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 8: _t->setCurrentValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 9: _t->setUnits((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->setLowAlarm((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 11: _t->setHighAlarm((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AccessoryGaugeModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccessoryGaugeModel::minValueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AccessoryGaugeModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccessoryGaugeModel::maxValueChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AccessoryGaugeModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccessoryGaugeModel::currentValueChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (AccessoryGaugeModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccessoryGaugeModel::unitsChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (AccessoryGaugeModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccessoryGaugeModel::lowAlarmChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (AccessoryGaugeModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccessoryGaugeModel::highAlarmChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        AccessoryGaugeModel *_t = static_cast<AccessoryGaugeModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->minValue(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->maxValue(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = _t->currentValue(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->units(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = _t->lowAlarm(); break;
        case 5: *reinterpret_cast< qreal*>(_v) = _t->highAlarm(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        AccessoryGaugeModel *_t = static_cast<AccessoryGaugeModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMinValue(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setMaxValue(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setCurrentValue(*reinterpret_cast< qreal*>(_v)); break;
        case 3: _t->setUnits(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setLowAlarm(*reinterpret_cast< qreal*>(_v)); break;
        case 5: _t->setHighAlarm(*reinterpret_cast< qreal*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject AccessoryGaugeModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_AccessoryGaugeModel.data,
      qt_meta_data_AccessoryGaugeModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AccessoryGaugeModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AccessoryGaugeModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AccessoryGaugeModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int AccessoryGaugeModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AccessoryGaugeModel::minValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AccessoryGaugeModel::maxValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AccessoryGaugeModel::currentValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AccessoryGaugeModel::unitsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void AccessoryGaugeModel::lowAlarmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void AccessoryGaugeModel::highAlarmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
