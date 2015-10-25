CC := gcc
CFLAG := -I ../ -L ../ -g

VPATH=./:../ 

all: array_feature_test array_effect_test \
     list_feature_test\
	 priority_queue_feature_test\
	 deque_feature_test\
	 queue_feature_test\
	 stack_feature_test

array_feature_test: array_feature_test.c array.h array.c
	$(CC) -o array_feature_test array_feature_test.c ../array.c $(CFLAG)

array_effect_test: array_effect_test.c array.h array.c
	$(CC) -o array_effect_test array_effect_test.c ../array.c $(CFLAG)

list_feature_test: list_feature_test.c list.h list.c
	$(CC) -o list_feature_test list_feature_test.c ../list.c $(CFLAG)

priority_queue_feature_test: priority_queue_feature_test.c priority_queue.h priority_queue.c
	$(CC) -o priority_queue_feature_test priority_queue_feature_test.c ../priority_queue.c $(CFLAG)

deque_feature_test: deque_feature_test.c deque.h deque.c list.h list.c
	$(CC) -o deque_feature_test deque_feature_test.c ../list.c ../deque.c $(CFLAG)

queue_feature_test: queue_feature_test.c deque.h deque.c list.h list.c queue.h queue.c
	$(CC) -o queue_feature_test queue_feature_test.c ../list.c ../deque.c ../queue.c $(CFLAG)

stack_feature_test: stack_feature_test.c deque.h deque.c list.h list.c stack.h stack.c
	$(CC) -o stack_feature_test stack_feature_test.c ../list.c ../deque.c ../stack.c $(CFLAG)

clean:
	rm -fr ./*_test ./*.o ../*.o 2> /dev/null
