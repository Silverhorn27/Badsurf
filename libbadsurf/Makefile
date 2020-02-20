# CXX := g++
CXX := clang++
LDFLAGS=-ludev -lpthread
INCUDES := -I./include
CXXFLAGS += -Wall -Wextra -Wpedantic -std=gnu++2a -g -fPIC $(INCUDES) $(LDFLAGS)
LIB := libbadsurf.so

SRCS :=  \
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
	$(CXX) $(LDFLAGS) $^ -shared -o $@

src/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

clean:
	rm -rf $(OBJS) $(LIB)
