#include <iostream>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>

#include "segment.h"
//#include "parser.h"
//#include "SPIDinterface.h"

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;
//char * argString;

int main(int argc, char *argv[]) {
	////// ARG CHECKS //////
	if (argc < 2 || argc > 2) {
		cerr << "Usage:" << endl;
		cerr << "./tcpstream <PCAP location>" << endl;
		return -1;
	}
	string stringArg = argv[1];
	if (stringArg == "-h") {
		cerr << "Usage:" << endl;
		cerr << "./tcpstream <PCAP location>" << endl;
		return -1;
	}
	//argString = argv[1];
	////// END ARG CHECKS //////


	// Create our follower
	Tins::TCPIP::StreamFollower follower;

	// Set the callback for new streams. Note that this is a std::function, so you
	// could use std::bind and use a member function for this
	follower.new_stream_callback(&on_new_stream);

	// Now set up the termination callback. This will be called whenever a stream is 
	// stopped being followed for some of the reasons explained above
	follower.stream_termination_callback(&on_stream_terminated);

	FileSniffer sniffer(stringArg);
	
	// And start sniffing, forwarding all packets to our follower
	sniffer.sniff_loop([&](PDU& pdu) {
		follower.process_packet(pdu);
		return true;
	});
}