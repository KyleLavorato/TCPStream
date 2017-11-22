CXX=g++
CFLAGS=-Wall -std=c++11 -c
LDLIBS=-ltins

#
# Utility
#

all: shitty_wireshark identify

clean:
	rm -f **/*.o ./shitty_wireshark ./identifier


#
# Executables
#

shitty_wireshark: src/pmain.o src/segment.o
	$(CXX) src/pmain.o src/segment.o -o shitty_wireshark $(LDLIBS) 

identify: src/identify.o
	$(CXX) src/identify.o -o identify


#
# Object Files
#

src/pmain.o: src/pmain.cpp
	$(CXX) $(CFLAGS) src/pmain.cpp -o src/pmain.o

src/segment.o: src/segment.h src/segment.cpp
	$(CXX) $(CFLAGS) src/segment.cpp -o src/segment.o

src/identify.o: src/identify.cpp
	$(CXX) $(CFLAGS) src/identify.cpp -o src/identify.o
