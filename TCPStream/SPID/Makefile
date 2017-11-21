CXX=g++
CPPFLAGS=-std=c++11
LDLIBS=-ltins -lboost_regex
OBJS= segment.o SPIDinterface.o Fingerprint.o AttributeFingerprintHandler.o protocolModel.o

all: tcpstream

tcpstream: pmain.o $(OBJS)
	$(CXX) -o tcpstream pmain.o $(OBJS) $(LDLIBS)

clean:
	rm -f *.o ./tcpstream

# MAIN
pmain.o: segment.h

# SUPPORT
segment.o: segment.h SPIDinterface.h

protocolModel.o: protocolModel.h AttributeFingerprintHandler.h Fingerprint.h

AttributeFingerprintHandler.o: AttributeFingerprintHandler.h Fingerprint.h

Fingerprint.o: Fingerprint.h

SPIDinterface.o: SPIDinterface.h protocolModel.h