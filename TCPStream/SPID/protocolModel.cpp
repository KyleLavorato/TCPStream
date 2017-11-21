#include "protocolModel.h"

using namespace std;


ProtocolModel::ProtocolModel(){
	cout << "begin protocolModel" << endl;
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
  cout << "adding observations" <<endl;
  packetSize.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  cout << "done size" <<endl;
  packetSource.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  cout << "done source"<<endl;
  byteFrequency.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  cout << "done frequency"<<endl;
  //byteSequences.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  byteOffsets.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  cout << "done offset" <<endl;
}

double ProtocolModel::GetAverageKullbackLeiblerDivergenceFrom (ProtocolModel model){

}

ProtocolModel ProtocolModel::MergeWith (ProtocolModel otherModel){

}
