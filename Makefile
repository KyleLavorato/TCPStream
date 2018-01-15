CXX=g++
CFLAGS=-Wall -std=c++11 -c
LDLIBS=-ltins

#
# Utility
#

all: shitty_wireshark

clean:
	rm -f **/*.o ./shitty_wireshark


#
# Executables
#

shitty_wireshark: src/Main.o src/Identifier.o src/StringMatchingIdentifier.o
	$(CXX) src/Main.o src/Identifier.o src/StringMatchingIdentifier.o -o shitty_wireshark $(LDLIBS) 


#
# Object Files
#

src/Main.o: src/Main.cpp
	$(CXX) $(CFLAGS) src/Main.cpp -o src/Main.o

src/Identifier.o: src/Identifier.cpp
	$(CXX) $(CFLAGS) src/Identifier.cpp -o src/Identifier.o

src/StringMatchingIdentifier.o: src/StringMatchingIdentifier.cpp
	$(CXX) $(CFLAGS) src/StringMatchingIdentifier.cpp -o src/StringMatchingIdentifier.o
