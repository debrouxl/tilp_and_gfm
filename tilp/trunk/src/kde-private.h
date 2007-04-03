#ifndef __SP_KDE_PRIVATE_H__
#define __SP_KDE_PRIVATE_H__

/*
 * KDE utilities for Sodipodi - adapted to TiEmu
 *
 * Authors:
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *   Kevin Kofler <Kevin@tigcc.ticalc.org>
 *
 * Copyright (C) 2003-2005 Authors
 * $Id$
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include <qobject.h>

class SPKDEBridge : public QObject {
	Q_OBJECT
public:
	SPKDEBridge (const char *name) : QObject (NULL, name) { /* NOP */ }

public slots:
	void EventHook (void);
	void TimerHook (void);
};

#endif
