/* vim: set et ts=4 sw=4 sts=4 fdm=marker syntax=c.doxygen: */

/** \file   mainwindow.c
 * \brief   Main application window
 *
 * \author  Bas Wassink <b.wassink@ziggo.nl>
 */

/*
    Focus Pixel Tool
    Copyright (C) 2020  Bas Wassink

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    This General Public License does not permit incorporating your program into
    proprietary programs.  If your program is a subroutine library, you may
    consider it more useful to permit linking proprietary applications with the
    library.  If this is what you want to do, use the GNU Lesser General
    Public License instead of this License.
*/


#include <gtk/gtk.h>

#include "mainwindow.h"


/** \brief  Create main window and hoop up event handlers
 *
 * \param[in,out]   app     GApplication refererence
 *
 * \return  Main Window
 */
GtkWidget *mainwindow_create(GtkApplication *app)
{
    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    gtk_window_set_title(GTK_WINDOW(window), "Focus Pixel Tool");

    return window;
}
