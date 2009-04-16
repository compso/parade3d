/****************************************************************************
** Meta object code from reading C++ file 'objects.h'
**
** Created: Thu Apr 16 09:55:41 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/objects.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objects.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Objects[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,    9,    8,    8, 0x0a,
      51,    9,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Objects[] = {
    "Objects\0\0wire,r,g,b\0spiral(bool,float,float,float)\0"
    "cube(bool,float,float,float)\0"
};

const QMetaObject Objects::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Objects,
      qt_meta_data_Objects, 0 }
};

const QMetaObject *Objects::metaObject() const
{
    return &staticMetaObject;
}

void *Objects::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Objects))
        return static_cast<void*>(const_cast< Objects*>(this));
    return QObject::qt_metacast(_clname);
}

int Objects::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: spiral((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 1: cube((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
