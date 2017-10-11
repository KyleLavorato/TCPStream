CXX=g++
CPPFLAGS=-std=c++11
LDLIBS=-ltins -lboost_regex
OBJS= fractions.o

all: tcpstream

tcpstream: pmain.o $(OBJS)
	$(CXX) -o tcpstream pmain.o $(OBJS)

clean:
	rm -f *.o ./tcpstream

# MAIN
pmain.o: fractions.h

# SUPPORT
fractions.o: fractions.h