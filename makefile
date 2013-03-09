EXECUTABLE := maxclique
LIBS := 

CC := g++
CFLAGS := -g -Wall
CXXFLAGS := $(CFLAGS)

SOURCE := $(wildcard *.c) $(wildcard *.cpp)
OBJS := $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(SOURCE)))
DEPS := $(patsubst %.o, %.d, $(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)), $(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d, %.c, $(MISSING_DEPS) $(patsubst %.d, %.cpp, $(MISSING_DEPS))))
CPPFLAGS += -MD
RM := rm -f

.PHONY: everything deps objs clean veryclean rebuild t r

everything: $(EXECUTABLE)

deps: $(DEPS)

objs: $(OBJS)

t:
	$(CC) $(CFLAGS) -o ver_test read_file.o Vertices.o Vertices_test.cc

r:
	./ver_test test/mytest.clq

clean:
	$(RM) *.o
	$(RM) *.d

veryclean: clean
	$(RM) $(EXECUTABLE)
	$(RM) ver_test

rebuild: veryclean everything

ifneq ($(MISSING_DEPS), )
	$(MISSING_DEPS) : 
	del -f $(patsubst %.d, %.o, $@)
endif

-include $(DEPS)

$(EXECUTABLE): $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS) $(addprefix -l, $(LIBS))
