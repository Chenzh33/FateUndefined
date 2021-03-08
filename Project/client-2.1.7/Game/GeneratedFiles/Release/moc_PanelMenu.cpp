/****************************************************************************
** Meta object code from reading C++ file 'PanelMenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PanelMenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PanelMenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PanelMenu_t {
    QByteArrayData data[21];
    char stringdata[299];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PanelMenu_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PanelMenu_t qt_meta_stringdata_PanelMenu = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PanelMenu"
QT_MOC_LITERAL(1, 10, 16), // "GameStart_Signal"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 16), // "multiplay_Signal"
QT_MOC_LITERAL(4, 45, 14), // "AILevel_Signal"
QT_MOC_LITERAL(5, 60, 7), // "ailevel"
QT_MOC_LITERAL(6, 68, 23), // "ReturnToPageMultiplayer"
QT_MOC_LITERAL(7, 92, 16), // "ReturnToMainMenu"
QT_MOC_LITERAL(8, 109, 9), // "nameError"
QT_MOC_LITERAL(9, 119, 8), // "nameTrue"
QT_MOC_LITERAL(10, 128, 8), // "nameList"
QT_MOC_LITERAL(11, 137, 9), // "getInvite"
QT_MOC_LITERAL(12, 147, 13), // "ConfirmInvite"
QT_MOC_LITERAL(13, 161, 21), // "SinglePlayerGameStart"
QT_MOC_LITERAL(14, 183, 14), // "ConfirmConnect"
QT_MOC_LITERAL(15, 198, 11), // "changeEnemy"
QT_MOC_LITERAL(16, 210, 12), // "getHttpReply"
QT_MOC_LITERAL(17, 223, 14), // "QNetworkReply*"
QT_MOC_LITERAL(18, 238, 27), // "ChangeBackgroundMusicVolume"
QT_MOC_LITERAL(19, 266, 18), // "ChangeEffectVolume"
QT_MOC_LITERAL(20, 285, 13) // "SetCurrentMap"

    },
    "PanelMenu\0GameStart_Signal\0\0"
    "multiplay_Signal\0AILevel_Signal\0ailevel\0"
    "ReturnToPageMultiplayer\0ReturnToMainMenu\0"
    "nameError\0nameTrue\0nameList\0getInvite\0"
    "ConfirmInvite\0SinglePlayerGameStart\0"
    "ConfirmConnect\0changeEnemy\0getHttpReply\0"
    "QNetworkReply*\0ChangeBackgroundMusicVolume\0"
    "ChangeEffectVolume\0SetCurrentMap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PanelMenu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,
       4,    1,  101,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  104,    2, 0x0a /* Public */,
       7,    0,  105,    2, 0x0a /* Public */,
       8,    0,  106,    2, 0x0a /* Public */,
       9,    0,  107,    2, 0x0a /* Public */,
      10,    1,  108,    2, 0x0a /* Public */,
      11,    2,  111,    2, 0x0a /* Public */,
      12,    0,  116,    2, 0x0a /* Public */,
      13,    0,  117,    2, 0x0a /* Public */,
      14,    0,  118,    2, 0x0a /* Public */,
      15,    1,  119,    2, 0x0a /* Public */,
      16,    1,  122,    2, 0x0a /* Public */,
      18,    1,  125,    2, 0x0a /* Public */,
      19,    1,  128,    2, 0x0a /* Public */,
      20,    1,  131,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariantList,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void PanelMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PanelMenu *_t = static_cast<PanelMenu *>(_o);
        switch (_id) {
        case 0: _t->GameStart_Signal(); break;
        case 1: _t->multiplay_Signal(); break;
        case 2: _t->AILevel_Signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->ReturnToPageMultiplayer(); break;
        case 4: _t->ReturnToMainMenu(); break;
        case 5: _t->nameError(); break;
        case 6: _t->nameTrue(); break;
        case 7: _t->nameList((*reinterpret_cast< QVariantList(*)>(_a[1]))); break;
        case 8: _t->getInvite((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->ConfirmInvite(); break;
        case 10: _t->SinglePlayerGameStart(); break;
        case 11: _t->ConfirmConnect(); break;
        case 12: _t->changeEnemy((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->getHttpReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 14: _t->ChangeBackgroundMusicVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->ChangeEffectVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->SetCurrentMap((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PanelMenu::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PanelMenu::GameStart_Signal)) {
                *result = 0;
            }
        }
        {
            typedef void (PanelMenu::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PanelMenu::multiplay_Signal)) {
                *result = 1;
            }
        }
        {
            typedef void (PanelMenu::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PanelMenu::AILevel_Signal)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject PanelMenu::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PanelMenu.data,
      qt_meta_data_PanelMenu,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PanelMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PanelMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PanelMenu.stringdata))
        return static_cast<void*>(const_cast< PanelMenu*>(this));
    return QFrame::qt_metacast(_clname);
}

int PanelMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void PanelMenu::GameStart_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void PanelMenu::multiplay_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void PanelMenu::AILevel_Signal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
