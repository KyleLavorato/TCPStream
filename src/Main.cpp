#include <iostream>
#include <functional>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>

#include "StringMatchingIdentifier.h"

using namespace Tins;
using namespace std;
using namespace std::placeholders;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

// TODO: Make options actually optional

void usage() {
	cerr << "Usage: shitty_wireshark OPTION CONFIG_FILE PCAP_FILE" << endl;
	cerr << endl;
	cerr << "CONFIG_FILE is the configuration file needed by the --approach you specified." << endl;
	cerr << "PCAP_FILE is the pcap file you're reading from." << endl;
	cerr << endl;
	cerr << "Miscellaneous:" << endl;
	cerr << "  -h, --help			display this help text and exit" << endl;
	cerr << endl;
	cerr << "Application layer protocol identification:" << endl;
	cerr << "      --approach=APPROACH	use APPROACH to identify application layer protocol;" << endl;
	cerr << "                           	APPROACH is 'spid', or 'string-matching'" << endl;
	cerr << endl;
	cerr << "Configuration file formats:" << endl;
	cerr << endl;
	cerr << "Each approach has a specific set of formatting rules for the config file. They" << endl;
	cerr << "are specified in this section." << endl;
	cerr << endl;
	cerr << "String Matching (--aproach=string-matching):" << endl;
	cerr << endl;
	cerr << "Each line defines a PROTOCOL, which is an application layer protocol you'd like" << endl;
	cerr << "to be able to identify, and a set of TOKENs, which are strings that are used" << endl;
	cerr << "to identify if a packet is of protocol PROTOCOL. Each protocol you'd like to" << endl;
	cerr << "identify gets one line in the config file. Each line should be formatted like" << endl;
	cerr << "so:" << endl;
	cerr << endl;
	cerr << "  PROTOCOL:TOKEN_1,TOKEN_2,TOKEN_3,...,TOKEN_n" << endl;
	cerr << endl;
	cerr << "Tokens cannot contain commas (a workaround for this could be a future addition" << endl;
	cerr << "to this software). Here is an example of identifying the HTTP protocol:" << endl;
	cerr << endl;
	cerr << "  HTTP:HTTP/1.1" << endl;
	cerr << endl;
	cerr << "Note that if ANY of the tokens are matched, then the packet is immediately" << endl;
	cerr << "identified as the protocol that token belongs to." << endl;

}

int main(int argc, char *argv[]) {
	
	// Check arguments for proper usage
	if (argc < 3) {
		usage();
		return -1;
	}

	string optionArg = argv[1];
	string configFileArg = argv[2];
	string pcapFileArg = argv[3];
	
	if (optionArg == "-h" || optionArg == "--help") {
		usage();
		return -1;
	}

	// Create our follower
	Tins::TCPIP::StreamFollower follower;

	// Set up the new stream callback with the approach specified on the
	// command line by the user using the --approach flag
	if (optionArg == "--approach=string-matching") {

		// Instantiate an identifier that uses our specific approach
		StringMatchingIdentifier* identifier = new StringMatchingIdentifier;

		// Configure the identifier using the config file
		identifier->configure(configFileArg);

		// Set up the new stream callback
		follower.new_stream_callback(std::bind(&StringMatchingIdentifier::on_new_stream, identifier, _1));

	} else if (optionArg == "--approach=spid") {
		cerr << "Error: SPID approach not yet implemented." << endl;
		return -1;
	} else {
		usage();
		return -1;
	}

	// Now create some sniffer
	FileSniffer sniffer(pcapFileArg);
	
	// And start sniffing, forwarding all packets to our follower
	sniffer.sniff_loop([&](PDU& pdu) {
		follower.process_packet(pdu);
		return true;
	});
}