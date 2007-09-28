#ifndef __SP_KDE_H__
#define __SP_KDE_H__

/*
 * KDE utilities for Sodipodi - adapted to TiEmu
 *
 * Authors:
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *   Kevin Kofler <Kevin@tigcc.ticalc.org>
 *
 * Copyright (C) 2003-2006 Authors
 * $Id$
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include <glib.h>

G_BEGIN_DECLS

void sp_kde_init (int argc, char **argv, const char *appName, const char *programName, const char *version, const char *shortDescription, const char *copyrightStatement, const char *homePageAddress, const char *bugsEmailAddress);
void sp_kde_finish (void);

char *sp_kde_get_open_filename (gchar *dir, gchar *filter, gchar *title);
char **sp_kde_get_open_filenames (gchar *dir, gchar *filter, gchar *title);
char *sp_kde_get_write_filename (gchar *dir, gchar *filter, gchar *title);

char *sp_kde_get_save_filename (unsigned char *dir, unsigned int *spns);

gint sp_kde_process_qt_events(gpointer data);

G_END_DECLS

#endif
