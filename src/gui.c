#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("Hello World\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title (GTK_WINDOW(window), "Hello");
    gtk_window_set_default_size (GTK_WINDOW(window), 200, 200);

    GtkWidget *button = gtk_button_new_with_label("Hello World");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_window_set_child(GTK_WINDOW(window), button);

    gtk_window_present(GTK_WINDOW(window));
}

int gui_run(void) {
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);

    return status;
}