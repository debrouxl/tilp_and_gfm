/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
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

#undef GTK_DISABLE_DEPRECATED
#include <gtk/gtk.h>
#define GTK_DISABLE_DEPRECATED

#include "tilp_core.h"

#include "gstruct.h"
#include "support.h"

struct toolbar_window toolbar_wnd = { 0 };

void toolbar_set_images(void)
{
	GtkToolbar *tb = GTK_TOOLBAR(toolbar_wnd.toolbar);
	GtkToolbarChild *child;
	GtkWidget *old_icon, *new_icon;
	GdkPixbuf *pixbuf;

	//gdk_pixbuf_new_from_xpm_data    (const char **data);
	if (toolbar_wnd.toolbar == NULL)
		return;
		
	child = g_list_nth(tb->children, 0)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_wnd.toolbar, "tb_ready.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 1)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_wnd.toolbar, "tb_calc_screen.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 2)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_wnd.toolbar, "tb_calc_dirlist.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 3)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_wnd.toolbar, "tb_calc_backup.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 4)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_wnd.toolbar, "tb_calc_restore.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 5)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_wnd.toolbar, "tb_calc_send.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 6)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_wnd.toolbar, "tb_mkdir.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 7)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_wnd.toolbar, "tb_trash.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
	
	child = g_list_nth(tb->children, 8)->data;
	old_icon = child->icon;
	new_icon = create_pixmap(toolbar_wnd.toolbar, "tb_refresh.xpm");
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(new_icon));
	gtk_image_set_from_pixbuf(GTK_IMAGE(old_icon), pixbuf);
}

/* Put sensitive some buttons of the toolbar according to some options */
void toolbar_refresh_buttons(void)
{
	CalcFeatures features;

	if (toolbar_wnd.toolbar == NULL)
		return;

	features = ticalcs_calc_features(calc_handle);

	gtk_widget_set_sensitive(toolbar_wnd.button10, features & OPS_ISREADY);
	gtk_widget_set_sensitive(toolbar_wnd.button11, features & OPS_DIRLIST);
	gtk_widget_set_sensitive(toolbar_wnd.button12, features & OPS_BACKUP);
	gtk_widget_set_sensitive(toolbar_wnd.button13, features & OPS_BACKUP);
	gtk_widget_set_sensitive(toolbar_wnd.button14, !(features & FTS_SILENT) || !options.full_gui);

	if(options.full_gui)
		gtk_widget_hide(toolbar_wnd.button15);
	else
		gtk_widget_show(toolbar_wnd.button15);

	/*
	if(options.calc_model == CALC_TI89T_USB || options.calc_model == CALC_TI84P_USB)
	{
		GtkToolbar *tb = GTK_TOOLBAR(toolbar_wnd.toolbar);
		GtkToolItem *item = gtk_toolbar_get_nth_item(tb, 0);
		GtkToolButton *btn = GTK_TOOL_BUTTON(item);
		
		gtk_tool_button_set_label       (btn, "Connect");
	}
	*/
}

// 0: disabled
// 1: send
// 2: receive
void toolbar_set_button(int sr)
{
	/*
	GtkToolbar *tb = GTK_TOOLBAR(toolbar_wnd.toolbar);
	GtkToolItem *item = gtk_toolbar_get_nth_item(tb, 5);
	GtkToolButton *btn = GTK_TOOL_BUTTON(item);
	GtkWidget *icon;

	icon = create_pixmap(toolbar_wnd.toolbar, "tb_refresh.xpm");
	//gtk_tool_button_set_icon_widget((GtkToolButton *)item, icon);
	//gtk_tool_button_set_label       (btn, "foobar");

	if(options.full_gui)
		gtk_widget_set_sensitive(toolbar_wnd.button14, FALSE);
	else
		gtk_widget_set_sensitive(toolbar_wnd.button14, sr);
		*/
}
