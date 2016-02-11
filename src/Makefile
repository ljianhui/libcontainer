CC := gcc
FLAGS := -g -Wall -O

SRCS := ${wildcard *.c}
OBJS := $(SRCS:.c=.o)
TARGET := ../lib/libcontainer.a

all: $(OBJS)
	ar -r $(TARGET) $(OBJS)

$(OBJS): %.o: %.c
	$(CC) -c $< -o $@ $(FLAGS)

clean:
	-rm -f $(TARGET) *.o
