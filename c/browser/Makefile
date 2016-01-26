obj-m := browser.o

all:
	gcc browser.c -o browser `pkg-config --cflags --libs gtk+-2.0 webkit-1.0`

clean:
	rm browser
