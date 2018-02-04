#pragma once

#include <iostream>
#include <tuple>
#include <ctime>
#include <vector>
#include "Fingerprint.h"

using namespace std;
using byte = unsigned char;

class AttributeFingerprintHandler {
private:
public:
	Fingerprint attributeFingerprint;
	string attributeName;
	int counter;
	AttributeFingerprintHandler();
	AttributeFingerprintHandler(string name);
	void AddObservation (const byte packetData[], time_t packetTimestamp, int packetDirection, int packetOrderNumberInSession, const unsigned long packetLength, int portNum);
	double GetAverageKullbackLeiblerDivergenceFrom (double* attributeArray);
	void MergeWith(AttributeFingerprintHandler otherAttributeHandler);
	void MergeWith(double* attributeArray);
	void reset();
	vector<int> GetMeasurements(const byte packetData[], time_t packetTimestamp, int packetDirection, int packetOrderNumberInSession, const unsigned long packetLength, int portNum);
};