memtest.o:
	gcc -Wall -fPIC -c memtest.c -o memtest.o

libmemtest.so.1.0: memtest.o
	gcc -shared -Wl,-soname,libmemtest.so.1.0 -o libmemtest.so.1.0 memtest.o
	ln -s ./libmemtest.so.1.0 libmemtest.so

test: libmemtest.so.1.0
	g++ -L. main.cpp -o test -lmemtest

all: libmemtest.so.1.0 test
	
clean:
	rm -f *.o libmemtest.*
