CC := gcc
CFLAG := -g

all: array_test

array_test: array_test.c ../array.h ../array.c
	gcc -o array_test array_test.c ../array.c -I ../ $(CFLAG)

clean:
	rm -fr ./*_test ./*.o ../*.o 2> /dev/null
