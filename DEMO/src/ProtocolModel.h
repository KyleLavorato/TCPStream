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
	void AddObservation (const byte packetData[], time_t packetTimestamp, int packetDirection, const unsigned long packetLength, int portNum);
	double GetAverageKullbackLeiblerDivergenceFrom (double attributeModel[][512]);
	void MergeWith(ProtocolModel otherModel);
	void MergeWith(double attributeModel[][512]);
	void reset();
	int trainingSessionCount;
	unsigned long observationCount;
	AttributeFingerprintHandler packetSize;
	AttributeFingerprintHandler packetSource;
	AttributeFingerprintHandler byteFrequency;
	AttributeFingerprintHandler byteSequences;
	AttributeFingerprintHandler byteOffsets;
	AttributeFingerprintHandler dirNumSize;
	AttributeFingerprintHandler dirFreq;
	AttributeFingerprintHandler dirSize;
	AttributeFingerprintHandler portNumber;
};