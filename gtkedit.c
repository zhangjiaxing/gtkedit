#include <gtk/gtk.h>


static void
on_exit_menu_active(GtkMenuItem *menuitem, gpointer app)
{
    g_application_quit(app);
}

static void
set_menubar(GtkWidget *window, gpointer app)
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
    gtk_box_pack_start(GTK_BOX(window), menubar, FALSE, FALSE, 0);
}

static void
activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *vbox;

    GtkWidget *text;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEdit");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // text = gtk_text_view_new();
    // gtk_container_add(GTK_CONTAINER(window), text);
    
    set_menubar(vbox, app);
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
