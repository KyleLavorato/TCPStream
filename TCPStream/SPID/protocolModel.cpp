#include "protocolModel.h"

using namespace std;


ProtocolModel::ProtocolModel(){
	//cout << "begin protocolModel" << endl;
	trainingSessionCount = 0;
	observationCount = 0;
	packetSize = AttributeFingerprintHandler("size");
	packetSource = AttributeFingerprintHandler("direction");
	byteFrequency = AttributeFingerprintHandler("frequency");
	//byteSequences = AttributeFingerprintHandler("sequences");
	byteOffsets = AttributeFingerprintHandler("offset");
}

void ProtocolModel::AddObservation (const byte packetData[], time_t packetTimestamp, int packetDirection){
  observationCount++;
  //cout << "adding observations" <<endl;
  packetSize.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  //cout << "done size" <<endl;
  packetSource.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  //cout << "done source"<<endl;
  byteFrequency.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  //cout << "done frequency"<<endl;
  //byteSequences.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  byteOffsets.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  //cout << "done offset" <<endl;
  // cout << "Byte frequency" << endl;
  // for (int i = 0; i < 2; i++){
  //     cout << packetSource.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
  // }
  // cout << endl;
  // for (int i = 0; i < 2; i++){
  //     cout << packetSource.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
  // }
}

double ProtocolModel::GetAverageKullbackLeiblerDivergenceFrom (double attritbuteModel[][700]){
  double sizeDiv, sourceDiv, frequencyDiv, offsetDiv, sum;
  sizeDiv = packetSize.GetAverageKullbackLeiblerDivergenceFrom(attritbuteModel[1]);
  cout << "sizeDIV = " << sizeDiv << endl;
  sourceDiv = packetSource.GetAverageKullbackLeiblerDivergenceFrom(attritbuteModel[2]);
  cout << "sourceDIV = " << sourceDiv << endl;
  frequencyDiv = byteFrequency.GetAverageKullbackLeiblerDivergenceFrom(attritbuteModel[0]);
  cout << "frequencyDIV = " << frequencyDiv << endl;
  offsetDiv = byteOffsets.GetAverageKullbackLeiblerDivergenceFrom(attritbuteModel[3]);
  cout << "offsetDIV = " << offsetDiv << endl;
  sum = sizeDiv + sourceDiv + frequencyDiv + offsetDiv;
  return sum;

}

void ProtocolModel::MergeWith (ProtocolModel otherModel){
	packetSize.MergeWith(otherModel.packetSize);
	packetSource.MergeWith(otherModel.packetSource);
	byteFrequency.MergeWith(otherModel.byteFrequency);
	byteOffsets.MergeWith(otherModel.byteOffsets);
}
