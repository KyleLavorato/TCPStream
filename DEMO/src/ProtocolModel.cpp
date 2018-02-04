#include "ProtocolModel.h"

using namespace std;


ProtocolModel::ProtocolModel(){
	trainingSessionCount = 0;
	observationCount = 0;
	packetSize = AttributeFingerprintHandler("size");
	packetSource = AttributeFingerprintHandler("direction");
	byteFrequency = AttributeFingerprintHandler("frequency");
	//byteSequences = AttributeFingerprintHandler("sequences");
	byteOffsets = AttributeFingerprintHandler("offset");
	dirNumSize = AttributeFingerprintHandler("dirnumsize");
	dirFreq = AttributeFingerprintHandler("dirfreq");
	dirSize = AttributeFingerprintHandler("dirsize");
	portNumber = AttributeFingerprintHandler("portnumber");
}

void ProtocolModel::AddObservation (const byte packetData[], time_t packetTimestamp, int packetDirection, const unsigned long packetLength, int portNum){
  observationCount++;
  packetSize.AddObservation(packetData, packetTimestamp, packetDirection, observationCount, packetLength, portNum);
  packetSource.AddObservation(packetData, packetTimestamp, packetDirection, observationCount, packetLength, portNum);
  byteFrequency.AddObservation(packetData, packetTimestamp, packetDirection, observationCount, packetLength, portNum);
  //byteSequences.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  byteOffsets.AddObservation(packetData, packetTimestamp, packetDirection, observationCount, packetLength, portNum);
  dirNumSize.AddObservation(packetData, packetTimestamp, packetDirection, observationCount, packetLength, portNum);
  dirFreq.AddObservation(packetData, packetTimestamp, packetDirection, observationCount, packetLength, portNum);
  dirSize.AddObservation(packetData, packetTimestamp, packetDirection, observationCount, packetLength, portNum);
  portNumber.AddObservation(packetData, packetTimestamp, packetDirection, observationCount, packetLength, portNum);
}

double ProtocolModel::GetAverageKullbackLeiblerDivergenceFrom (double attributeModel[][512]){
  double sizeDiv, sourceDiv, frequencyDiv, offsetDiv, dirNumSizeDiv, dirFreqDiv, dirSizeDiv, portNumberDiv, sum;
  sizeDiv = packetSize.GetAverageKullbackLeiblerDivergenceFrom(attributeModel[1]);
  sourceDiv = packetSource.GetAverageKullbackLeiblerDivergenceFrom(attributeModel[2]);
  frequencyDiv = byteFrequency.GetAverageKullbackLeiblerDivergenceFrom(attributeModel[0]);
  offsetDiv = byteOffsets.GetAverageKullbackLeiblerDivergenceFrom(attributeModel[3]);
  dirNumSizeDiv = dirNumSize.GetAverageKullbackLeiblerDivergenceFrom(attributeModel[4]);
  dirFreqDiv = dirFreq.GetAverageKullbackLeiblerDivergenceFrom(attributeModel[5]);
  dirSizeDiv = dirSize.GetAverageKullbackLeiblerDivergenceFrom(attributeModel[6]);
  portNumberDiv = portNumber.GetAverageKullbackLeiblerDivergenceFrom(attributeModel[7]);
  // cout << "sizeDIV = " << sizeDiv << endl;
  // cout << "sourceDIV = " << sourceDiv << endl;
  // cout << "frequencyDIV = " << frequencyDiv << endl;
  // cout << "offsetDIV = " << offsetDiv << endl;
  sum = sizeDiv + sourceDiv + frequencyDiv + offsetDiv + dirNumSizeDiv + dirFreqDiv + dirSizeDiv + portNumberDiv;
  sum /= 7;
  return sum;

}

void ProtocolModel::MergeWith (ProtocolModel otherModel){
	packetSize.MergeWith(otherModel.packetSize);
	packetSource.MergeWith(otherModel.packetSource);
	byteFrequency.MergeWith(otherModel.byteFrequency);
	byteOffsets.MergeWith(otherModel.byteOffsets);
	dirNumSize.MergeWith(otherModel.dirNumSize);
	dirFreq.MergeWith(otherModel.dirFreq);
	dirSize.MergeWith(otherModel.dirSize);
	portNumber.MergeWith(otherModel.portNumber);
}

void ProtocolModel::MergeWith (double attributeModel[][512]){
	packetSize.MergeWith(attributeModel[1]);
	packetSource.MergeWith(attributeModel[2]);
	byteFrequency.MergeWith(attributeModel[0]);
	byteOffsets.MergeWith(attributeModel[3]);
	dirNumSize.MergeWith(attributeModel[4]);
	dirFreq.MergeWith(attributeModel[5]);
	dirSize.MergeWith(attributeModel[6]);
	portNumber.MergeWith(attributeModel[7]);
}

void ProtocolModel::reset(){
	packetSize.reset();
	packetSource.reset();
	byteFrequency.reset();
	byteOffsets.reset();
	dirNumSize.reset();
	dirFreq.reset();
	dirSize.reset();
	portNumber.reset();
}