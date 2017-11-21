#include "AttributeFingerprintHandler.h"
#include <valarray>

using namespace std;

AttributeFingerprintHandler::AttributeFingerprintHandler(){};

AttributeFingerprintHandler::AttributeFingerprintHandler(string name){
	cout << "begin attributeFingerprintHandler" <<endl;
	attributeName = name;
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
		counter = 1; //?????
	}
	else if (attributeName == "offset"){
		counter = 257; //First 128 bits of application data
	}
	cout << attributeName << endl;
	Fingerprint attributeFingerprint (counter);
	cout <<"end attributeFingerprintHandler " <<endl;
}

void AttributeFingerprintHandler::AddObservation (const byte packetData[], time_t packetTimestamp, int packetDirection, int packetOrderNumberInSession){
  //int* measurements;
  cout << "observation for " << attributeName << endl;
  vector<int> measurements;
  int total = 0;
  int measurementsLength;
  //Gets the indicies of values to be incremented
  measurements = GetMeasurements(packetData,  packetTimestamp, packetDirection, packetOrderNumberInSession);
  measurementsLength = measurements.size();
  cout << measurements[0] << endl;
  //measurementsLength = sizeof(measurements)/sizeof(*measurements); //Calculates length of measurements array
  //Increments all approiate counter vector indicies
  for (int i = 0; i < measurementsLength; i++){
  	cout << i << "  " << measurementsLength << endl;
  	attributeFingerprint.IncrementFingerprintCounterAtIndex(measurements[i]);
  }
  cout << "we good? " <<endl;
  for (int i = 0; i < attributeFingerprint.size; i++){
  	total += attributeFingerprint.probabilityDistributionVector[i][0];
  }
  cout << "problem with dis vector" << endl;
  cout << "still gucci?" << endl;
  for (int i = 0; i < attributeFingerprint.size; i++){
  	attributeFingerprint.probabilityDistributionVector[i][1] = attributeFingerprint.probabilityDistributionVector[i][0] / total;
  }
  //delete[] indiciesToBeIncremented;
}

double AttributeFingerprintHandler::GetAverageKullbackLeiblerDivergenceFrom (AttributeFingerprintHandler model){
	//Nothing yet
}

AttributeFingerprintHandler AttributeFingerprintHandler::MergeWith (Fingerprint otherFingerprint){
	//Nothing yet
}

vector<int> AttributeFingerprintHandler::GetMeasurements (const byte* packetData, time_t packetTimestamp, int packetDirection, int packetOrderNumberInSession){
	cout << attributeName << endl;
	if (attributeName == "size"){
		//calculates size of packet
		int length = sizeof(packetData)/sizeof(*packetData);
		//int* indiciesToBeIncremented = new int [1];
		vector<int> indiciesToBeIncremented(1);
		indiciesToBeIncremented[0] = length;
		return indiciesToBeIncremented;
	}
	else if (attributeName == "direction"){
		//puts 0 or 1 to be incremented depeding on packet direction
		//int* indiciesToBeIncremented = new int [1];
		vector<int> indiciesToBeIncremented(1);
		indiciesToBeIncremented[0] = packetDirection;
		return indiciesToBeIncremented;
	}
	else if (attributeName == "frequency"){
		// for each ascii value, the corresponding value in the counter vector is increased
		int length = sizeof(packetData)/sizeof(*packetData);
		//int* indiciesToBeIncremented = new int [length];
		vector<int> indiciesToBeIncremented(length);
		cout <<"but did we get here?" << endl;
		cout << length << endl;
		cout << packetData[0] << endl;
		for (int i = 0; i < length; i++){
			cout << packetData[i] << endl;
			indiciesToBeIncremented[i] = int(packetData[i]);
		}
		cout << "holla at me bois if we got here" <<endl;
		return indiciesToBeIncremented;
	}
	else if (attributeName == "sequences"){

	}
	else if (attributeName == "offset"){
		int length = sizeof(packetData)/sizeof(*packetData);
		//int* indiciesToBeIncremented = new int [128];
		vector<int> indiciesToBeIncremented(128);
		cout << "did we make it?" << endl;
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