MAKEFLAGS+=--no-builtin-rules --no-builtin-varialbes

OUTPUT=./bin/gl

CXXFLAGS=-O3 -g -W -MMD -Wno-unused-function
CXXFLAGS+=-Iinclude
CXXFLAGS+=-Iinclude/Core/Maths/
CXXFLAGS+=-Iinclude/Core/Debug/
CXXFLAGS+=-Iinclude/Core/DataStructure/
CXXFLAGS+=-Iinclude/LowRenderer
CXXFLAGS+=-Iinclude/Physics
CXXFLAGS+=-Iinclude/Resources
CXXFLAGS+=-Iinclude/Tools
CXXFLAGS+=-Iinclude/ImGUI

CFLAGS=$(CXXFLAGS)
SRCPP=$(wildcard src/*.cpp)
SRCPP+=$(wildcard src/Core/Maths/*.cpp)
SRCPP+=$(wildcard src/Core/Debug/*.cpp)
SRCPP+=$(wildcard src/Core/DataStructure/*.cpp)
SRCPP+=$(wildcard src/LowRenderer/*.cpp)
SRCPP+=$(wildcard src/Physics/*.cpp)
SRCPP+=$(wildcard src/Resources/*.cpp)
SRCPP+=$(wildcard src/Tools/*.cpp)
SRCPP+=$(wildcard src/ImGUI/*.cpp)

SRC=$(wildcard src/*.c)

SRCLEAN=$(wildcard src/*.d)
SRCLEAN+=$(wildcard src/Core/Maths/*.d)
SRCLEAN+=$(wildcard src/Core/Debug/*.d)
SRCLEAN+=$(wildcard src/Core/DataStructure/*.d)
SRCLEAN+=$(wildcard src/LowRenderer/*.d)
SRCLEAN+=$(wildcard src/Physics/*.d)
SRCLEAN+=$(wildcard src/Resources/*.d)
SRCLEAN+=$(wildcard src/Tools/*.d)
SRCLEAN+=$(wildcard src/ImGUI/*.d)

SRCLEAN+=$(wildcard src/*.o)
SRCLEAN+=$(wildcard src/Core/Maths/*.o)
SRCLEAN+=$(wildcard src/Core/Debug/*.o)
SRCLEAN+=$(wildcard src/Core/DataStructure/*.o)
SRCLEAN+=$(wildcard src/LowRenderer/*.o)
SRCLEAN+=$(wildcard src/Physics/*.o)
SRCLEAN+=$(wildcard src/Resources/*.o)
SRCLEAN+=$(wildcard src/Tools/*.o)
SRCLEAN+=$(wildcard src/ImGUI/*.o)

CC=gcc
CXX?=g++
LDFLAGS=-Llibs/linux
LDLIBS=-Llib -lglfw -lGL -lGLU -ldl -lim
OBJS=$(SRC:.c=.o)
OBJS+=$(SRCPP:.cpp=.o)
DEPS=$(OBJS:.o=.d)


.PHONY: all clean clear run

all: $(OUTPUT)

-include $(DEPS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) 

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(OUTPUT): $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)

run: $(OBJS)
	$(OUTPUT)

clean:
	rm -f $(OBJS) $(OUTPUT)

clear:
	rm -f $(OBJS) $(SRCLEAN) $(OUTPUT)
