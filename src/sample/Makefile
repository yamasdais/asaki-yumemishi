PROGRAMS=sample0
CXX=g++ 
CXXFLAGS=-O -std=c++14 -Wall -Wextra -g
INCLUDES=-I../main/include
LDFLAGS=-std=c++14

.SUFFIXES: .cxx
.PHONY: all clean

all: $(PROGRAMS)

clean:
	/bin/rm -f *.o $(PROGRAMS)

.cxx.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

sample0: sample0.o
	$(CXX) $(LDFLAGS) -o $@ $<

