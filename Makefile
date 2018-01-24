CXX=g++
CFLAGS=-Wall -std=c++11 -c
LDLIBS=-ltins
OBJS=src/Main.o src/Identifier.o src/StringMatchingIdentifier.o src/SpidIdentifier.o src/SpidInterface.o src/Fingerprint.o src/AttributeFingerprintHandler.o src/ProtocolModel.o

#
# Utility
#

all: shitty_wireshark

clean:
	rm -f **/*.o ./shitty_wireshark


#
# Executables
#

shitty_wireshark: src/Main.o src/Identifier.o src/StringMatchingIdentifier.o src/SpidIdentifier.o src/SpidInterface.o src/Fingerprint.o src/AttributeFingerprintHandler.o src/ProtocolModel.o
	$(CXX) $(OBJS) -o shitty_wireshark $(LDLIBS) 


#
# Object Files
#

src/Main.o: src/Main.cpp
	$(CXX) $(CFLAGS) src/Main.cpp -o src/Main.o

src/Identifier.o: src/Identifier.cpp
	$(CXX) $(CFLAGS) src/Identifier.cpp -o src/Identifier.o

src/StringMatchingIdentifier.o: src/StringMatchingIdentifier.cpp
	$(CXX) $(CFLAGS) src/StringMatchingIdentifier.cpp -o src/StringMatchingIdentifier.o

src/SpidIdentifier.o: src/SpidIdentifier.cpp
	$(CXX) $(CFLAGS) src/SpidIdentifier.cpp -o src/SpidIdentifier.o

src/SpidInterface.o: src/SpidInterface.cpp
	$(CXX) $(CFLAGS) src/SpidInterface.cpp -o src/SpidInterface.o

src/Fingerprint.o: src/Fingerprint.cpp
	$(CXX) $(CFLAGS) src/Fingerprint.cpp -o src/Fingerprint.o

src/AttributeFingerprintHandler.o: src/AttributeFingerprintHandler.cpp
	$(CXX) $(CFLAGS) src/AttributeFingerprintHandler.cpp -o src/AttributeFingerprintHandler.o

src/ProtocolModel.o: src/ProtocolModel.cpp
	$(CXX) $(CFLAGS) src/ProtocolModel.cpp -o src/ProtocolModel.o
