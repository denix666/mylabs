/* To compile: gcc -o win win.c `pkg-config --libs --cflags gtk+-2.0` */

#include <gtk/gtk.h>

void show_about(GtkWidget *widget, gpointer data){
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("/usr/share/pixmaps/fedora-logo.png", NULL);
	
	GtkWidget *dialog = gtk_about_dialog_new();
	
	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "Моя программка");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "0.1"); 
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "(c) Denis Salmanovich");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "Моя первая программка на GTK+.");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "http://os.vc");

	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
	g_object_unref(pixbuf), pixbuf = NULL;

	gtk_dialog_run(GTK_DIALOG (dialog));
	gtk_widget_destroy(dialog);
}

int main( int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *fixed;
	GtkWidget *button;
	
	GtkWidget *about;
	
	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "MyTitle");
	gtk_window_set_default_size(GTK_WINDOW(window), 330, 250);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);
  
	button = gtk_button_new_with_label("Quit");
	gtk_fixed_put(GTK_FIXED(fixed), button, 50, 50);
	gtk_widget_set_size_request(button, 80, 35);
    
    GdkColor color;
    gdk_color_parse ("red", &color);
    gtk_widget_modify_bg (GTK_WIDGET(button), GTK_STATE_NORMAL, &color);
    
    about = gtk_button_new_with_label("About");
    gtk_fixed_put(GTK_FIXED(fixed), about, 150, 50);
	gtk_widget_set_size_request(about, 80, 35);
    
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), G_OBJECT(window));
	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(about), "button-press-event", G_CALLBACK(show_about), (gpointer) window);
  
	gtk_widget_show_all(window);
	
	gtk_main();
	
	return 0;
}
