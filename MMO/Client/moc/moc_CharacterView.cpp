/****************************************************************************
** Meta object code from reading C++ file 'CharacterView.hh'
**
** Created: Wed Feb 19 14:01:59 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/Qt/Views/CharacterView.hh"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CharacterView.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CharacterView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      32,   14,   14,   14, 0x08,
      49,   14,   14,   14, 0x08,
      69,   14,   14,   14, 0x08,
      88,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CharacterView[] = {
    "CharacterView\0\0b_prev_clicked()\0"
    "b_next_clicked()\0on_b_back_clicked()\0"
    "on_b_new_clicked()\0on_b_play_clicked()\0"
};

void CharacterView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CharacterView *_t = static_cast<CharacterView *>(_o);
        switch (_id) {
        case 0: _t->b_prev_clicked(); break;
        case 1: _t->b_next_clicked(); break;
        case 2: _t->on_b_back_clicked(); break;
        case 3: _t->on_b_new_clicked(); break;
        case 4: _t->on_b_play_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CharacterView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CharacterView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CharacterView,
      qt_meta_data_CharacterView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CharacterView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CharacterView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CharacterView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CharacterView))
        return static_cast<void*>(const_cast< CharacterView*>(this));
    return QWidget::qt_metacast(_clname);
}

int CharacterView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
