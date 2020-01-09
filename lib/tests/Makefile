CC := g++
INCUDES := -I../include
LDFLAGS := ../libbadsurf.so
CFLAGS += -Wall -Wextra -Wpedantic -std=c++2a -g $(INCUDES) $(LDFLAGS)
ELF := ../run_tests

SRCS :=  \
	badsurf_test.cpp \
	tests_main.cpp

OBJS := $(SRCS:.cpp=.o)

all: $(ELF)

$(ELF): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $?

clean:
	rm $(OBJS) $(ELF)
