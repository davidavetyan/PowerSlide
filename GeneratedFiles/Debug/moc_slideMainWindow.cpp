/****************************************************************************
** Meta object code from reading C++ file 'slideMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/gui/slideMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'slideMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GUI__SlideMainWindow_t {
    QByteArrayData data[12];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GUI__SlideMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GUI__SlideMainWindow_t qt_meta_stringdata_GUI__SlideMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 20), // "GUI::SlideMainWindow"
QT_MOC_LITERAL(1, 21, 16), // "onNewFileClicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 17), // "onOpenFileClicked"
QT_MOC_LITERAL(4, 57, 17), // "onNewSlideClicked"
QT_MOC_LITERAL(5, 75, 18), // "onSaveImageClicked"
QT_MOC_LITERAL(6, 94, 13), // "onUndoClicked"
QT_MOC_LITERAL(7, 108, 13), // "onRedoClicked"
QT_MOC_LITERAL(8, 122, 13), // "onLineClicked"
QT_MOC_LITERAL(9, 136, 13), // "onRectClicked"
QT_MOC_LITERAL(10, 150, 16), // "onEllipseClicked"
QT_MOC_LITERAL(11, 167, 16) // "onActionExecuted"

    },
    "GUI::SlideMainWindow\0onNewFileClicked\0"
    "\0onOpenFileClicked\0onNewSlideClicked\0"
    "onSaveImageClicked\0onUndoClicked\0"
    "onRedoClicked\0onLineClicked\0onRectClicked\0"
    "onEllipseClicked\0onActionExecuted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI__SlideMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x09 /* Protected */,
       3,    0,   65,    2, 0x09 /* Protected */,
       4,    0,   66,    2, 0x09 /* Protected */,
       5,    0,   67,    2, 0x09 /* Protected */,
       6,    0,   68,    2, 0x09 /* Protected */,
       7,    0,   69,    2, 0x09 /* Protected */,
       8,    0,   70,    2, 0x09 /* Protected */,
       9,    0,   71,    2, 0x09 /* Protected */,
      10,    0,   72,    2, 0x09 /* Protected */,
      11,    0,   73,    2, 0x09 /* Protected */,

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

       0        // eod
};

void GUI::SlideMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SlideMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onNewFileClicked(); break;
        case 1: _t->onOpenFileClicked(); break;
        case 2: _t->onNewSlideClicked(); break;
        case 3: _t->onSaveImageClicked(); break;
        case 4: _t->onUndoClicked(); break;
        case 5: _t->onRedoClicked(); break;
        case 6: _t->onLineClicked(); break;
        case 7: _t->onRectClicked(); break;
        case 8: _t->onEllipseClicked(); break;
        case 9: _t->onActionExecuted(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject GUI::SlideMainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_GUI__SlideMainWindow.data,
    qt_meta_data_GUI__SlideMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GUI::SlideMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI::SlideMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI__SlideMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int GUI::SlideMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
