#include <iostream>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>
#include <tuple>

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

class Stream {
private:
	tuple <string, int, string, int, string> connections;
	int [][] packetSizeDistribution;
	int [][] packetDirectionDistribution;
	int [][] byteFrequency;
	int [][] reoccurringByteSequences;
	int [][] offsetsByteValues;
public:
	Stream (string ipAddress, int sourcePort, string destAddress, int destPort, string protocol);

}