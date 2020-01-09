CC := g++
LDFLAGS=-ludev -lpthread
INCUDES := -I./include
CFLAGS += -Wall -Wextra -Wpedantic -std=gnu++2a -g -fPIC $(INCUDES) $(LDFLAGS)
LIB := libbadsurf.so

SRCS :=  \
	src/posix/error.cpp \
	src/udev/device.cpp \
	src/udev/enumerate.cpp \
	src/udev/udev.cpp \
	src/ata.cpp \
	src/hpa_set.cpp \
	src/scsi.cpp \
	src/utils.cpp \
	src/read_test.cpp \
	src/procedure.cpp \
	src/smart_parse.cpp \
	src/smart_show.cpp \
	src/badsurflib.cpp \

OBJS := $(SRCS:.cpp=.o)

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(LDFLAGS) $^ -shared -o $@

src/%.o : src/%.cpp
	$(CC) $(CFLAGS) -c $? -o $@

clean:
	rm -rf $(OBJS) $(LIB)
