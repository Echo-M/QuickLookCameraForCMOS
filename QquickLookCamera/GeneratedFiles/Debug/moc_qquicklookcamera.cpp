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
    QByteArrayData data[15];
    char stringdata[126];
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
QT_MOC_LITERAL(4, 36, 6), // "AECRun"
QT_MOC_LITERAL(5, 43, 4), // "Stop"
QT_MOC_LITERAL(6, 48, 11), // "setExpoTime"
QT_MOC_LITERAL(7, 60, 5), // "_time"
QT_MOC_LITERAL(8, 66, 9), // "setFrRate"
QT_MOC_LITERAL(9, 76, 5), // "_rate"
QT_MOC_LITERAL(10, 82, 7), // "setAGCG"
QT_MOC_LITERAL(11, 90, 10), // "_totalGain"
QT_MOC_LITERAL(12, 101, 5), // "setDG"
QT_MOC_LITERAL(13, 107, 3), // "_dg"
QT_MOC_LITERAL(14, 111, 14) // "AGCGBoxChanged"

    },
    "QquickLookCamera\0OpenFile\0\0saveFlie\0"
    "AECRun\0Stop\0setExpoTime\0_time\0setFrRate\0"
    "_rate\0setAGCG\0_totalGain\0setDG\0_dg\0"
    "AGCGBoxChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QquickLookCamera[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    1,   63,    2, 0x0a /* Public */,
       8,    1,   66,    2, 0x0a /* Public */,
      10,    1,   69,    2, 0x0a /* Public */,
      12,    1,   72,    2, 0x0a /* Public */,
      14,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Float,   11,
    QMetaType::Void, QMetaType::Float,   13,
    QMetaType::Void,

       0        // eod
};

void QquickLookCamera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QquickLookCamera *_t = static_cast<QquickLookCamera *>(_o);
        switch (_id) {
        case 0: _t->OpenFile(); break;
        case 1: _t->saveFlie(); break;
        case 2: _t->AECRun(); break;
        case 3: _t->Stop(); break;
        case 4: _t->setExpoTime((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 5: _t->setFrRate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setAGCG((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->setDG((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->AGCGBoxChanged(); break;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
