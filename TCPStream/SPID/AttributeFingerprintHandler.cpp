#include "AttributeFingerprintHandler.h"
#include <valarray>
#include <math.h>

using namespace std;

AttributeFingerprintHandler::AttributeFingerprintHandler(){};

AttributeFingerprintHandler::AttributeFingerprintHandler(string name){
	attributeName = name;
	int counter = 0; // counter is the number of indices to be incremented. Will be calculated in GetMeasurements
	if (attributeName == "size") {
		counter = 1500; //Most are under 1500 bytes, so any over is counted as 1499.  This gives room for above average packet sizes
	}
	else if (attributeName == "direction"){
		counter = 2; //Packet can be going one of two directions
	}
	else if (attributeName == "frequency"){
		counter = 256; //Each index is for one ASCII value (computers reserve 8 bits for an ASCII character)
	}
	else if (attributeName == "sequences"){
		counter = 1; //?????
	}
	else if (attributeName == "offset"){
		counter = 257; //First 128 bits of application data
	}
	attributeFingerprint = Fingerprint(counter);
}

void AttributeFingerprintHandler::AddObservation (const byte packetData[], time_t packetTimestamp, int packetDirection, int packetOrderNumberInSession, const unsigned long packetLength){
  vector<int> measurements;
  int total = 0;
  int measurementsLength;
  //Gets the indicies of values to be incremented
  measurements = GetMeasurements(packetData,  packetTimestamp, packetDirection, packetOrderNumberInSession, packetLength);
  measurementsLength = measurements.size();
  //Increments all approiate counter vector indicies
  for (int i = 0; i < measurementsLength; i++){
  	attributeFingerprint.IncrementFingerprintCounterAtIndex(measurements[i]);
  }
  for (int i = 0; i < attributeFingerprint.size; i++){
  	total += attributeFingerprint.probabilityDistributionVector[i][0];
  }
  for (int i = 0; i < attributeFingerprint.size; i++){
  	attributeFingerprint.probabilityDistributionVector[i][1] = attributeFingerprint.probabilityDistributionVector[i][0] / total;
  }
}

double AttributeFingerprintHandler::GetAverageKullbackLeiblerDivergenceFrom (double* attributeArray){
	double divergence;
	divergence = 0;
	for (int i = 0; i < attributeFingerprint.size; i++){
		if (attributeArray[i] != 0 and attributeFingerprint.probabilityDistributionVector[i][1] != 0){
			divergence += abs(attributeArray[i] * log2(attributeArray[i] / attributeFingerprint.probabilityDistributionVector[i][1]));
			//divergence += -(attributeArray[i] * log2(attributeFingerprint.probabilityDistributionVector[i][1] / attributeArray[i]));
		}
	}
	return divergence;
}

void AttributeFingerprintHandler::MergeWith (AttributeFingerprintHandler otherAttributeHandler){
	attributeFingerprint.MergeWith(otherAttributeHandler.attributeFingerprint);
}

void AttributeFingerprintHandler::MergeWith (double* attributeArray){
	attributeFingerprint.MergeWith(attributeArray);
}

void AttributeFingerprintHandler::reset(){
	attributeFingerprint.reset();
}

vector<int> AttributeFingerprintHandler::GetMeasurements (const byte* packetData, time_t packetTimestamp, int packetDirection, int packetOrderNumberInSession, const unsigned long packetLength){
	if (attributeName == "size"){
		//calculates size of packet
		int length = packetLength;
		if (length >= 1500){
			length = 1499;
		}
		vector<int> indiciesToBeIncremented(1);
		indiciesToBeIncremented[0] = length;
		return indiciesToBeIncremented;
	}
	else if (attributeName == "direction"){
		//puts 0 or 1 to be incremented depeding on packet direction
		vector<int> indiciesToBeIncremented(1);
		indiciesToBeIncremented[0] = packetDirection;
		return indiciesToBeIncremented;
	}
	else if (attributeName == "frequency"){
		// for each ascii value, the corresponding value in the counter vector is increased
		int length = packetLength;
		vector<int> indiciesToBeIncremented(length);
		for (int i = 0; i < length; i++){
			indiciesToBeIncremented[i] = int(packetData[i]);
		}
		return indiciesToBeIncremented;
	}
	else if (attributeName == "sequences"){

	}
	else if (attributeName == "offset"){
		int length = sizeof(packetData)/sizeof(*packetData);
		vector<int> indiciesToBeIncremented(128);
		for (int i = 0; i < 128; i++){
			if (packetData[i]) {
				indiciesToBeIncremented[i] = 2*i;
			}
			else{
				indiciesToBeIncremented[i] = 2*i+1;
			}
		}
		return indiciesToBeIncremented;
	}
}