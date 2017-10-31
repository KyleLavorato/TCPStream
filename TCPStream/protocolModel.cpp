#include "protocolModel.h"

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

ProtocolModel::ProtocolModel(){};

ProtocolModel ProtocolModel::ProtocolModel(){
	trainingSessionCount = 0;
	observationCount = 0;
	AttributeFingerprintHandler packetSize = AttributeFingerprintHandler("size");
	AttributeFingerprintHandler packetDirection = AttributeFingerprintHandler("direction");
	AttributeFingerprintHandler byteFrequency = AttributeFingerprintHandler("frequency");
	AttributeFingerprintHandler byteSequences = AttributeFingerprintHandler("sequences");
	AttributeFingerprintHandler byteOffsets = AttributeFingerprintHandler("offests");
}

void ProtocolModel::AddObservation (byte[] packetData, DateTime packetTimestamp, PacketDirection packetDirection){
  this.observationCount++;
  packetSize.AddObsevation(packetData, packetTimestamp, packetDirection, observationCount);
  packetDirection.AddObsevation(packetData, packetTimestamp, packetDirection, observationCount);
  byteFrequency.AddObsevation(packetData, packetTimestamp, packetDirection, observationCount);
  byteSequences.AddObsevation(packetData, packetTimestamp, packetDirection, observationCount);
  byteOffsets.AddObsevation(packetData, packetTimestamp, packetDirection, observationCount);
}

double ProtocolModel::GetAverageKullbackLeiblerDivergenceFrom (ProtocolModel model){

}

ProtocolModel ProtocolModel::MergerWith (ProtocolModel otherModel){

}
