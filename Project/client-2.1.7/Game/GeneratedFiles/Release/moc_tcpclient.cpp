/****************************************************************************
** Meta object code from reading C++ file 'tcpclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tcpclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TcpClient_t {
    QByteArrayData data[11];
    char stringdata[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpClient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpClient_t qt_meta_stringdata_TcpClient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TcpClient"
QT_MOC_LITERAL(1, 10, 9), // "nameError"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "nameTrue"
QT_MOC_LITERAL(4, 30, 8), // "nameList"
QT_MOC_LITERAL(5, 39, 9), // "getInvite"
QT_MOC_LITERAL(6, 49, 9), // "startGame"
QT_MOC_LITERAL(7, 59, 10), // "battleData"
QT_MOC_LITERAL(8, 70, 8), // "gameOver"
QT_MOC_LITERAL(9, 79, 12), // "disconnected"
QT_MOC_LITERAL(10, 92, 12) // "dataReceived"

    },
    "TcpClient\0nameError\0\0nameTrue\0nameList\0"
    "getInvite\0startGame\0battleData\0gameOver\0"
    "disconnected\0dataReceived"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    1,   61,    2, 0x06 /* Public */,
       5,    2,   64,    2, 0x06 /* Public */,
       6,    0,   69,    2, 0x06 /* Public */,
       7,    1,   70,    2, 0x06 /* Public */,
       8,    1,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariantList,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariantMap,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpClient *_t = static_cast<TcpClient *>(_o);
        switch (_id) {
        case 0: _t->nameError(); break;
        case 1: _t->nameTrue(); break;
        case 2: _t->nameList((*reinterpret_cast< QVariantList(*)>(_a[1]))); break;
        case 3: _t->getInvite((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->startGame(); break;
        case 5: _t->battleData((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 6: _t->gameOver((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->disconnected(); break;
        case 8: _t->dataReceived(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TcpClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClient::nameError)) {
                *result = 0;
            }
        }
        {
            typedef void (TcpClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClient::nameTrue)) {
                *result = 1;
            }
        }
        {
            typedef void (TcpClient::*_t)(QVariantList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClient::nameList)) {
                *result = 2;
            }
        }
        {
            typedef void (TcpClient::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClient::getInvite)) {
                *result = 3;
            }
        }
        {
            typedef void (TcpClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClient::startGame)) {
                *result = 4;
            }
        }
        {
            typedef void (TcpClient::*_t)(QVariantMap );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClient::battleData)) {
                *result = 5;
            }
        }
        {
            typedef void (TcpClient::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClient::gameOver)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject TcpClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TcpClient.data,
      qt_meta_data_TcpClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TcpClient.stringdata))
        return static_cast<void*>(const_cast< TcpClient*>(this));
    return QObject::qt_metacast(_clname);
}

int TcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void TcpClient::nameError()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TcpClient::nameTrue()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void TcpClient::nameList(QVariantList _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TcpClient::getInvite(QString _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TcpClient::startGame()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void TcpClient::battleData(QVariantMap _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TcpClient::gameOver(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
