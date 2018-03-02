/****************************************************************************
** Meta object code from reading C++ file 'unitwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../unitwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'unitwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UnitWindow_t {
    QByteArrayData data[9];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UnitWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UnitWindow_t qt_meta_stringdata_UnitWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "UnitWindow"
QT_MOC_LITERAL(1, 11, 19), // "backButtonPressSlot"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 20), // "musicButtonPressSlot"
QT_MOC_LITERAL(4, 53, 23), // "settingsButtonPressSlot"
QT_MOC_LITERAL(5, 77, 19), // "tempRibbonPressSlot"
QT_MOC_LITERAL(6, 97, 20), // "lightRibbonPressSlot"
QT_MOC_LITERAL(7, 118, 23), // "moistureRibbonPressSlot"
QT_MOC_LITERAL(8, 142, 23) // "humidityRibbonPressSlot"

    },
    "UnitWindow\0backButtonPressSlot\0\0"
    "musicButtonPressSlot\0settingsButtonPressSlot\0"
    "tempRibbonPressSlot\0lightRibbonPressSlot\0"
    "moistureRibbonPressSlot\0humidityRibbonPressSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UnitWindow[] = {

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
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UnitWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UnitWindow *_t = static_cast<UnitWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backButtonPressSlot(); break;
        case 1: _t->musicButtonPressSlot(); break;
        case 2: _t->settingsButtonPressSlot(); break;
        case 3: _t->tempRibbonPressSlot(); break;
        case 4: _t->lightRibbonPressSlot(); break;
        case 5: _t->moistureRibbonPressSlot(); break;
        case 6: _t->humidityRibbonPressSlot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject UnitWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UnitWindow.data,
      qt_meta_data_UnitWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *UnitWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UnitWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UnitWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int UnitWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
