#pragma once 

#include <iostream>
#include <vector>

using namespace std;

class Fingerprint {
public:
	int size;
	vector <vector <double>> probabilityDistributionVector;
	Fingerprint ();
	Fingerprint (int counter);
	void IncrementFingerprintCounterAtIndex(int index);
	Fingerprint MergeWith (Fingerprint otherFingerprint);
private:
};