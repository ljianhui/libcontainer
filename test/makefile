CC := gcc
CFLAG := -I ../ -L ../ -g

VPATH=./:../ 

all: array_feature_test array_effect_test \
     list_feature_test\
	 priority_queue_feature_test\
	 deque_feature_test\
	 queue_feature_test\
	 stack_feature_test

array_feature_test: array_feature_test.c mky_array.h mky_array.c
	$(CC) -o array_feature_test array_feature_test.c ../mky_array.c $(CFLAG)

array_effect_test: array_effect_test.c mky_array.h mky_array.c
	$(CC) -o array_effect_test array_effect_test.c ../mky_array.c $(CFLAG)

list_feature_test: list_feature_test.c mky_list.h mky_list.c
	$(CC) -o list_feature_test list_feature_test.c ../mky_list.c $(CFLAG)

priority_queue_feature_test: priority_queue_feature_test.c mky_priority_queue.h mky_priority_queue.c
	$(CC) -o priority_queue_feature_test priority_queue_feature_test.c ../mky_priority_queue.c $(CFLAG)

deque_feature_test: deque_feature_test.c mky_deque.h mky_deque.c mky_list.h mky_list.c
	$(CC) -o deque_feature_test deque_feature_test.c ../mky_list.c ../mky_deque.c $(CFLAG)

queue_feature_test: queue_feature_test.c mky_deque.h mky_deque.c mky_list.h mky_list.c mky_queue.h mky_queue.c
	$(CC) -o queue_feature_test queue_feature_test.c ../mky_list.c ../mky_deque.c ../mky_queue.c $(CFLAG)

stack_feature_test: stack_feature_test.c mky_deque.h mky_deque.c mky_list.h mky_list.c mky_stack.h mky_stack.c
	$(CC) -o stack_feature_test stack_feature_test.c ../mky_list.c ../mky_deque.c ../mky_stack.c $(CFLAG)

clean:
	rm -fr ./*_test ./*.o ../*.o 2> /dev/null
