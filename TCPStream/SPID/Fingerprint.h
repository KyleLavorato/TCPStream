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
	void MergeWith (Fingerprint otherFingerprint);
	void MergeWith (double* attributeArray);
	void reset();
private:
};