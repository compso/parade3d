/****************************************************************************
** Meta object code from reading C++ file 'glview.h'
**
** Created: Thu Apr 16 09:55:42 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/glview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLView[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      14,    8,    7,    7, 0x05,
      42,    8,    7,    7, 0x05,
      74,   69,    7,    7, 0x05,
      98,   92,    7,    7, 0x05,
     121,  117,    7,    7, 0x05,
     138,  117,    7,    7, 0x05,
     161,  156,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     178,    7,    7,    7, 0x0a,
     189,    7,    7,    7, 0x0a,
     202,    7,    7,    7, 0x0a,
     215,    7,    7,    7, 0x0a,
     235,  226,    7,    7, 0x0a,
     258,  253,    7,    7, 0x0a,
     282,    7,    7,    7, 0x2a,
     302,    7,    7,    7, 0x0a,
     325,  253,    7,    7, 0x0a,
     348,    7,    7,    7, 0x2a,
     367,    7,    7,    7, 0x0a,
     389,  156,    7,    7, 0x0a,
     402,    7,    7,    7, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_GLView[] = {
    "GLView\0\0drawn\0parGridIsDrawnChanged(bool)\0"
    "parFPSIsDrawnChanged(bool)\0wire\0"
    "parWireView(bool)\0shade\0parShadeView(bool)\0"
    "tex\0parTexView(bool)\0parFlatView(bool)\0"
    "mode\0modeChanged(int)\0homeView()\0"
    "clearScene()\0drawSpiral()\0drawCube()\0"
    "filename\0loadFile(QString)\0draw\0"
    "parSetGridIsDrawn(bool)\0parSetGridIsDrawn()\0"
    "parToggleGridIsDrawn()\0parSetFPSIsDrawn(bool)\0"
    "parSetFPSIsDrawn()\0parToggleFPSIsDrawn()\0"
    "setMode(int)\0setMode()\0"
};

const QMetaObject GLView::staticMetaObject = {
    { &QGLViewer::staticMetaObject, qt_meta_stringdata_GLView,
      qt_meta_data_GLView, 0 }
};

const QMetaObject *GLView::metaObject() const
{
    return &staticMetaObject;
}

void *GLView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLView))
        return static_cast<void*>(const_cast< GLView*>(this));
    return QGLViewer::qt_metacast(_clname);
}

int GLView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLViewer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: parGridIsDrawnChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: parFPSIsDrawnChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: parWireView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: parShadeView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: parTexView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: parFlatView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: modeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: homeView(); break;
        case 8: clearScene(); break;
        case 9: drawSpiral(); break;
        case 10: drawCube(); break;
        case 11: loadFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: parSetGridIsDrawn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: parSetGridIsDrawn(); break;
        case 14: parToggleGridIsDrawn(); break;
        case 15: parSetFPSIsDrawn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: parSetFPSIsDrawn(); break;
        case 17: parToggleFPSIsDrawn(); break;
        case 18: setMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: setMode(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void GLView::parGridIsDrawnChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GLView::parFPSIsDrawnChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GLView::parWireView(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GLView::parShadeView(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GLView::parTexView(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GLView::parFlatView(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GLView::modeChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
