/****************************************************************************
** Meta object code from reading C++ file 'qquicklookcamera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qquicklookcamera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qquicklookcamera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QquickLookCamera_t {
    QByteArrayData data[10];
    char stringdata[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QquickLookCamera_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QquickLookCamera_t qt_meta_stringdata_QquickLookCamera = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QquickLookCamera"
QT_MOC_LITERAL(1, 17, 8), // "OpenFile"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "saveFlie"
QT_MOC_LITERAL(4, 36, 7), // "Initial"
QT_MOC_LITERAL(5, 44, 5), // "Start"
QT_MOC_LITERAL(6, 50, 4), // "Stop"
QT_MOC_LITERAL(7, 55, 15), // "setExposureRate"
QT_MOC_LITERAL(8, 71, 5), // "_rate"
QT_MOC_LITERAL(9, 77, 12) // "setFrameRate"

    },
    "QquickLookCamera\0OpenFile\0\0saveFlie\0"
    "Initial\0Start\0Stop\0setExposureRate\0"
    "_rate\0setFrameRate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QquickLookCamera[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    1,   54,    2, 0x0a /* Public */,
       9,    1,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void QquickLookCamera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QquickLookCamera *_t = static_cast<QquickLookCamera *>(_o);
        switch (_id) {
        case 0: _t->OpenFile(); break;
        case 1: _t->saveFlie(); break;
        case 2: _t->Initial(); break;
        case 3: _t->Start(); break;
        case 4: _t->Stop(); break;
        case 5: _t->setExposureRate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setFrameRate((*reinterpret_cast< int(*)>(_a[1]))); break;
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
    if (!strcmp(_clname, qt_meta_stringdata_QquickLookCamera.stringdata))
        return static_cast<void*>(const_cast< QquickLookCamera*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QquickLookCamera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
