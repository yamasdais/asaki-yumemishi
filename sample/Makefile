PROGRAMS=sample0 utilexp
CXX=g++
CXXSTD=c++14
CXXFLAGS=-O -std=$(CXXSTD) -Wall -Wextra -g
INCLUDES=-I../src/main/include
LDFLAGS=-std=$(CXXSTD)

SRCS=$(shell ls *.cxx)
OBJS=$(SRCS:.cxx=.o)
DEPS=$(SRCS:.cxx=.dep)

.SUFFIXES: .cxx
.PHONY: all clean depend

all: $(PROGRAMS)

clean:
	/bin/rm -f *.o *.dep $(PROGRAMS) .depend

depend : $(DEPS)
.depend:
	touch .depend
$(DEPS) : .depend

%.dep: %.cxx
	$(CXX) $(INCLUDES) $(CXXFLAGS) -MM $(CPPFLAGS) $< > $@

.cxx.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

sample0: sample0.o sample_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

utilexp: utilexp.o
	$(CXX) $(LDFLAGS) -o $@ $^

include $(DEPS)
