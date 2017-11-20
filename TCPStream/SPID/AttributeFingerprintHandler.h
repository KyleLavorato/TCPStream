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
	void AddObservation (const byte packetData[], time_t packetTimestamp, int packetDirection, int packetOrderNumberInSession);
	double GetAverageKullbackLeiblerDivergenceFrom (AttributeFingerprintHandler model);
	AttributeFingerprintHandler MergeWith(Fingerprint otherFingerprint);
	vector<int> GetMeasurements(const byte packetData[], time_t packetTimestamp, int packetDirection, int packetOrderNumberInSession);
};