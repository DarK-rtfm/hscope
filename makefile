CC=gcc
LINKS=-lcurl -lnotify
HEADERS=-I/usr/include/glib-2.0/ -I/usr/lib/glib-2.0/include -I/usr/include/gdk-pixbuf-2.0/

build:
	$(CC) -o hscope main.c lib/response.c lib/parse.c lib/scope.c $(LINKS) $(HEADERS)