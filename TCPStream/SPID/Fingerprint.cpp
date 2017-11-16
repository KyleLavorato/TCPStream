#pragma once 

#include <iostream>
#include <tuple>

using namespace std;

class Fingerprint {
public:
	int size;
	double probabilityDistributionVector[][2];
	Fingerprint ();
	Fingerprint (int counter);
	void IncrementFingerprintCounterAtIndex(int index);
	Fingerprint MergeWith (Fingerprint otherFingerprint);
private:
};