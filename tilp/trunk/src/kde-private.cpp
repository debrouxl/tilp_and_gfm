/****************************************************************************
** SPKDEBridge meta object code from reading C++ file 'kde-private.h'
**
** Created: Tue Apr 3 00:20:18 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "kde-private.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *SPKDEBridge::className() const
{
    return "SPKDEBridge";
}

QMetaObject *SPKDEBridge::metaObj = 0;
static QMetaObjectCleanUp cleanUp_SPKDEBridge( "SPKDEBridge", &SPKDEBridge::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString SPKDEBridge::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SPKDEBridge", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString SPKDEBridge::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SPKDEBridge", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* SPKDEBridge::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUMethod slot_0 = {"EventHook", 0, 0 };
    static const QUMethod slot_1 = {"TimerHook", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "EventHook()", &slot_0, QMetaData::Public },
	{ "TimerHook()", &slot_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"SPKDEBridge", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_SPKDEBridge.setMetaObject( metaObj );
    return metaObj;
}

void* SPKDEBridge::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "SPKDEBridge" ) )
	return this;
    return QObject::qt_cast( clname );
}

bool SPKDEBridge::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: EventHook(); break;
    case 1: TimerHook(); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool SPKDEBridge::qt_emit( int _id, QUObject* _o )
{
    return QObject::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool SPKDEBridge::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool SPKDEBridge::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
