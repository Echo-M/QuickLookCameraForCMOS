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
    QByteArrayData data[13];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QquickLookCamera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QquickLookCamera_t qt_meta_stringdata_QquickLookCamera = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QquickLookCamera"
QT_MOC_LITERAL(1, 17, 12), // "showOpenFile"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 8), // "stopComs"
QT_MOC_LITERAL(4, 40, 12), // "autoExposure"
QT_MOC_LITERAL(5, 53, 14), // "manualExposure"
QT_MOC_LITERAL(6, 68, 12), // "showAboutMSg"
QT_MOC_LITERAL(7, 81, 12), // "showExpoTime"
QT_MOC_LITERAL(8, 94, 11), // "showDigGain"
QT_MOC_LITERAL(9, 106, 7), // "showATI"
QT_MOC_LITERAL(10, 114, 9), // "showAG_CG"
QT_MOC_LITERAL(11, 124, 12), // "showRegister"
QT_MOC_LITERAL(12, 137, 8) // "saveFlie"

    },
    "QquickLookCamera\0showOpenFile\0\0stopComs\0"
    "autoExposure\0manualExposure\0showAboutMSg\0"
    "showExpoTime\0showDigGain\0showATI\0"
    "showAG_CG\0showRegister\0saveFlie"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QquickLookCamera[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QquickLookCamera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QquickLookCamera *_t = static_cast<QquickLookCamera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showOpenFile(); break;
        case 1: _t->stopComs(); break;
        case 2: _t->autoExposure(); break;
        case 3: _t->manualExposure(); break;
        case 4: _t->showAboutMSg(); break;
        case 5: _t->showExpoTime(); break;
        case 6: _t->showDigGain(); break;
        case 7: _t->showATI(); break;
        case 8: _t->showAG_CG(); break;
        case 9: _t->showRegister(); break;
        case 10: _t->saveFlie(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
