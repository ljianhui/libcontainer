CC := gcc
CFLAG := -I ../ -L ../ -g

VPATH=./:../ 

all: array_feature_test array_effect_test \
	 list_feature_test\
	 priority_queue_feature_test\
	 deque_feature_test\
	 queue_feature_test\
	 stack_feature_test

array_feature_test: array_feature_test.c c_array.h c_array.c c_libdef.h
	$(CC) -o array_feature_test array_feature_test.c ../c_array.c $(CFLAG)

array_effect_test: array_effect_test.c c_array.h c_array.c
	$(CC) -o array_effect_test array_effect_test.c ../c_array.c $(CFLAG)

list_feature_test: list_feature_test.c c_list.h c_list.c
	$(CC) -o list_feature_test list_feature_test.c ../c_list.c $(CFLAG)

priority_queue_feature_test: priority_queue_feature_test.c c_priority_queue.h c_priority_queue.c
	$(CC) -o priority_queue_feature_test priority_queue_feature_test.c ../c_priority_queue.c $(CFLAG)

deque_feature_test: deque_feature_test.c c_deque.h c_deque.c c_list.h c_list.c
	$(CC) -o deque_feature_test deque_feature_test.c ../c_list.c ../c_deque.c $(CFLAG)

queue_feature_test: queue_feature_test.c c_deque.h c_deque.c c_list.h c_list.c c_queue.h c_queue.c
	$(CC) -o queue_feature_test queue_feature_test.c ../c_list.c ../c_deque.c ../c_queue.c $(CFLAG)

stack_feature_test: stack_feature_test.c c_deque.h c_deque.c c_list.h c_list.c c_stack.h c_stack.c
	$(CC) -o stack_feature_test stack_feature_test.c ../c_list.c ../c_deque.c ../c_stack.c $(CFLAG)

clean:
	rm -fr ./*_test ./*.o ../*.o 2> /dev/null
