/****************************************************************************
** Meta object code from reading C++ file 'PlayerViewController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PlayerViewController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlayerViewController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlayerViewController_t {
    QByteArrayData data[4];
    char stringdata[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayerViewController_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayerViewController_t qt_meta_stringdata_PlayerViewController = {
    {
QT_MOC_LITERAL(0, 0, 20), // "PlayerViewController"
QT_MOC_LITERAL(1, 21, 32), // "ShowMenu_ViewToMainWindow_Signal"
QT_MOC_LITERAL(2, 54, 0), // ""
QT_MOC_LITERAL(3, 55, 15) // "QuitGame_Signal"

    },
    "PlayerViewController\0"
    "ShowMenu_ViewToMainWindow_Signal\0\0"
    "QuitGame_Signal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerViewController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlayerViewController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayerViewController *_t = static_cast<PlayerViewController *>(_o);
        switch (_id) {
        case 0: _t->ShowMenu_ViewToMainWindow_Signal(); break;
        case 1: _t->QuitGame_Signal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PlayerViewController::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayerViewController::ShowMenu_ViewToMainWindow_Signal)) {
                *result = 0;
            }
        }
        {
            typedef void (PlayerViewController::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayerViewController::QuitGame_Signal)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PlayerViewController::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_PlayerViewController.data,
      qt_meta_data_PlayerViewController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PlayerViewController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerViewController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerViewController.stringdata))
        return static_cast<void*>(const_cast< PlayerViewController*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int PlayerViewController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void PlayerViewController::ShowMenu_ViewToMainWindow_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void PlayerViewController::QuitGame_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
struct qt_meta_stringdata_M_Element_Animation_t {
    QByteArrayData data[4];
    char stringdata[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_M_Element_Animation_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_M_Element_Animation_t qt_meta_stringdata_M_Element_Animation = {
    {
QT_MOC_LITERAL(0, 0, 19), // "M_Element_Animation"
QT_MOC_LITERAL(1, 20, 13), // "Damage_signal"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 6) // "Damage"

    },
    "M_Element_Animation\0Damage_signal\0\0"
    "Damage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_M_Element_Animation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void M_Element_Animation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        M_Element_Animation *_t = static_cast<M_Element_Animation *>(_o);
        switch (_id) {
        case 0: _t->Damage_signal((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (M_Element_Animation::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&M_Element_Animation::Damage_signal)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject M_Element_Animation::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_M_Element_Animation.data,
      qt_meta_data_M_Element_Animation,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *M_Element_Animation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *M_Element_Animation::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_M_Element_Animation.stringdata))
        return static_cast<void*>(const_cast< M_Element_Animation*>(this));
    return QObject::qt_metacast(_clname);
}

int M_Element_Animation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void M_Element_Animation::Damage_signal(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
