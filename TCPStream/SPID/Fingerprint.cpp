#include "Fingerprint.h"

using namespace std;

Fingerprint::Fingerprint(){};

Fingerprint::Fingerprint(int counter){
	int size = counter;
	int probabilityDistributionVector [size][2] = {{}};
}

void Fingerprint::IncrementFingerprintCounterAtIndex(int index){
	probabilityDistributionVector[index][0]++;
}

Fingerprint Fingerprint::MergeWith(Fingerprint otherFingerprint){

}
