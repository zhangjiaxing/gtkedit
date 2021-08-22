#include <gtk/gtk.h>

static void
on_exit_menu_active(GtkMenuItem *menuitem, gpointer app)
{
    g_application_quit(app);
}

static void
on_open_menu_active(GtkMenuItem *menuitem, gpointer window)
{
    g_message("openfile xxxxxx");
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Open File",
                                         GTK_WINDOW(window),
                                         action,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "_Open",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        g_message(filename);

        // open_file(filename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

static GtkWidget *
init_menubar(GtkWidget *window, GtkWidget *text_view, gpointer app)
{
    GtkWidget *menubar;
    GtkWidget *menu_file_root;
    GtkWidget *menu_file;
    GtkWidget *menu_item_open;
    GtkWidget *menu_item_save;
    GtkWidget *menu_item_save_as;
    GtkWidget *menu_item_exit;

    menu_file = gtk_menu_new();
    menu_item_open = gtk_menu_item_new_with_label("Open File...");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_file), menu_item_open);
    g_signal_connect(G_OBJECT(menu_item_open), "activate", G_CALLBACK(on_open_menu_active), window);

    menu_item_save = gtk_menu_item_new_with_label("Save");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_file), menu_item_save);

    menu_item_save_as = gtk_menu_item_new_with_label("Save As...");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_file), menu_item_save_as);

    menu_item_exit = gtk_menu_item_new_with_label("Exit");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_file), menu_item_exit);
    g_signal_connect(G_OBJECT(menu_item_exit), "activate", G_CALLBACK(on_exit_menu_active), app);

    menu_file_root = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_file_root), menu_file);

    menubar = gtk_menu_bar_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_file_root);

    return menubar;
}

static void
activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEdit");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);

    GtkWidget *menubar = init_menubar(window, text_view, app);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    GtkWidget *sw = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), GTK_POLICY_EXTERNAL, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(sw), text_view);

    gtk_box_pack_start(GTK_BOX(vbox), sw, TRUE, TRUE, 0);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.gtkedit", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
