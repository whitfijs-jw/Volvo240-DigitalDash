/****************************************************************************
** Meta object code from reading C++ file 'warning_light_model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "warning_light_model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'warning_light_model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WarningLightModel_t {
    QByteArrayData data[16];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WarningLightModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WarningLightModel_t qt_meta_stringdata_WarningLightModel = {
    {
QT_MOC_LITERAL(0, 0, 17), // "WarningLightModel"
QT_MOC_LITERAL(1, 18, 9), // "onChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 9), // "onFlipped"
QT_MOC_LITERAL(4, 39, 13), // "onTextChanged"
QT_MOC_LITERAL(5, 53, 19), // "onLightColorChanged"
QT_MOC_LITERAL(6, 73, 5), // "setOn"
QT_MOC_LITERAL(7, 79, 2), // "on"
QT_MOC_LITERAL(8, 82, 10), // "setFlipped"
QT_MOC_LITERAL(9, 93, 7), // "flipped"
QT_MOC_LITERAL(10, 101, 7), // "setText"
QT_MOC_LITERAL(11, 109, 4), // "text"
QT_MOC_LITERAL(12, 114, 13), // "setLightColor"
QT_MOC_LITERAL(13, 128, 5), // "color"
QT_MOC_LITERAL(14, 134, 11), // "warningText"
QT_MOC_LITERAL(15, 146, 10) // "lightColor"

    },
    "WarningLightModel\0onChanged\0\0onFlipped\0"
    "onTextChanged\0onLightColorChanged\0"
    "setOn\0on\0setFlipped\0flipped\0setText\0"
    "text\0setLightColor\0color\0warningText\0"
    "lightColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WarningLightModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       4,   70, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   58,    2, 0x0a /* Public */,
       8,    1,   61,    2, 0x0a /* Public */,
      10,    1,   64,    2, 0x0a /* Public */,
      12,    1,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QColor,   13,

 // properties: name, type, flags
       7, QMetaType::Bool, 0x00495103,
       9, QMetaType::Bool, 0x00495103,
      14, QMetaType::QString, 0x00495003,
      15, QMetaType::QColor, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void WarningLightModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WarningLightModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onChanged(); break;
        case 1: _t->onFlipped(); break;
        case 2: _t->onTextChanged(); break;
        case 3: _t->onLightColorChanged(); break;
        case 4: _t->setOn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setFlipped((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setLightColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WarningLightModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WarningLightModel::onChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WarningLightModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WarningLightModel::onFlipped)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WarningLightModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WarningLightModel::onTextChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WarningLightModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WarningLightModel::onLightColorChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<WarningLightModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->on(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->flipped(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->warningText(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->lightColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<WarningLightModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setOn(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setFlipped(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setLightColor(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject WarningLightModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_WarningLightModel.data,
    qt_meta_data_WarningLightModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WarningLightModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WarningLightModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WarningLightModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int WarningLightModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WarningLightModel::onChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WarningLightModel::onFlipped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WarningLightModel::onTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WarningLightModel::onLightColorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
