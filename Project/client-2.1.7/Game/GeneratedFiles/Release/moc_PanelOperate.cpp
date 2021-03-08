/****************************************************************************
** Meta object code from reading C++ file 'PanelOperate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PanelOperate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PanelOperate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PanelOperate_t {
    QByteArrayData data[6];
    char stringdata[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PanelOperate_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PanelOperate_t qt_meta_stringdata_PanelOperate = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PanelOperate"
QT_MOC_LITERAL(1, 13, 22), // "btAttackPressed_Signal"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 20), // "btMovePressed_Signal"
QT_MOC_LITERAL(4, 58, 29), // "btUltimateSkillPressed_Signal"
QT_MOC_LITERAL(5, 88, 22) // "btCancelPressed_Signal"

    },
    "PanelOperate\0btAttackPressed_Signal\0"
    "\0btMovePressed_Signal\0"
    "btUltimateSkillPressed_Signal\0"
    "btCancelPressed_Signal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PanelOperate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PanelOperate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PanelOperate *_t = static_cast<PanelOperate *>(_o);
        switch (_id) {
        case 0: _t->btAttackPressed_Signal(); break;
        case 1: _t->btMovePressed_Signal(); break;
        case 2: _t->btUltimateSkillPressed_Signal(); break;
        case 3: _t->btCancelPressed_Signal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PanelOperate::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PanelOperate::btAttackPressed_Signal)) {
                *result = 0;
            }
        }
        {
            typedef void (PanelOperate::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PanelOperate::btMovePressed_Signal)) {
                *result = 1;
            }
        }
        {
            typedef void (PanelOperate::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PanelOperate::btUltimateSkillPressed_Signal)) {
                *result = 2;
            }
        }
        {
            typedef void (PanelOperate::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PanelOperate::btCancelPressed_Signal)) {
                *result = 3;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PanelOperate::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_PanelOperate.data,
      qt_meta_data_PanelOperate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PanelOperate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PanelOperate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PanelOperate.stringdata))
        return static_cast<void*>(const_cast< PanelOperate*>(this));
    return QLabel::qt_metacast(_clname);
}

int PanelOperate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PanelOperate::btAttackPressed_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void PanelOperate::btMovePressed_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void PanelOperate::btUltimateSkillPressed_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void PanelOperate::btCancelPressed_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
