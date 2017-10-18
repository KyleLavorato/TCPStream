#include <iostream>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

// A stream closed properly
void on_stream_closed(Stream& stream) {
	cout << "Stream closed." << endl;
}

// A stream was terminated. The second argument is the reason why it was terminated
void on_stream_terminated(Stream& stream, StreamFollower::TerminationReason reason) {
	cout << "Stream terminated." << endl;
}

// New stream is seen
void on_new_stream(Stream& stream) {
	stream.stream_closed_callback(&on_stream_closed);
	cout << "New stream started." << endl;
}