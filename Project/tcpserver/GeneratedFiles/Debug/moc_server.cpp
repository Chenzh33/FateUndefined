/****************************************************************************
** Meta object code from reading C++ file 'server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Server_t {
    QByteArrayData data[13];
    char stringdata[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Server_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Server_t qt_meta_stringdata_Server = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Server"
QT_MOC_LITERAL(1, 7, 12), // "updateServer"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 16), // "slotDisconnected"
QT_MOC_LITERAL(4, 38, 8), // "nameList"
QT_MOC_LITERAL(5, 47, 16), // "TcpClientSocket*"
QT_MOC_LITERAL(6, 64, 4), // "chat"
QT_MOC_LITERAL(7, 69, 9), // "findVital"
QT_MOC_LITERAL(8, 79, 5), // "start"
QT_MOC_LITERAL(9, 85, 6), // "battle"
QT_MOC_LITERAL(10, 92, 8), // "sendName"
QT_MOC_LITERAL(11, 101, 4), // "lose"
QT_MOC_LITERAL(12, 106, 9) // "messageon"

    },
    "Server\0updateServer\0\0slotDisconnected\0"
    "nameList\0TcpClientSocket*\0chat\0findVital\0"
    "start\0battle\0sendName\0lose\0messageon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Server[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   67,    2, 0x0a /* Public */,
       4,    1,   70,    2, 0x0a /* Public */,
       6,    1,   73,    2, 0x0a /* Public */,
       7,    3,   76,    2, 0x0a /* Public */,
       8,    2,   83,    2, 0x0a /* Public */,
       9,    2,   88,    2, 0x0a /* Public */,
      10,    2,   93,    2, 0x0a /* Public */,
      11,    2,   98,    2, 0x0a /* Public */,
      12,    1,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::QVariantMap,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 5,    2,    2,
    QMetaType::Void, QMetaType::QVariantMap, 0x80000000 | 5,    2,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 5,    2,    2,
    QMetaType::Void, QMetaType::QVariantMap, 0x80000000 | 5,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void Server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Server *_t = static_cast<Server *>(_o);
        switch (_id) {
        case 0: _t->updateServer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->slotDisconnected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->nameList((*reinterpret_cast< TcpClientSocket*(*)>(_a[1]))); break;
        case 3: _t->chat((*reinterpret_cast< const QVariantMap(*)>(_a[1]))); break;
        case 4: _t->findVital((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 5: _t->start((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< TcpClientSocket*(*)>(_a[2]))); break;
        case 6: _t->battle((*reinterpret_cast< const QVariantMap(*)>(_a[1])),(*reinterpret_cast< TcpClientSocket*(*)>(_a[2]))); break;
        case 7: _t->sendName((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< TcpClientSocket*(*)>(_a[2]))); break;
        case 8: _t->lose((*reinterpret_cast< const QVariantMap(*)>(_a[1])),(*reinterpret_cast< TcpClientSocket*(*)>(_a[2]))); break;
        case 9: _t->messageon((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
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
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TcpClientSocket* >(); break;
            }
            break;
        case 7:
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
            typedef void (Server::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Server::updateServer)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Server::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_Server.data,
      qt_meta_data_Server,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Server::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Server.stringdata))
        return static_cast<void*>(const_cast< Server*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int Server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Server::updateServer(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
