CXX=g++
CPPFLAGS=-std=c++11
LDLIBS=-ltins -lboost_regex
OBJS= segment.o SMB2_Generated.o putilities.o packet.o parser.o

all: tcpstream

tcpstream: pmain.o $(OBJS)
	$(CXX) -o tcpstream pmain.o $(OBJS) $(LDLIBS)

clean:
	rm -f *.o ./tcpstream

# MAIN
pmain.o: segment.h

# SUPPORT
segment.o: segment.h

parser.o: parser.h

SMB2_Generated.o: pglobals.h SMB2_Generated.h
putilities.o: putilities.h
packet.o: globals.h packet.h