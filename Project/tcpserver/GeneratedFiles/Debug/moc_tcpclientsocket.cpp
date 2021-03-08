/****************************************************************************
** Meta object code from reading C++ file 'tcpclientsocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tcpclientsocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpclientsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TcpClientSocket_t {
    QByteArrayData data[14];
    char stringdata[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpClientSocket_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpClientSocket_t qt_meta_stringdata_TcpClientSocket = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TcpClientSocket"
QT_MOC_LITERAL(1, 16, 8), // "nameList"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "TcpClientSocket*"
QT_MOC_LITERAL(4, 43, 4), // "chat"
QT_MOC_LITERAL(5, 48, 9), // "findVital"
QT_MOC_LITERAL(6, 58, 5), // "start"
QT_MOC_LITERAL(7, 64, 6), // "battle"
QT_MOC_LITERAL(8, 71, 8), // "sendName"
QT_MOC_LITERAL(9, 80, 12), // "disconnected"
QT_MOC_LITERAL(10, 93, 9), // "messageon"
QT_MOC_LITERAL(11, 103, 4), // "lose"
QT_MOC_LITERAL(12, 108, 12), // "dataReceived"
QT_MOC_LITERAL(13, 121, 16) // "slotDisconnected"

    },
    "TcpClientSocket\0nameList\0\0TcpClientSocket*\0"
    "chat\0findVital\0start\0battle\0sendName\0"
    "disconnected\0messageon\0lose\0dataReceived\0"
    "slotDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpClientSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       5,    3,   75,    2, 0x06 /* Public */,
       6,    2,   82,    2, 0x06 /* Public */,
       7,    2,   87,    2, 0x06 /* Public */,
       8,    2,   92,    2, 0x06 /* Public */,
       9,    1,   97,    2, 0x06 /* Public */,
      10,    1,  100,    2, 0x06 /* Public */,
      11,    2,  103,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,  108,    2, 0x0a /* Public */,
      13,    0,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QVariantMap,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::QVariantMap, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QVariantMap, 0x80000000 | 3,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TcpClientSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpClientSocket *_t = static_cast<TcpClientSocket *>(_o);
        switch (_id) {
        case 0: _t->nameList((*reinterpret_cast< TcpClientSocket*(*)>(_a[1]))); break;
        case 1: _t->chat((*reinterpret_cast< const QVariantMap(*)>(_a[1]))); break;
        case 2: _t->findVital((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 3: _t->start((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< TcpClientSocket*(*)>(_a[2]))); break;
        case 4: _t->battle((*reinterpret_cast< const QVariantMap(*)>(_a[1])),(*reinterpret_cast< TcpClientSocket*(*)>(_a[2]))); break;
        case 5: _t->sendName((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< TcpClientSocket*(*)>(_a[2]))); break;
        case 6: _t->disconnected((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 7: _t->messageon((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->lose((*reinterpret_cast< const QVariantMap(*)>(_a[1])),(*reinterpret_cast< TcpClientSocket*(*)>(_a[2]))); break;
        case 9: _t->dataReceived(); break;
        case 10: _t->slotDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TcpClientSocket* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TcpClientSocket* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TcpClientSocket* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TcpClientSocket* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TcpClientSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TcpClientSocket::*_t)(TcpClientSocket * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::nameList)) {
                *result = 0;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(const QVariantMap & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::chat)) {
                *result = 1;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(const QString & , const QString & , const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::findVital)) {
                *result = 2;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(const QString & , TcpClientSocket * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::start)) {
                *result = 3;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(const QVariantMap & , TcpClientSocket * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::battle)) {
                *result = 4;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(const QString & , TcpClientSocket * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::sendName)) {
                *result = 5;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::disconnected)) {
                *result = 6;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::messageon)) {
                *result = 7;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(const QVariantMap & , TcpClientSocket * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::lose)) {
                *result = 8;
            }
        }
    }
}

const QMetaObject TcpClientSocket::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_TcpClientSocket.data,
      qt_meta_data_TcpClientSocket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TcpClientSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpClientSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TcpClientSocket.stringdata))
        return static_cast<void*>(const_cast< TcpClientSocket*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int TcpClientSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void TcpClientSocket::nameList(TcpClientSocket * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpClientSocket::chat(const QVariantMap & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TcpClientSocket::findVital(const QString & _t1, const QString & _t2, const int & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TcpClientSocket::start(const QString & _t1, TcpClientSocket * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TcpClientSocket::battle(const QVariantMap & _t1, TcpClientSocket * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TcpClientSocket::sendName(const QString & _t1, TcpClientSocket * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TcpClientSocket::disconnected(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void TcpClientSocket::messageon(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void TcpClientSocket::lose(const QVariantMap & _t1, TcpClientSocket * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
