/* 
	Компиляция: gcc -o combo combo.c `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
*/

#include <gtk/gtk.h>

void combo_selected(GtkWidget *widget, gpointer main_window) { 
	gchar *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
	gtk_label_set_text(GTK_LABEL(main_window), text);
	g_free(text);
}

int main( int argc, char *argv[]) {
	GtkWidget *main_window;		// Главное окошко
	GtkWidget *main_fixed;		// Фиксированная площадь
	GtkWidget *main_combo;		// Выпадающее меню
	GtkWidget *main_label1;		// Метка

	gtk_init(&argc, &argv);
	
	// Главное окошко
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(main_window), "Drop down menu");
	gtk_window_set_default_size(GTK_WINDOW(main_window), 370, 130);
	gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(main_window), 10);
	
	// Фиксированная площадь
	main_fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(main_window), main_fixed);

	// Выпадающее меню
	main_combo = gtk_combo_box_new_text();
	gtk_combo_box_append_text(GTK_COMBO_BOX(main_combo), "Ubuntu");
	gtk_combo_box_append_text(GTK_COMBO_BOX(main_combo), "Mandriva");
	gtk_combo_box_append_text(GTK_COMBO_BOX(main_combo), "Fedora");
	gtk_combo_box_append_text(GTK_COMBO_BOX(main_combo), "Mint");
	gtk_combo_box_append_text(GTK_COMBO_BOX(main_combo), "Gentoo");
	gtk_combo_box_append_text(GTK_COMBO_BOX(main_combo), "Debian");
	gtk_fixed_put(GTK_FIXED(main_fixed), main_combo, 50, 10);
	
	// Метка где будет отображаться выбор
	main_label1 = gtk_label_new("-");
	gtk_fixed_put(GTK_FIXED(main_fixed), main_label1, 200, 10);
	
	// Общие сигналы
	g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // Нажат крестик выхода из апликации

	// Смена выбора
	g_signal_connect(G_OBJECT(main_combo), "changed", G_CALLBACK(combo_selected), (gpointer)main_label1);
	
	gtk_widget_show_all(main_window);
	gtk_main();
	
	return 0;
}
