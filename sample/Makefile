PROGRAMS=sample0
CXX=g++ 
CXXFLAGS=-O -std=c++14 -Wall -Wextra -g
INCLUDES=-I../src/main/include
LDFLAGS=-std=c++14

SRCS=$(shell ls *.cxx)
OBJS=$(SRCS:.cxx=.o)
DEPS=$(SRCS:.cxx=.dep)

.SUFFIXES: .cxx
.PHONY: all clean depend

all: $(PROGRAMS)

clean:
	/bin/rm -f *.o *.dep $(PROGRAMS)

depend : $(DEPS)

%.dep: %.cxx
	$(CXX) $(INCLUDES) $(CXXFLAGS) -MM $(CPPFLAGS) $< > $@

.cxx.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

sample0: sample0.o sample_lib.o
	$(CXX) $(LDFLAGS) -o $@ $<

include $(DEPS)
