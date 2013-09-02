CFLAGS=-g -Wall -O0 -std=gnu99

SOURCES=malloc.h malloc.c test_malloc.c

HEADERS=malloc.h
LIBRARIES=malloc.so

main: malloc.c
	gcc $(CFLAGS) -c -lm malloc.c -o malloc.o
	ar ruv libmalloc.a malloc.o
	ranlib libmalloc.a

test:
	gcc $(CFLAGS) -c malloc.c -o -libmalloc.so
	gcc $(CFLAGS) -L`pwd` -lmalloc test_malloc.c -o test_malloc
