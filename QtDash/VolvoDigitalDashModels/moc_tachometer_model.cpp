/****************************************************************************
** Meta object code from reading C++ file 'tachometer_model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "tachometer_model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tachometer_model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TachometerModel_t {
    QByteArrayData data[11];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TachometerModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TachometerModel_t qt_meta_stringdata_TachometerModel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TachometerModel"
QT_MOC_LITERAL(1, 16, 10), // "rpmChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 14), // "redLineChanged"
QT_MOC_LITERAL(4, 43, 13), // "maxRpmChanged"
QT_MOC_LITERAL(5, 57, 6), // "setRpm"
QT_MOC_LITERAL(6, 64, 3), // "rpm"
QT_MOC_LITERAL(7, 68, 10), // "setRedLine"
QT_MOC_LITERAL(8, 79, 7), // "redLine"
QT_MOC_LITERAL(9, 87, 9), // "setMaxRpm"
QT_MOC_LITERAL(10, 97, 6) // "maxRpm"

    },
    "TachometerModel\0rpmChanged\0\0redLineChanged\0"
    "maxRpmChanged\0setRpm\0rpm\0setRedLine\0"
    "redLine\0setMaxRpm\0maxRpm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TachometerModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       3,   56, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   47,    2, 0x0a /* Public */,
       7,    1,   50,    2, 0x0a /* Public */,
       9,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,

 // properties: name, type, flags
       6, QMetaType::Int, 0x00495103,
       8, QMetaType::Int, 0x00495103,
      10, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void TachometerModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TachometerModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rpmChanged(); break;
        case 1: _t->redLineChanged(); break;
        case 2: _t->maxRpmChanged(); break;
        case 3: _t->setRpm((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setRedLine((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setMaxRpm((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TachometerModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TachometerModel::rpmChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TachometerModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TachometerModel::redLineChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TachometerModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TachometerModel::maxRpmChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<TachometerModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->rpm(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->redLine(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->maxRpm(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TachometerModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRpm(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setRedLine(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setMaxRpm(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject TachometerModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_TachometerModel.data,
    qt_meta_data_TachometerModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TachometerModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TachometerModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TachometerModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int TachometerModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void TachometerModel::rpmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TachometerModel::redLineChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TachometerModel::maxRpmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
