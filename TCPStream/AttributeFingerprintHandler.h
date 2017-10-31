#include <iostream>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>
#include <tuple>
#include "Fingerprint.h"
#include "lAttributeMeter.h"

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

class AttributeFingerprintHandler {
private:
	lAttributeMeter attributeMeter;
	Fingerprint attributeFingerprint;
	string attributeName;
public:
	AttributeFingerprintHandler();
	AttributeFingerprintHandler AttributeFingerprintHandler(string name);
	AddObservation (byte[] packetData, DateTime packetTimestamp, PacketDirection packetDirection, int packetOrderNumberInSession);
	double GetAvergaeKullbackLeiblerDivergenceFrom (AttributeFingerprintHandler model);
	AttributeFingerprintHandler MergeWith(Fingerprint otherFingerprint);
	int* GetMeasurements(byte[] packetData, DateTime packetTimestamp, PacketDirection packetDirection, int packetOrderNumberInSession);
}