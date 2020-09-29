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

#include "debug.h"
#include "app-resources.h"
#include "mainwindow.h"
#include "about.h"


/** \brief  Accelerator data
 *
 * Used to pass accelerator data to the accelerator functions.
 */
typedef struct accel_s {
    const gchar *action;    /**< action name, ie 'app.quit' */
    const gchar *accel;     /**< accelerator, ie '<Primary>Q' */
} accel_t;



/** \brief  App reference
 *
 * \todo    Do we really need this?
 */
GtkApplication *main_app;


/** \brief  Main Windows reference
 *
 * \todo    Do we really need this?
 */
GtkWindow *main_window;


/** \brief  List of accelerators used in the app
 */
static const accel_t main_accels[] = {
    { "app.quit",   "<Primary>Q" },
    { NULL,         NULL }
};


/** \brief  Add accelerators to \a app
 *
 */
static void add_accelerators(GtkApplication *app)
{
    for (int i = 0; main_accels[i].action != NULL; i++) {
        const gchar *temp[2];

        temp[0] = main_accels[i].accel;
        temp[1] = NULL;

        gtk_application_set_accels_for_action(app,
                                              main_accels[i].action,
                                              temp);
    }
}


/** \brief  Action handler for 'About'
 *
 * Opens a dialog/wizard to create a new FPT project.
 *
 * \param[in,out]   action      action
 * \param[in]       paramater   action parameter
 * \param[in]       data        user data
 */
static void on_about(GSimpleAction * action,
                     GVariant *      parameter,
                     gpointer        data)
{
#if 0
    g_print("%s:%d:%s(): Called\n", __FILE__, __LINE__, __func__);
#else

    GtkWidget *dialog;

    fpt_debug("Called!\n");
    dialog = ui_about_dialog_new();
    gtk_window_set_transient_for(main_window, GTK_WINDOW(dialog));
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_widget_show(dialog);

#endif
}



/** \brief  Action handler for 'open project'
 *
 * Opens a dialog/wizard to create a new FPT project
 *
 * \param[in,out]   action      action
 * \param[in]       paramater   action parameter
 * \param[in]       data        user data
 */
static void on_project_open(GSimpleAction * action,
                            GVariant *      parameter,
                            gpointer        data)
{
    g_print("%s:%d:%s(): Called\n", __FILE__, __LINE__, __func__);
}


/** \brief  Action handler for 'Quit'
 *
 * Opens a dialog/wizard to create a new FPT project
 *
 * \param[in,out]   action      action
 * \param[in]       paramater   action parameter
 * \param[in]       data        user data
 */

static void on_app_quit(GSimpleAction *action,
                        GVariant *     parameter,
                        gpointer       data)
{
    GtkWindow *window = main_window;

    fpt_debug("Called!");
    gtk_widget_destroy(GTK_WIDGET(window));
}


/** \brief  Mapping of menu actions to GSimpleActions
 *
 * This might get large, so perhaps later move this into its own file or so.
 */
static GActionEntry app_actions[] = {
    {
        .name = "project_open",
        .activate = on_project_open
    },
    {
        .name = "about",
        .activate = on_about
    },
    {
        .name = "quit",
        .activate = on_app_quit
    }
};




/** \brief  Handler for the 'activate' event of the main application
 *
 * \param[in]   app     main application
 * \param[in]   data    extra event data (unused)
 */
static void on_app_activate(GtkApplication *app,
                            gpointer        data)
{
    GtkBuilder *builder = gtk_builder_new_from_resource(
            "/nl/focus/focus-pixel-tool/app-menu.xml");
    GMenuModel *app_menu = G_MENU_MODEL(gtk_builder_get_object(builder,
                                                               "app-menu"));
    GtkWidget *window;

    gtk_application_set_menubar(app, app_menu);
    g_object_unref(builder);

    window = mainwindow_create(app);
    /* add actions */
    g_action_map_add_action_entries(
            G_ACTION_MAP(app),
            app_actions,
            G_N_ELEMENTS(app_actions),
            window);

    /* add accelerators */
    add_accelerators(app);


    gtk_widget_show_all(window);
    main_window = GTK_WINDOW(window);
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
    main_app = app;

    app_register_resource();
    char **items = g_resources_enumerate_children("/nl/focus/focus-pixel-tool", 0, NULL);
    for (int i = 0; items[i] != NULL; i++) {
        g_print("'%s'\n", items[i]);
    }

    status = g_application_run(G_APPLICATION(app), argc, argv);


    app_unregister_resource();
    return status;
}

