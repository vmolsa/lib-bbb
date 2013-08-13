all:
	gcc -Wall -fPIC -c bbb.c	
	gcc -o bbb main.c bbb.o

	ar -rc lib-bbb.a bbb.o
	gcc -shared -Wl,-soname,lib-bbb.so.1 -o lib-bbb.so.1.0 bbb.o

install:
	install -m 0755 ./bbb /usr/local/bin/
	install -m 0644 bbb.h /usr/local/include/
	install -m 0755 lib-bbb.so.1.0 /usr/local/lib/

clean:
	rm -f bbb bbb.o lib-bbb.so.1.0 lib-bbb.a
