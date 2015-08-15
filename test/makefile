CC := gcc
CFLAG := -g

all: array_feature_test array_effect_test

array_feature_test: array_feature_test.c ../array.h ../array.c
	$(CC) -o array_feature_test array_feature_test.c ../array.c -I ../ $(CFLAG)

array_effect_test: array_effect_test.c ../array.h ../array.c
	$(CC) -o array_effect_test array_effect_test.c ../array.c -I ../ $(CFLAG)

clean:
	rm -fr ./*_test ./*.o ../*.o 2> /dev/null
