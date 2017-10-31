#include <iostream>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>
#include <tuple>
#include "AttributeFingerprintHandler.h"

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

class ProtocolModel {
private:
public:
	ProtocolModel();
	ProtocolModel ProtocolModel();
	AddObservation (byte[] packetData, DateTime packetTimestamp, PacketDirection packetDirection);
	double GetAvergaeKullbackLeiblerDivergenceFrom (ProtocolModel model);
	ProtocolModel MergeWith(ProtocolModel otherModel);
	int trainingSessionCount;
	unsigned long observationCount;
}