/****************************************************************************
** Meta object code from reading C++ file 'PanelHeadUp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PanelHeadUp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PanelHeadUp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PanelHeadUp_t {
    QByteArrayData data[4];
    char stringdata[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PanelHeadUp_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PanelHeadUp_t qt_meta_stringdata_PanelHeadUp = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PanelHeadUp"
QT_MOC_LITERAL(1, 12, 28), // "ShowMenu_HeadUpToView_Signal"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 26) // "ShowPanelBattleInfo_Signal"

    },
    "PanelHeadUp\0ShowMenu_HeadUpToView_Signal\0"
    "\0ShowPanelBattleInfo_Signal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PanelHeadUp[] = {

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

void PanelHeadUp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PanelHeadUp *_t = static_cast<PanelHeadUp *>(_o);
        switch (_id) {
        case 0: _t->ShowMenu_HeadUpToView_Signal(); break;
        case 1: _t->ShowPanelBattleInfo_Signal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PanelHeadUp::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PanelHeadUp::ShowMenu_HeadUpToView_Signal)) {
                *result = 0;
            }
        }
        {
            typedef void (PanelHeadUp::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PanelHeadUp::ShowPanelBattleInfo_Signal)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PanelHeadUp::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PanelHeadUp.data,
      qt_meta_data_PanelHeadUp,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PanelHeadUp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PanelHeadUp::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PanelHeadUp.stringdata))
        return static_cast<void*>(const_cast< PanelHeadUp*>(this));
    return QFrame::qt_metacast(_clname);
}

int PanelHeadUp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
void PanelHeadUp::ShowMenu_HeadUpToView_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void PanelHeadUp::ShowPanelBattleInfo_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
struct qt_meta_stringdata_Set_Health_Animation_t {
    QByteArrayData data[9];
    char stringdata[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Set_Health_Animation_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Set_Health_Animation_t qt_meta_stringdata_Set_Health_Animation = {
    {
QT_MOC_LITERAL(0, 0, 20), // "Set_Health_Animation"
QT_MOC_LITERAL(1, 21, 21), // "set_health_end_signal"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 8), // "idx_temp"
QT_MOC_LITERAL(4, 53, 2), // "HP"
QT_MOC_LITERAL(5, 56, 6), // "max_HP"
QT_MOC_LITERAL(6, 63, 23), // "set_health_color_signal"
QT_MOC_LITERAL(7, 87, 5), // "color"
QT_MOC_LITERAL(8, 93, 16) // "set_death_signal"

    },
    "Set_Health_Animation\0set_health_end_signal\0"
    "\0idx_temp\0HP\0max_HP\0set_health_color_signal\0"
    "color\0set_death_signal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Set_Health_Animation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   29,    2, 0x06 /* Public */,
       6,    2,   36,    2, 0x06 /* Public */,
       8,    1,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QColor,    3,    7,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void Set_Health_Animation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Set_Health_Animation *_t = static_cast<Set_Health_Animation *>(_o);
        switch (_id) {
        case 0: _t->set_health_end_signal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->set_health_color_signal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 2: _t->set_death_signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Set_Health_Animation::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Set_Health_Animation::set_health_end_signal)) {
                *result = 0;
            }
        }
        {
            typedef void (Set_Health_Animation::*_t)(int , QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Set_Health_Animation::set_health_color_signal)) {
                *result = 1;
            }
        }
        {
            typedef void (Set_Health_Animation::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Set_Health_Animation::set_death_signal)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Set_Health_Animation::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Set_Health_Animation.data,
      qt_meta_data_Set_Health_Animation,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Set_Health_Animation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Set_Health_Animation::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Set_Health_Animation.stringdata))
        return static_cast<void*>(const_cast< Set_Health_Animation*>(this));
    return QObject::qt_metacast(_clname);
}

int Set_Health_Animation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Set_Health_Animation::set_health_end_signal(int _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Set_Health_Animation::set_health_color_signal(int _t1, QColor _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Set_Health_Animation::set_death_signal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
