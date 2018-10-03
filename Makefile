all: libmemtest.so.1.0 test

memtest.o: memtest.c
	gcc -ggdb -Wall -I/usr/include/c++/5 -fPIC -c memtest.c -o memtest.o

libmemtest.so.1.0: memtest.o
	gcc -shared -rdynamic -ldl -Wl,-soname,libmemtest.so.1.0 -o libmemtest.so.1.0 memtest.o
	ln -s ./libmemtest.so.1.0 libmemtest.so

test: main.cpp libmemtest.so.1.0
	g++ -ggdb -L. main.cpp -o test -lmemtest -pthread -rdynamic -ldl
	
clean:
	rm -f *.o libmemtest.*
