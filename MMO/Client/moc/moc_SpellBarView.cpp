/****************************************************************************
** Meta object code from reading C++ file 'SpellBarView.hh'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/Qt/Views/SpellBarView.hh"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SpellBarView.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SpellBarView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      36,   13,   13,   13, 0x0a,
      58,   13,   13,   13, 0x0a,
      80,   13,   13,   13, 0x0a,
     102,   13,   13,   13, 0x0a,
     124,   13,   13,   13, 0x0a,
     146,   13,   13,   13, 0x0a,
     168,   13,   13,   13, 0x0a,
     190,   13,   13,   13, 0x0a,
     212,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SpellBarView[] = {
    "SpellBarView\0\0on_b_spell1_clicked()\0"
    "on_b_spell2_clicked()\0on_b_spell3_clicked()\0"
    "on_b_spell4_clicked()\0on_b_spell5_clicked()\0"
    "on_b_spell6_clicked()\0on_b_spell7_clicked()\0"
    "on_b_spell8_clicked()\0on_b_spell9_clicked()\0"
    "on_b_spell10_clicked()\0"
};

void SpellBarView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SpellBarView *_t = static_cast<SpellBarView *>(_o);
        switch (_id) {
        case 0: _t->on_b_spell1_clicked(); break;
        case 1: _t->on_b_spell2_clicked(); break;
        case 2: _t->on_b_spell3_clicked(); break;
        case 3: _t->on_b_spell4_clicked(); break;
        case 4: _t->on_b_spell5_clicked(); break;
        case 5: _t->on_b_spell6_clicked(); break;
        case 6: _t->on_b_spell7_clicked(); break;
        case 7: _t->on_b_spell8_clicked(); break;
        case 8: _t->on_b_spell9_clicked(); break;
        case 9: _t->on_b_spell10_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SpellBarView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SpellBarView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SpellBarView,
      qt_meta_data_SpellBarView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SpellBarView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SpellBarView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SpellBarView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SpellBarView))
        return static_cast<void*>(const_cast< SpellBarView*>(this));
    return QWidget::qt_metacast(_clname);
}

int SpellBarView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
