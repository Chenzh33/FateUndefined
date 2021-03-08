/****************************************************************************
** Meta object code from reading C++ file 'SinglePlayerController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SinglePlayerController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SinglePlayerController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SinglePlayerController_t {
    QByteArrayData data[4];
    char stringdata[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SinglePlayerController_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SinglePlayerController_t qt_meta_stringdata_SinglePlayerController = {
    {
QT_MOC_LITERAL(0, 0, 22), // "SinglePlayerController"
QT_MOC_LITERAL(1, 23, 32), // "ShowMenu_ViewToMainWindow_Signal"
QT_MOC_LITERAL(2, 56, 0), // ""
QT_MOC_LITERAL(3, 57, 15) // "QuitGame_Signal"

    },
    "SinglePlayerController\0"
    "ShowMenu_ViewToMainWindow_Signal\0\0"
    "QuitGame_Signal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SinglePlayerController[] = {

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

void SinglePlayerController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SinglePlayerController *_t = static_cast<SinglePlayerController *>(_o);
        switch (_id) {
        case 0: _t->ShowMenu_ViewToMainWindow_Signal(); break;
        case 1: _t->QuitGame_Signal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SinglePlayerController::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SinglePlayerController::ShowMenu_ViewToMainWindow_Signal)) {
                *result = 0;
            }
        }
        {
            typedef void (SinglePlayerController::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SinglePlayerController::QuitGame_Signal)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SinglePlayerController::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_SinglePlayerController.data,
      qt_meta_data_SinglePlayerController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SinglePlayerController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SinglePlayerController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SinglePlayerController.stringdata))
        return static_cast<void*>(const_cast< SinglePlayerController*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int SinglePlayerController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SinglePlayerController::ShowMenu_ViewToMainWindow_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void SinglePlayerController::QuitGame_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
struct qt_meta_stringdata_Element_Animation_t {
    QByteArrayData data[4];
    char stringdata[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Element_Animation_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Element_Animation_t qt_meta_stringdata_Element_Animation = {
    {
QT_MOC_LITERAL(0, 0, 17), // "Element_Animation"
QT_MOC_LITERAL(1, 18, 13), // "Damage_signal"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 6) // "Damage"

    },
    "Element_Animation\0Damage_signal\0\0"
    "Damage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Element_Animation[] = {

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

void Element_Animation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Element_Animation *_t = static_cast<Element_Animation *>(_o);
        switch (_id) {
        case 0: _t->Damage_signal((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Element_Animation::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Element_Animation::Damage_signal)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Element_Animation::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Element_Animation.data,
      qt_meta_data_Element_Animation,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Element_Animation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Element_Animation::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Element_Animation.stringdata))
        return static_cast<void*>(const_cast< Element_Animation*>(this));
    return QObject::qt_metacast(_clname);
}

int Element_Animation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Element_Animation::Damage_signal(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_AI_Animation_t {
    QByteArrayData data[8];
    char stringdata[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AI_Animation_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AI_Animation_t qt_meta_stringdata_AI_Animation = {
    {
QT_MOC_LITERAL(0, 0, 12), // "AI_Animation"
QT_MOC_LITERAL(1, 13, 11), // "Move_Signal"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "MapUnit*"
QT_MOC_LITERAL(4, 35, 6), // "target"
QT_MOC_LITERAL(5, 42, 13), // "Attack_Signal"
QT_MOC_LITERAL(6, 56, 8), // "Element*"
QT_MOC_LITERAL(7, 65, 5) // "enemy"

    },
    "AI_Animation\0Move_Signal\0\0MapUnit*\0"
    "target\0Attack_Signal\0Element*\0enemy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AI_Animation[] = {

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
       1,    1,   24,    2, 0x06 /* Public */,
       5,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void AI_Animation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AI_Animation *_t = static_cast<AI_Animation *>(_o);
        switch (_id) {
        case 0: _t->Move_Signal((*reinterpret_cast< MapUnit*(*)>(_a[1]))); break;
        case 1: _t->Attack_Signal((*reinterpret_cast< Element*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MapUnit* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Element* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AI_Animation::*_t)(MapUnit * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AI_Animation::Move_Signal)) {
                *result = 0;
            }
        }
        {
            typedef void (AI_Animation::*_t)(Element * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AI_Animation::Attack_Signal)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject AI_Animation::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AI_Animation.data,
      qt_meta_data_AI_Animation,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AI_Animation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AI_Animation::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AI_Animation.stringdata))
        return static_cast<void*>(const_cast< AI_Animation*>(this));
    return QObject::qt_metacast(_clname);
}

int AI_Animation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void AI_Animation::Move_Signal(MapUnit * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AI_Animation::Attack_Signal(Element * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
