/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  tilp - Ti Linking Program
 *  Copyright (C) 1999-2004  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <gtk/gtk.h>

#include "tilp_core.h"

#include "gstruct.h"
#include "support.h"

struct toolbar_window toolbar_win = { 0 };

#define GTK_DISABLE_DEPRECATED

void toolbar_set_images(void)
{
	GtkToolbar *tb = GTK_TOOLBAR(toolbar_win.toolbar);
	GtkToolbarChild *child;
	GtkWidget *old_icon, *new_icon;
	GdkPixbuf *pixbuf;

	//gdk_pixbuf_new_from_xpm_data    (const char **data);
	if (toolbar_win.toolbar == NULL)
		return;
		
	child = g_list_nth(tb->children, 0)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_win.toolbar, "tb_ready.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 1)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_win.toolbar, "tb_calc_screen.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 2)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_win.toolbar, "tb_calc_dirlist.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 3)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_win.toolbar, "tb_calc_backup.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 4)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_win.toolbar, "tb_calc_restore.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 5)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_win.toolbar, "tb_calc_send.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 6)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_win.toolbar, "tb_mkdir.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 7)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_win.toolbar, "tb_trash.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 8)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_win.toolbar, "tb_refresh.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
}

#undef GTK_DISABLE_DEPRECATED


/* Put sensitive some buttons of the toolbar according to some options */
void toolbar_refresh_buttons(void)
{
	if (toolbar_win.toolbar == NULL)
		return;

	/* Enable or disable some buttons */
	gtk_widget_set_sensitive(toolbar_win.button10, (ti_calc.supported_operations() & OPS_ISREADY));
	gtk_widget_set_sensitive(toolbar_win.button11, (ti_calc.supported_operations() & OPS_DIRLIST));
	gtk_widget_set_sensitive(toolbar_win.button12, (ti_calc.supported_operations() & OPS_RECV_BACKUP));
	gtk_widget_set_sensitive(toolbar_win.button13, (ti_calc.supported_operations() & OPS_SEND_BACKUP));
	gtk_widget_set_sensitive(toolbar_win.button14, !ti_calc.is_silent);
}
