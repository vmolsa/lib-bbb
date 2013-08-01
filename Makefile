all:
	gcc -fPIC -c bbb.c	
	gcc -o bbb main.c bbb.o

	ar -rc lib-bbb.a bbb.o
	gcc -shared -o lib-bbb.so bbb.o

clean:
	rm -f bbb bbb.o lib-bbb.so lib-bbb.a
