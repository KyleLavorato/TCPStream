CXX = g++
CFLAGS = -Wall -std=c++11 -Wno-unused-variable
LDLIBS = -ltins -lboost_regex
OBJS = src/Main.o src/Identifier.o src/StringMatchingIdentifier.o src/SpidIdentifier.o src/SpidInterface.o src/Fingerprint.o src/AttributeFingerprintHandler.o src/ProtocolModel.o src/Parser.o src/packet.o src/putilities.o src/HTTP_Generated.o src/SMB2_Generated.o src/FTP_Generated.o

all: TCPStream

clean: 
	rm -f **/*.o ./TCPStream

TCPStream: $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

.cpp.o: 
	$(CXX) $(CFLAGS) -o $*.o -c $*.cpp

