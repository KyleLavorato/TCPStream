#include "AttributeFingerprintHandler.h"

using namespace std;

AttributeFingerprintHandler::AttributeFingerprintHandler(){};

AttributeFingerprintHandler::AttributeFingerprintHandler(string name){
	string attributeName = name;
	int counter = 0; // counter is the number of indices to be incremented. Will be calculated in GetMeasurements
	if (attributeName == "size") {
		counter = 700; //Average packet size is ~557 bytes.  This gives room for above average packet sizes
	}
	else if (attributeName == "direction"){
		counter = 2; //Packet can be going one of two directions
	}
	else if (attributeName == "frequency"){
		counter = 256; //Each index is for one ASCII value (computers reserve 8 bits for an ASCII character)
	}
	else if (attributeName == "sequences"){
		counter = 0; //?????
	}
	else if (attributeName == "offset"){
		counter = 257; //First 128 bits of application data
	}
	Fingerprint attributeFingerprint;
}

void AttributeFingerprintHandler::AddObservation (byte packetData[], time_t packetTimestamp, int packetDirection, int packetOrderNumberInSession){
  int* measurements;
  measurements = GetMeasurements(packetData,  packetTimestamp, packetDirection, packetOrderNumberInSession);
  for (int i = 0; i < counter; i++){
  	attributeFingerprint.IncrementFingerprintCounterAtIndex(measurements[i]);
  }
}

double AttributeFingerprintHandler::GetAverageKullbackLeiblerDivergenceFrom (AttributeFingerprintHandler model){
	//Nothing yet
}

AttributeFingerprintHandler AttributeFingerprintHandler::MergeWith (Fingerprint otherFingerprint){
	//Nothing yet
}

int* AttributeFingerprintHandler::GetMeasurements (byte packetData[], time_t packetTimestamp, int packetDirection, int packetOrderNumberInSession){
	if (attributeName == "size"){
		int length = sizeof(packetData)/sizeof(*packetData);
		int indiciesToBeIncremented [1];
		indiciesToBeIncremented[0] = length;
		return indiciesToBeIncremented;
	}
	else if (attributeName == "direction"){
		int indiciesToBeIncremented [1];
		indiciesToBeIncremented[0] = packetDirection;
		return indiciesToBeIncremented;
	}
	else if (attributeName == "frequency"){
		int length = sizeof(packetData)/sizeof(*packetData);
		int indiciesToBeIncremented [length];
		for (int i=0; i < length; i++){
			indiciesToBeIncremented[i] = int(packetData[i]);
		}
		return indiciesToBeIncremented;
	}
	else if (attributeName == "sequences"){

	}
	else if (attributeName == "offset"){
		int length = sizeof(packetData)/sizeof(*packetData);
		int indiciesToBeIncremented[128];
		for (int i = 0; i < 128; i++){
			if (packetData[i]) {
				indiciesToBeIncremented[i] = 2*i;
			}
			else{
				indiciesToBeIncremented[i] = 2*i+1;
			}
		}
	}
}