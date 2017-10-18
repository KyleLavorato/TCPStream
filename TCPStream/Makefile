CXX=g++
CPPFLAGS=-std=c++11
LDLIBS=-ltins -lboost_regex
OBJS= segment.o

all: tcpstream

tcpstream: pmain.o $(OBJS)
	$(CXX) -o tcpstream pmain.o $(OBJS) $(LDLIBS)

clean:
	rm -f *.o ./tcpstream

# MAIN
pmain.o: segment.h

# SUPPORT
segment.o: segment.h