#include <gtk/gtk.h>

static void
activate(GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *text;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "GtkEdit");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  text = gtk_text_view_new();
  gtk_container_add(GTK_CONTAINER(window), text);

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