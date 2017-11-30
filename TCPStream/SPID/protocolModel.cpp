#include "protocolModel.h"

using namespace std;


ProtocolModel::ProtocolModel(){
	trainingSessionCount = 0;
	observationCount = 0;
	packetSize = AttributeFingerprintHandler("size");
	packetSource = AttributeFingerprintHandler("direction");
	byteFrequency = AttributeFingerprintHandler("frequency");
	//byteSequences = AttributeFingerprintHandler("sequences");
	byteOffsets = AttributeFingerprintHandler("offset");
}

void ProtocolModel::AddObservation (const byte packetData[], time_t packetTimestamp, int packetDirection, const unsigned long packetLength){
  observationCount++;
  packetSize.AddObservation(packetData, packetTimestamp, packetDirection, observationCount, packetLength);
  packetSource.AddObservation(packetData, packetTimestamp, packetDirection, observationCount, packetLength);
  byteFrequency.AddObservation(packetData, packetTimestamp, packetDirection, observationCount, packetLength);
  //byteSequences.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  byteOffsets.AddObservation(packetData, packetTimestamp, packetDirection, observationCount, packetLength);
}

double ProtocolModel::GetAverageKullbackLeiblerDivergenceFrom (double attributeModel[][1500]){
  double sizeDiv, sourceDiv, frequencyDiv, offsetDiv, sum;
  sizeDiv = packetSize.GetAverageKullbackLeiblerDivergenceFrom(attributeModel[1]);
  sourceDiv = packetSource.GetAverageKullbackLeiblerDivergenceFrom(attributeModel[2]);
  frequencyDiv = byteFrequency.GetAverageKullbackLeiblerDivergenceFrom(attributeModel[0]);
  offsetDiv = byteOffsets.GetAverageKullbackLeiblerDivergenceFrom(attributeModel[3]);
  // cout << "sizeDIV = " << sizeDiv << endl;
  // cout << "sourceDIV = " << sourceDiv << endl;
  // cout << "frequencyDIV = " << frequencyDiv << endl;
  // cout << "offsetDIV = " << offsetDiv << endl;
  sum = sizeDiv + sourceDiv + frequencyDiv + offsetDiv;
  sum /= 4;
  return sum;

}

void ProtocolModel::MergeWith (ProtocolModel otherModel){
	packetSize.MergeWith(otherModel.packetSize);
	packetSource.MergeWith(otherModel.packetSource);
	byteFrequency.MergeWith(otherModel.byteFrequency);
	byteOffsets.MergeWith(otherModel.byteOffsets);
}

void ProtocolModel::MergeWith (double attributeModel[][1500]){
	packetSize.MergeWith(attributeModel[1]);
	packetSource.MergeWith(attributeModel[2]);
	byteFrequency.MergeWith(attributeModel[0]);
	byteOffsets.MergeWith(attributeModel[3]);
}

void ProtocolModel::reset(){
	packetSize.reset();
	packetSource.reset();
	byteFrequency.reset();
	byteOffsets.reset();
}