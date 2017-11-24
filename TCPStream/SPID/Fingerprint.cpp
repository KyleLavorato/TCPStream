#include "Fingerprint.h"

using namespace std;

Fingerprint::Fingerprint(){};

Fingerprint::Fingerprint(int counter){
	size = counter;
	probabilityDistributionVector;
	probabilityDistributionVector.resize(size,vector<double>(2,0));
}

void Fingerprint::IncrementFingerprintCounterAtIndex(int index){
	probabilityDistributionVector[index][0]++;
}

void Fingerprint::MergeWith(Fingerprint otherFingerprint){
	int total = 0;
	for (int i = 0; i < size; i++){
		probabilityDistributionVector[i][0] += otherFingerprint.probabilityDistributionVector[i][0];
		total += probabilityDistributionVector[i][0];
	}
	for (int i = 0; i < size; i++){
		probabilityDistributionVector[i][1] = probabilityDistributionVector[i][0] / total;		
	}
}
