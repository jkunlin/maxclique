EXECUTABLE := maxclique.exe
LIBS := 

CC := g++
CFLAGS := -g -Wall -O3 
CXXFLAGS := $(CFLAGS)

SOURCE := $(wildcard *.c) $(wildcard *.cpp)
OBJS := $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(SOURCE)))
DEPS := $(patsubst %.o, %.d, $(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)), $(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d, %.c, $(MISSING_DEPS) $(patsubst %.d, %.cpp, $(MISSING_DEPS))))
CPPFLAGS += -MD
RM := del -f

.PHONY: everything deps objs clean veryclean rebuild

everything: $(EXECUTABLE)

deps: $(DEPS)

objs: $(OBJS)

clean:
	$(RM) *.o
	$(RM) *.d

veryclean: clean
	$(RM) $(EXECUTABLE)

rebuild: veryclean everything

ifneq ($(MISSING_DEPS), )
	$(MISSING_DEPS) : 
	del -f $(patsubst %.d, %.o, $@)
endif

-include $(DEPS)

$(EXECUTABLE): $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS) $(addprefix -l, $(LIBS))
