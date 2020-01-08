# CC := gcc
CC := clang
LDFLAGS=
INCUDES := -I../include
CFLAGS += -Wall -Wextra -Wpedantic -std=gnu99 -g $(INCUDES) $(LDFLAGS)
ELF := ../run_tests

SRCS :=  \
	../src/string.c \
	../src/list.c \
	\
	string_test.c \
	list_test.c \
	result_test.c \
	\
	tests_main.c

OBJS := $(SRCS:.c=.o)

all: $(ELF)

$(ELF): $(OBJS)
	$(CC) $(LDFLAGS) $? -o $@

../src/%.o : ../src/%.c
	$(CC) $(CFLAGS) -c $? -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $?

clean:
	rm $(OBJS) $(ELF)
