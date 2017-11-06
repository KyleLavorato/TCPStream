CXX=g++
CPPFLAGS=-std=c++11
LDLIBS=-ltins
OBJS= src/segment.o

all: tcpstream

tcpstream: src/pmain.o $(OBJS)
	$(CXX) -o tcpstream src/pmain.o $(OBJS) $(LDLIBS)

clean:
	rm -f **/*.o ./tcpstream

# MAIN
src/pmain.o: src/segment.h

# SUPPORT
src/segment.o: src/segment.h
