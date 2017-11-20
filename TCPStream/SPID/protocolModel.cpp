#include "protocolModel.h"

using namespace std;


ProtocolModel::ProtocolModel(){
	trainingSessionCount = 0;
	observationCount = 0;
	AttributeFingerprintHandler packetSize = AttributeFingerprintHandler("size");
	AttributeFingerprintHandler packetSource = AttributeFingerprintHandler("direction");
	AttributeFingerprintHandler byteFrequency = AttributeFingerprintHandler("frequency");
	AttributeFingerprintHandler byteSequences = AttributeFingerprintHandler("sequences");
	AttributeFingerprintHandler byteOffsets = AttributeFingerprintHandler("offests");
}

void ProtocolModel::AddObservation (const byte packetData[], time_t packetTimestamp, int packetDirection){
  observationCount++;
  packetSize.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  packetSource.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  byteFrequency.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  byteSequences.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
  byteOffsets.AddObservation(packetData, packetTimestamp, packetDirection, observationCount);
}

double ProtocolModel::GetAverageKullbackLeiblerDivergenceFrom (ProtocolModel model){

}

ProtocolModel ProtocolModel::MergeWith (ProtocolModel otherModel){

}
