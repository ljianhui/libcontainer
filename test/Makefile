CC := gcc
INCS := -I ../src
LIBS := -L../lib -lcontainer
CFLAG := -g -Wall -O

SRCS := ${wildcard *.c}
DEPS := $(SRCS:.c=.d)
OBJS := $(SRCS:.c=.o)
EXES := ${basename $(SRCS)}

all: $(OBJS) $(DEPS) $(EXES)

$(EXES):%:%.o
	$(CC) -o $@ $< $(INCS) $(LIBS) $(CFLAG) 

$(OBJS):%.o:%.c
	$(CC) -c $< -o $@ $(INCS) $(CFLAG)

$(DEPS):%.d:%.c
	rm -f $@;
	$(CC) -MM $< $(INCS) > $@

-include $(DEPS)

clean:
	-rm -fr  $(EXES) *.o *.d
