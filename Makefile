all:
	gcc -fPIC -c bbb.c	
	gcc -o bbb main.c bbb.o

	ar -rc lib-bbb.a bbb.o
	gcc -shared -o lib-bbb.so bbb.o

install:
	install -m 0755 ./bbb /usr/local/bin/
	install -m 0644 bbb.h /usr/local/include/
	install -m 0755 lib-bbb.so /usr/local/lib/

clean:
	rm -f bbb bbb.o lib-bbb.so lib-bbb.a
