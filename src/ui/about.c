/* vim: set et ts=4 sw=4 sts=4 fdm=marker syntax=c.doxygen: */

/** \file   about.c
 * \brief   About dialog
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

#include "config.h"
#include "debug.h"

#include "about.h"


/** \brief  Create the application's About dialog
 *
 * \return  GtkDialog
 */
GtkWidget *ui_about_dialog_new(void)
{
    GtkWidget *dialog;

    dialog = gtk_about_dialog_new();

    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), FPT_PRG_NAME);
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), FPT_PRG_VERSION);

    return dialog;
}

