/****************************************************************************
** Meta object code from reading C++ file 'v_mainrelation.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../plurinotes/views/v_mainrelation.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'v_mainrelation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_V_MainView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      44,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_V_MainView[] = {
    "V_MainView\0\0refreshCouple(QListWidgetItem*)\0"
    "afficheCouple(QListWidgetItem*)\0"
};

void V_MainView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        V_MainView *_t = static_cast<V_MainView *>(_o);
        switch (_id) {
        case 0: _t->refreshCouple((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->afficheCouple((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData V_MainView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject V_MainView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_V_MainView,
      qt_meta_data_V_MainView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &V_MainView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *V_MainView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *V_MainView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_V_MainView))
        return static_cast<void*>(const_cast< V_MainView*>(this));
    return QWidget::qt_metacast(_clname);
}

int V_MainView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
