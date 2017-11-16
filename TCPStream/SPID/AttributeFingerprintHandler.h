#pragma once

#include <iostream>
#include <tuple>
#include <ctime>
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
	void AddObservation (byte packetData[], time_t packetTimestamp, int packetDirection, int packetOrderNumberInSession);
	double GetAverageKullbackLeiblerDivergenceFrom (AttributeFingerprintHandler model);
	AttributeFingerprintHandler MergeWith(Fingerprint otherFingerprint);
	int* GetMeasurements(byte packetData[], time_t packetTimestamp, int packetDirection, int packetOrderNumberInSession);
};