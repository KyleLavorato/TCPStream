CXX=g++
CFLAGS=-Wall -std=c++11
LDLIBS=-ltins -lboost_regex
OBJS=src/Main.o src/Identifier.o src/StringMatchingIdentifier.o src/SpidIdentifier.o src/SpidInterface.o src/Fingerprint.o src/AttributeFingerprintHandler.o src/ProtocolModel.o src/Parser.o src/SMB2_Generated.o src/packet.o src/putilities.o

all: shitty_wireshark

clean:
	rm -f **/*.o ./shitty_wireshark

shitty_wireshark: $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS) 

.cpp.o:
	$(CXX) $(CFLAGS) -o $*.o -c $*.cpp
