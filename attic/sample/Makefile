PROGRAMS=sample0 utilexp literal literal0
CXX=g++
CXXSTD=c++17
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

sample0: sample0.o
	$(CXX) $(LDFLAGS) -o $@ $^

utilexp: utilexp.o
	$(CXX) $(LDFLAGS) -o $@ $^

literal: literal.o
	$(CXX) $(LDFLAGS) -o $@ $^
literal0: literal0.o
	$(CXX) $(LDFLAGS) -o $@ $^

include $(DEPS)
