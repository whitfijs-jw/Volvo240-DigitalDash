/****************************************************************************
** Meta object code from reading C++ file 'speedometer_model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "speedometer_model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'speedometer_model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SpeedometerModel_t {
    QByteArrayData data[20];
    char stringdata0[243];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpeedometerModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpeedometerModel_t qt_meta_stringdata_SpeedometerModel = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SpeedometerModel"
QT_MOC_LITERAL(1, 17, 15), // "minValueChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 15), // "maxValueChanged"
QT_MOC_LITERAL(4, 50, 19), // "currentValueChanged"
QT_MOC_LITERAL(5, 70, 12), // "unitsChanged"
QT_MOC_LITERAL(6, 83, 15), // "topValueChanged"
QT_MOC_LITERAL(7, 99, 15), // "topUnitsChanged"
QT_MOC_LITERAL(8, 115, 11), // "setMinValue"
QT_MOC_LITERAL(9, 127, 8), // "minValue"
QT_MOC_LITERAL(10, 136, 11), // "setMaxValue"
QT_MOC_LITERAL(11, 148, 8), // "maxValue"
QT_MOC_LITERAL(12, 157, 15), // "setCurrentValue"
QT_MOC_LITERAL(13, 173, 12), // "currentValue"
QT_MOC_LITERAL(14, 186, 8), // "setUnits"
QT_MOC_LITERAL(15, 195, 5), // "units"
QT_MOC_LITERAL(16, 201, 11), // "setTopValue"
QT_MOC_LITERAL(17, 213, 8), // "topValue"
QT_MOC_LITERAL(18, 222, 11), // "setTopUnits"
QT_MOC_LITERAL(19, 234, 8) // "topUnits"

    },
    "SpeedometerModel\0minValueChanged\0\0"
    "maxValueChanged\0currentValueChanged\0"
    "unitsChanged\0topValueChanged\0"
    "topUnitsChanged\0setMinValue\0minValue\0"
    "setMaxValue\0maxValue\0setCurrentValue\0"
    "currentValue\0setUnits\0units\0setTopValue\0"
    "topValue\0setTopUnits\0topUnits"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpeedometerModel[] = {

 // content:
       8,       // revision
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
    QMetaType::Void, QMetaType::QString,   19,

 // properties: name, type, flags
       9, QMetaType::QReal, 0x00495103,
      11, QMetaType::QReal, 0x00495103,
      13, QMetaType::QReal, 0x00495103,
      15, QMetaType::QString, 0x00495103,
      17, QMetaType::QReal, 0x00495103,
      19, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,

       0        // eod
};

void SpeedometerModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SpeedometerModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->minValueChanged(); break;
        case 1: _t->maxValueChanged(); break;
        case 2: _t->currentValueChanged(); break;
        case 3: _t->unitsChanged(); break;
        case 4: _t->topValueChanged(); break;
        case 5: _t->topUnitsChanged(); break;
        case 6: _t->setMinValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 7: _t->setMaxValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 8: _t->setCurrentValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 9: _t->setUnits((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->setTopValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 11: _t->setTopUnits((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SpeedometerModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SpeedometerModel::minValueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SpeedometerModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SpeedometerModel::maxValueChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SpeedometerModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SpeedometerModel::currentValueChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SpeedometerModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SpeedometerModel::unitsChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SpeedometerModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SpeedometerModel::topValueChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SpeedometerModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SpeedometerModel::topUnitsChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SpeedometerModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->minValue(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->maxValue(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = _t->currentValue(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->units(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = _t->topValue(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->topUnits(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SpeedometerModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMinValue(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setMaxValue(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setCurrentValue(*reinterpret_cast< qreal*>(_v)); break;
        case 3: _t->setUnits(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setTopValue(*reinterpret_cast< qreal*>(_v)); break;
        case 5: _t->setTopUnits(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject SpeedometerModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_SpeedometerModel.data,
    qt_meta_data_SpeedometerModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SpeedometerModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpeedometerModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SpeedometerModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int SpeedometerModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SpeedometerModel::minValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SpeedometerModel::maxValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SpeedometerModel::currentValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SpeedometerModel::unitsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SpeedometerModel::topValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SpeedometerModel::topUnitsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
