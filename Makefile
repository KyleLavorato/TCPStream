CXX=g++
CFLAGS=-Wall -std=c++11 -c
LDLIBS=-ltins
OBJS=src/Main.o src/Identifier.o src/StringMatchingIdentifier.o src/SpidIdentifier.o src/SPIDinterface.o src/Fingerprint.o src/AttributeFingerprintHandler.o src/protocolModel.o

#
# Utility
#

all: shitty_wireshark

clean:
	rm -f **/*.o ./shitty_wireshark


#
# Executables
#

shitty_wireshark: src/Main.o src/Identifier.o src/StringMatchingIdentifier.o src/SpidIdentifier.o src/SPIDinterface.o src/Fingerprint.o src/AttributeFingerprintHandler.o src/protocolModel.o
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

src/SPIDinterface.o: src/SPIDinterface.cpp
	$(CXX) $(CFLAGS) src/SPIDinterface.cpp -o src/SPIDinterface.o

src/Fingerprint.o: src/Fingerprint.cpp
	$(CXX) $(CFLAGS) src/Fingerprint.cpp -o src/Fingerprint.o

src/AttributeFingerprintHandler.o: src/AttributeFingerprintHandler.cpp
	$(CXX) $(CFLAGS) src/AttributeFingerprintHandler.cpp -o src/AttributeFingerprintHandler.o

src/protocolModel.o: src/protocolModel.cpp
	$(CXX) $(CFLAGS) src/protocolModel.cpp -o src/protocolModel.o
