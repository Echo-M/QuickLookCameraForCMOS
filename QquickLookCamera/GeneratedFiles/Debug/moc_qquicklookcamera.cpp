/****************************************************************************
** Meta object code from reading C++ file 'qquicklookcamera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qquicklookcamera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qquicklookcamera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QquickLookCamera_t {
    QByteArrayData data[10];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QquickLookCamera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QquickLookCamera_t qt_meta_stringdata_QquickLookCamera = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QquickLookCamera"
QT_MOC_LITERAL(1, 17, 8), // "OpenFile"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "saveFlie"
QT_MOC_LITERAL(4, 36, 6), // "AECRun"
QT_MOC_LITERAL(5, 43, 4), // "Stop"
QT_MOC_LITERAL(6, 48, 11), // "setExpoTime"
QT_MOC_LITERAL(7, 60, 5), // "_time"
QT_MOC_LITERAL(8, 66, 9), // "setFrRate"
QT_MOC_LITERAL(9, 76, 5) // "_rate"

    },
    "QquickLookCamera\0OpenFile\0\0saveFlie\0"
    "AECRun\0Stop\0setExpoTime\0_time\0setFrRate\0"
    "_rate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QquickLookCamera[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    1,   48,    2, 0x0a /* Public */,
       8,    1,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    7,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void QquickLookCamera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QquickLookCamera *_t = static_cast<QquickLookCamera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OpenFile(); break;
        case 1: _t->saveFlie(); break;
        case 2: _t->AECRun(); break;
        case 3: _t->Stop(); break;
        case 4: _t->setExpoTime((*reinterpret_cast< long long(*)>(_a[1]))); break;
        case 5: _t->setFrRate((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QquickLookCamera::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QquickLookCamera.data,
      qt_meta_data_QquickLookCamera,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QquickLookCamera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QquickLookCamera::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QquickLookCamera.stringdata0))
        return static_cast<void*>(const_cast< QquickLookCamera*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QquickLookCamera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_END_MOC_NAMESPACE
