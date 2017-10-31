#include <iostream>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>
#include <tuple>

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

class Fingerprint {
private:
public:
	int[][] probabilityDistributionVector;
	Fingerprint ();
	Fingerprint Fingerprint();
	IncrementFingerprintCounterAtIndex(int index);
	Fingerprint MergeWith (Fingerprint otherFingerprint);
}