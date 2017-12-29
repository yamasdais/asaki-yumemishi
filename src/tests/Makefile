libgtestsrcdir = /usr/src/gtest/src
libgtest_CXXFLAGS = -I$(libgtestsrcdir) -I$(libgtestsrcdir)/.. \
	-DGTEST_USE_OWN_TR1_TUPLE=1 -Wno-unused-private-field

PROGRAMS=all_test
CXX=g++
CXXSTD=c++14
CXXFLAGS=-O -std=$(CXXSTD) -Wall -Wextra -g
INCLUDES=-I../main/include -I.
LDFLAGS=-std=$(CXXSTD) -L. -lgtest -lpthread

SRCS=$(shell ls *.cxx)
OBJS=$(SRCS:.cxx=.o)
DEPS=$(SRCS:.cxx=.dep)

.SUFFIXES: .cxx
.PHONY: all clean depend

all: $(PROGRAMS)

clean:
	/bin/rm -f *.o *.dep $(PROGRAMS) libgtest.a

depend : $(DEPS)

%.dep: %.cxx
	$(CXX) $(INCLUDES) $(CXXFLAGS) -MM $(CPPFLAGS) $< > $@

.cxx.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<


libgtest.a:
	$(CXX) $(libgtest_CXXFLAGS) -o gtest-all.o -c $(libgtestsrcdir)/gtest-all.cc
	$(CXX) $(libgtest_CXXFLAGS) -o gtest-main.o -c $(libgtestsrcdir)/gtest_main.cc
	ar rcs $@ gtest-all.o gtest-main.o

all_test: $(OBJS) libgtest.a
	$(CXX) $(LDFLAGS) -o $@ $^

include $(DEPS)
