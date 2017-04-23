CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall -std=c++11
LDFLAGS=-g -Wall -std=c++11
LDLIBS=-L../dahuasdk -ldhnetsdk
INCLUDES=-I.


SRCS=netalarm.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: netalarm

netalarm: $(OBJS)
	$(CXX) $(LDFLAGS) $(INCLUDES) -o netalarm $(OBJS) $(LDLIBS) 

netalarm.o: netalarm.cpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) netalarm
