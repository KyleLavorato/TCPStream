#include <iostream>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>
#include <tuple>

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

class lAttributeModel {
private:
public:
	string attributeName;
	int[] GetMeasurements(byte[] packetData, DateTime packetTimestamp, PacketDirection packetDirection, int packetOrderNumberInSession);
}