/* vim: set et ts=4 sw=4 sts=4 fdm=marker syntax=c.doxygen: */

/** \file   main.c
 * \brief   Main program driver
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

#include "app-resources.h"
#include "mainwindow.h"


/** \brief  Handler for the 'activate' event of the main application
 *
 * \param[in]   app     main application
 * \param[in]   data    extra event data (unused)
 */
static void on_app_activate(GtkApplication *app,
                        gpointer        data)
{
    GtkWidget *window;

    window = mainwindow_create(app);
    gtk_widget_show_all(window);
}


/** \brief  Main entry point
 *
 * \param[in]   argc    argument count
 * \param[in]   argv    argument vector
 *
 * \return  exit status
 */
int main(int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new(
            "nl.focus.pixeltool",
            G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);


    app_register_resource();
    char **items = g_resources_enumerate_children("/nl/focus/focus-pixel-tool", 0, NULL);
    for (int i = 0; items[i] != NULL; i++) {
        g_print("'%s'\n", items[i]);
    }

    status = g_application_run(G_APPLICATION(app), argc, argv);


    app_unregister_resource();
    return status;
}

