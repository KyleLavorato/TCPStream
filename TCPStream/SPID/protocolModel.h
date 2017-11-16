#pragma once

#include <iostream>
#include <tuple>
#include "AttributeFingerprintHandler.h"

using namespace std;

class ProtocolModel {
private:
public:
	ProtocolModel();
	//packetTimestamp is time of recieving packet
	//packetDirection is 1 for client data, and 0 for server data
	void AddObservation (byte packetData[], time_t packetTimestamp, int packetDirection);
	double GetAverageKullbackLeiblerDivergenceFrom (ProtocolModel model);
	ProtocolModel MergeWith(ProtocolModel otherModel);
	int trainingSessionCount;
	unsigned long observationCount;
	AttributeFingerprintHandler packetSize;
	AttributeFingerprintHandler packetSource;
	AttributeFingerprintHandler byteFrequency;
	AttributeFingerprintHandler byteSequences;
	AttributeFingerprintHandler byteOffsets;
};