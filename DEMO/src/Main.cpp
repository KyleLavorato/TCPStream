#include <iostream>
#include <functional>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>

#include "StringMatchingIdentifier.h"
#include "SpidIdentifier.h"

using namespace Tins;
using namespace std;
using namespace std::placeholders;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

void usage() {
	cerr << "Usage: shitty_wireshark [OPTIONS ...] MODE APPROACH CONFIG_FILE PACKET_SOURCE" << endl;
	cerr << endl;
	cerr << "MODE is either 'live' or 'file' without the single quotes. In 'live' mode," << endl;
	cerr << "\tPACKET_SOURCE must be a valid network interface. Run `ifconfig` to see" << endl;
	cerr << "\twhat interfaces are available on your machine. When in 'file' mode, the" << endl;
	cerr << "\tPACKET_SOURCE must be a PCAP file that will be read from." << endl;
	cerr << endl;
	cerr << "APPROACH is either 'string-matching' or 'spid' without the single quotes." << endl;
	cerr << "\tSee respective sections below for detailed descriptions of which" << endl;
	cerr << "\tapproach to use and when." << endl;
	cerr << endl;
	cerr << "CONFIG_FILE is the configuration file needed by the APPROACH you specified." << endl;
	cerr << endl;
	cerr << "PACKET_SOURCE is either a network interface or a PCAP file, depending on" << endl;
	cerr << "\twhat MODE is set to." << endl;
	cerr << endl;
	cerr << "Miscellaneous:" << endl;
	cerr << "  -h, --help           display this help text and exit" << endl;
	cerr << "      --print-packets  print the contents of packets" << endl;
	// cerr << endl;
	// cerr << "Configuration file formats:" << endl;
	// cerr << endl;
	// cerr << "Each approach has a specific set of formatting rules for the config file. They" << endl;
	// cerr << "are specified in this section." << endl;
	// cerr << endl;
	// cerr << "String Matching:" << endl;
	// cerr << endl;
	// cerr << "Each line defines a PROTOCOL, which is an application layer protocol you'd like" << endl;
	// cerr << "to be able to identify, and a set of TOKENs, which are strings that are used" << endl;
	// cerr << "to identify if a packet is of protocol PROTOCOL. Each protocol you'd like to" << endl;
	// cerr << "identify gets one line in the config file. Each line should be formatted like" << endl;
	// cerr << "so:" << endl;
	// cerr << endl;
	// cerr << "  PROTOCOL:TOKEN_1,TOKEN_2,TOKEN_3,...,TOKEN_n" << endl;
	// cerr << endl;
	// cerr << "Tokens cannot contain commas (a workaround for this could be a future addition" << endl;
	// cerr << "to this software). Here is an example of identifying the HTTP protocol:" << endl;
	// cerr << endl;
	// cerr << "  HTTP:HTTP/1.1" << endl;
	// cerr << endl;
	// cerr << "Note that if ANY of the tokens are matched, then the packet is immediately" << endl;
	// cerr << "identified as the protocol that token belongs to." << endl;
}

char* argString;

int main(int argc, char *argv[]) {

	argString = argv[0];

	bool printPackets = false;

	int arg = 1;
	string currentArg = argv[arg];

	while (currentArg.size() > 0 && currentArg[0] == '-') {

		if (currentArg == "--print-packets") {
			printPackets = true;
		} else if (currentArg == "-h" || currentArg == "--help") {
			usage();
			return -1;
		} else {
			cerr << "Error: Unrecognized argument: " << currentArg << endl;
			cerr << endl;
			usage();
			return -1;
		}

		currentArg = argv[++arg];
	}

	const string& modeArg = argv[arg++];
	string approachArg = argv[arg++];
	string configFileArg = argv[arg++];
	string packetSourceArg = argv[arg++];

	// Create our follower
	Tins::TCPIP::StreamFollower follower;

	// Set up the new stream callback with the approach specified on the
	// command line by the user using the APPROACH argument
	if (approachArg == "string-matching") {

		// Instantiate an identifier that uses our specific approach
		StringMatchingIdentifier* identifier = new StringMatchingIdentifier;

		// Configure the identifier using the config file
		identifier->configure(configFileArg, printPackets);

		// Set up the new stream callback
		follower.new_stream_callback(std::bind(&StringMatchingIdentifier::on_new_stream, identifier, _1));

	} else if (approachArg == "spid") {

		// Instantiate an identifier that uses our specific approach
		SpidIdentifier* identifier = new SpidIdentifier;

		// Configure the identifier using the config file
		identifier->configure(configFileArg, printPackets);

		// Set up the new stream callback
		follower.new_stream_callback(std::bind(&SpidIdentifier::on_new_stream, identifier, _1));

	} else {
		usage();
		return -1;
	}

	if (modeArg == "live") {
		Sniffer sniffer(packetSourceArg); // packetSourceArg will be a PCAP file

		// Start sniffing, forwarding all packets to our follower
		sniffer.sniff_loop([&](PDU& pdu) {
			follower.process_packet(pdu);
			return true;
		});
	} else if (modeArg == "file") {
		FileSniffer sniffer(packetSourceArg); // packetSourceArg will be a network interface

		// Start sniffing, forwarding all packets to our follower
		sniffer.sniff_loop([&](PDU& pdu) {
			follower.process_packet(pdu);
			return true;
		});
	} else {
		usage();
		return -1;
	}
}
