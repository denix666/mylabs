/* 
	Автор: Denis Salmanovich
	
	Данная программа написана для изучения основ программирования на языке C
	
	Для корректной работы программы должны быть установлены следующие пакеты:
	GeoIP, gtk3-devel, xclip
	
	Компиляция: gcc -o geo_lookup geo_lookup.c `pkg-config --libs --cflags gtk+-3.0`
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

void get_geo_location(GtkWidget *widget, gpointer data) {
	char cmd[100];
	
	// Восстановление переданных данных о виджетах
	gpointer *dataForButton = (gpointer*)data;
	
	GtkWidget *main_entry1 = (GtkWidget*)dataForButton[0];
	GtkWidget *main_label2 = (GtkWidget*)dataForButton[1];
	
	
	// Выполняем команду и записываем результат в файл
	sprintf(cmd, "geoiplookup '%s' | awk -F\": \" '{print $2}' >/tmp/iplookup",gtk_entry_get_text(GTK_ENTRY(main_entry1)));
	system(cmd);
	
	// Считываем полученный результат команды из файла
	char buf[256];
	FILE *myFile = fopen("/tmp/iplookup","r");
	fgets(buf, 60, myFile);
	fclose(myFile);
	
	// Подтираем за собой
	system("rm -rf /tmp/iplookup");
	
	// Выводим результат в метку
	gtk_label_set_text(GTK_LABEL(main_label2), buf);
}

void clear_entry(GtkWidget *widget, gpointer data) {
	// Восстановление переданных данных о виджетах
	gpointer *dataForButton = (gpointer*)data;
	
	GtkWidget *main_entry1 = (GtkWidget*)dataForButton[0];
	GtkWidget *main_label2 = (GtkWidget*)dataForButton[1];
	
	gtk_label_set_text(GTK_LABEL(main_label2), "");
	gtk_entry_set_text(GTK_ENTRY(main_entry1), "");
}

void get_from_clipboard(GtkWidget *widget, gpointer main_entry1) {
	// Очищаем окошко (чтоб данные из него не попали в буфер обмена)
	gtk_entry_set_text(GTK_ENTRY(main_entry1), "");
	
	// Вызываем команду передачи содержимого буфера обмена в файл
	system("xclip -o >/tmp/clip");
	
	// Считываем полученный результат команды из файла
	char buf[256];
	FILE *myFile = fopen("/tmp/clip","r");
	fgets(buf, 60, myFile);
	fclose(myFile);
	
	// Подтираем за собой
	system("rm -rf /tmp/clip");
	
	// Выводим результат в окошко ввода
	gtk_entry_set_text(GTK_ENTRY(main_entry1), buf);
}

static gboolean check_key(GtkWidget *widget, GdkEventKey *event) {
	// Если нажат 'Esc' - закрыть приложение
	if (event->keyval == GDK_KEY_Escape) {
		gtk_main_quit();
		return TRUE;
	}
	
	// Если нажать 'ENTER' должна вызываться функция get_geo_location, но как ее правильно вызвать, пока что ниасилил.
	if (event->keyval == GDK_KEY_Return) {
		return TRUE;
	}
	return FALSE;
}

int main( int argc, char *argv[]) {
	GtkWidget *main_window;		// Главное окошко
	GtkWidget *main_fixed;		// Фиксированная площадь
	GtkWidget *main_label1;		// Метка
	GtkWidget *main_label2;		// Метка вывода локации
	GtkWidget *main_entry1;		// Ввод адреса
	GtkWidget *main_button1;	// GEO Lookup
	GtkWidget *main_button2;	// Exit
	GtkWidget *main_button3;	// Clear
	GtkWidget *main_button4;	// Get IP from clipboard
	GtkWidget *main_frame1;		// Фрэйм для вывода локации

	gtk_init(&argc, &argv);
	
	// Главное окошко
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(main_window), "GEO Lookup by -=DeN=-");
	gtk_window_set_default_size(GTK_WINDOW(main_window), 370, 130);
	gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(main_window), 10);
	
	// Фиксированная площадь
	main_fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(main_window), main_fixed);
	
	// Метка
	main_label1 = gtk_label_new("Ресурс:");
	gtk_fixed_put(GTK_FIXED(main_fixed), main_label1, 5, 10); 
	
	// Ввод IP адреса
	main_entry1 = gtk_entry_new();
	gtk_fixed_put(GTK_FIXED(main_fixed), main_entry1, 100, 7);
	gtk_entry_set_text(GTK_ENTRY(main_entry1), "");
	gtk_widget_set_tooltip_text(main_entry1, "Введите IP адрес или hostname");
	
	// Кнопка вывода локации
	main_button1 = gtk_button_new_with_label("Найти!");
	gtk_widget_set_size_request(main_button1, 90, 15);
	gtk_fixed_put(GTK_FIXED(main_fixed), main_button1, 270, 6);

	// Фрэйм для вывода локации
	main_frame1 = gtk_frame_new("Местонахождение:");
	gtk_frame_set_shadow_type(GTK_FRAME(main_frame1), GTK_SHADOW_ETCHED_IN);
	gtk_widget_set_size_request(main_frame1, 360, 50);
	gtk_fixed_put(GTK_FIXED(main_fixed), main_frame1, 2, 40);
	
	// Метка вывода локации
	main_label2 = gtk_label_new(NULL);
	gtk_label_set_justify(GTK_LABEL(main_label2), GTK_JUSTIFY_CENTER);
	gtk_widget_set_size_request(main_label2, 345, 15);
	gtk_fixed_put(GTK_FIXED(main_fixed), main_label2, 10, 70);
	
	// Кнопка выхода
	main_button2 = gtk_button_new_with_label("Выход");
	gtk_widget_set_size_request(main_button2, 90, 15);
	gtk_fixed_put(GTK_FIXED(main_fixed), main_button2, 270, 110);
	
	// Кнопка Clear
	main_button3 = gtk_button_new_with_label("Очистить");
	gtk_widget_set_size_request(main_button3, 90, 15);
	gtk_fixed_put(GTK_FIXED(main_fixed), main_button3, 170, 110);
	
	// Кнопка Get IP from clipboard
	main_button4 = gtk_button_new_with_label("Вставить из буфера");
	gtk_widget_set_size_request(main_button4, 150, 15);
	gtk_fixed_put(GTK_FIXED(main_fixed), main_button4, 6, 110);
	
	// Общие сигналы
	g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // Нажат крестик выхода из апликации
	g_signal_connect(main_button2, "clicked", G_CALLBACK(gtk_main_quit), G_OBJECT(main_window)); // Нажата кнопка "Выход"
	g_signal_connect(main_button4, "clicked", G_CALLBACK(get_from_clipboard),(gpointer)main_entry1); // Нажата кнопка "Get IP from clipboard"
		
	// Сигнал и передача более одного аргумента
	gpointer dataForButton[2];
	dataForButton[0] = (gpointer)main_entry1;
	dataForButton[1] = (gpointer)main_label2;
	g_signal_connect(main_button1, "clicked", G_CALLBACK(get_geo_location), (gpointer)dataForButton); // Нажата кнопка GEO Lookup
	g_signal_connect(main_button3, "clicked", G_CALLBACK(clear_entry),(gpointer)dataForButton); // Нажата кнопка Clear
	
	// Обработка сигналов нажатия клавиш
	g_signal_connect(main_window, "key_press_event", G_CALLBACK(check_key), (gpointer)dataForButton);
	
	gtk_widget_show_all(main_window);
	gtk_main();
	
	return 0;
}
