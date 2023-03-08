/****************************************************************************
** Meta object code from reading C++ file 'UIController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UIController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UIController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UIController_t {
    QByteArrayData data[16];
    char stringdata0[352];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UIController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UIController_t qt_meta_stringdata_UIController = {
    {
QT_MOC_LITERAL(0, 0, 12), // "UIController"
QT_MOC_LITERAL(1, 13, 20), // "on_Open_File_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 23), // "on_Contrast_sliderMoved"
QT_MOC_LITERAL(4, 59, 8), // "position"
QT_MOC_LITERAL(5, 68, 25), // "on_Brightness_sliderMoved"
QT_MOC_LITERAL(6, 94, 25), // "on_Grayscale_stateChanged"
QT_MOC_LITERAL(7, 120, 4), // "arg1"
QT_MOC_LITERAL(8, 125, 37), // "on_Edge_detection_currentInde..."
QT_MOC_LITERAL(9, 163, 24), // "on_Choose_Camera_clicked"
QT_MOC_LITERAL(10, 188, 20), // "on_Save_File_clicked"
QT_MOC_LITERAL(11, 209, 25), // "on_Canny_Max_valueChanged"
QT_MOC_LITERAL(12, 235, 25), // "on_Canny_Min_valueChanged"
QT_MOC_LITERAL(13, 261, 29), // "on_Delta_Spinner_valueChanged"
QT_MOC_LITERAL(14, 291, 29), // "on_Scale_Spinner_valueChanged"
QT_MOC_LITERAL(15, 321, 30) // "on_Kernel_Spinner_valueChanged"

    },
    "UIController\0on_Open_File_clicked\0\0"
    "on_Contrast_sliderMoved\0position\0"
    "on_Brightness_sliderMoved\0"
    "on_Grayscale_stateChanged\0arg1\0"
    "on_Edge_detection_currentIndexChanged\0"
    "on_Choose_Camera_clicked\0on_Save_File_clicked\0"
    "on_Canny_Max_valueChanged\0"
    "on_Canny_Min_valueChanged\0"
    "on_Delta_Spinner_valueChanged\0"
    "on_Scale_Spinner_valueChanged\0"
    "on_Kernel_Spinner_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UIController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    1,   75,    2, 0x08 /* Private */,
       5,    1,   78,    2, 0x08 /* Private */,
       6,    1,   81,    2, 0x08 /* Private */,
       8,    1,   84,    2, 0x08 /* Private */,
       9,    0,   87,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    1,   89,    2, 0x08 /* Private */,
      12,    1,   92,    2, 0x08 /* Private */,
      13,    1,   95,    2, 0x08 /* Private */,
      14,    1,   98,    2, 0x08 /* Private */,
      15,    1,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void UIController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UIController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_Open_File_clicked(); break;
        case 1: _t->on_Contrast_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_Brightness_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_Grayscale_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_Edge_detection_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_Choose_Camera_clicked(); break;
        case 6: _t->on_Save_File_clicked(); break;
        case 7: _t->on_Canny_Max_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_Canny_Min_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_Delta_Spinner_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->on_Scale_Spinner_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->on_Kernel_Spinner_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UIController::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_UIController.data,
    qt_meta_data_UIController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UIController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UIController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UIController.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int UIController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
