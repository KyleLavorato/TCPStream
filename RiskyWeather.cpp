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

int main() {

	// Create our follower
	Tins::TCPIP::StreamFollower follower;

	// Set the callback for new streams. Note that this is a std::function, so you
	// could use std::bind and use a member function for this
	follower.new_stream_callback(&on_new_stream);

	// Now set up the termination callback. This will be called whenever a stream is 
	// stopped being followed for some of the reasons explained above
	follower.stream_termination_callback(&on_stream_terminated);

	// Now create some sniffer
	Sniffer sniffer("wlp2s0"); // Change this value to whatever interface you want (run `ifconfig`)

	// And start sniffing, forwarding all packets to our follower
	sniffer.sniff_loop([&](PDU& pdu) {
		follower.process_packet(pdu);
		return true;
	});
}
