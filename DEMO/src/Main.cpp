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

const char* usageText = R"(NAME
        shitty_wireshark - a module to identify application layer protocols
            used in TCP streams and parse them

SYNOPSIS
        shitty_wireshark [OPTION...] MODE APPROACH CONFIG SOURCE
        shitty_wireshark [-h|--help]
        shitty_wireshark [-i|--individual] MODE APPROACH CONFIG SOURCE
        shitty_wireshark --print-packets MODE APPROACH CONFIG SOURCE

DESCRIPTION
        MODE
            live - Capture TCP streams on a network device. Runs until killed.
            file - Read TCP stream from a PCAP file. Exits when all streams
                have been read.

        APPROACH
            string-matching - Use string-matching to identify which application
                layer protocol a packet or stream is
            spid - Use the SPID algorithm to identify which application layer
                protocol a packet or stream is.

        CONFIG
            Must be a path to a user-made config file that is used by the
            chosen approach. There are no defaults. Each approach has unique
            formatting requirements for their config files. These requirements
            are outlined in a section below.

        SOURCE
            If MODE is live, then SOURCE must be the name of a network device
                on the machine. These names can be found by running the command
                `ifconfig` in a terminal.
            If MODE is file, then SOURCE must be a path to a PCAP file.

CONFIGURATION
        Each approach reads from a config file. The purpose of the config file
        is to allow the user to specify which application layer protocols
        should be identified, as well as how to identify them. This means
        different things for each approach.

        String Matching
            The string matching approach looks for a string in the contents of
            a stream or packet. Each string is associated with an application
            layer protocol. When a match is found in a packet or stream, it is
            identified as the protocol that is associated with that string.
            Therefore the user must specify two things in the config file for
            the string matching approach: a list of protocols that can be
            identified, and a list of strings associated with each protocol to
            look for. The user can specify such things in the following format:

            PROTOCOL:STRING,STRING,STRING,...,STRING
            PROTOCOL:STRING,STRING,STRING,...,STRING
            .
            .
            .

            For example, a config file that tries to identify HTTP streams by
            looking for the string "HTTP/1.1" in them would look like this:

            HTTP:HTTP/1.1

        SPID
            Statistical Protocol IDentification (SPID) creates a model of each
            protocol using existing PCAPS that have already been filtered for
            specific protocol.  This method will then create a new model for each
            stream as it receives packet data.  The current model is then compared
            to each protocol model using a modified version of the Kullback-Leibler
            divergence.  The algorithm picks the protocol with the lowest divergence,
            provided it passes a predetermined threshold, and passes the packets to 
            the parser.  In the config file the user must specify the Protocol,
            a PCAP containing data from that protocol, and a destination file for 
            the model.

            PROTOCOL:PCAP LOCATION;MODEL DESTINATION
            .
            .
            .

            For example:
            
            HTTP:PCAPS/HTTP.pcap;SpidModels/HTTP.txt

EXAMPLES
        shitty_wireshark live string-matching myConfig.txt eth0
            Capture all TCP streams on the network device eth0 and identify them
            using the string-matching approach

        shitty_wireshark file spid myConfig.txt myPcapFile.pcap
            Find all TCP streams in myPcapFile.pcap and identify them using SPID

        shitty_wireshark -i file spid myConfig.txt myPcapFile.pcap
            Same as above, but identify each packet in each stream individually
            instead of just processing the stream in its entirety

        shitty_wireshark --print-packets file spid myConfig.txt myPcapFile.pcap
            Same as second example, but print the contents of every packet after
            identifying it

        shitty_wireshark -h
            Print this help text

OPTIONS
   General options
       -h, --help
              Print this help text

   Control Options
       -i, --individual
              Process packets individually instead of processing streams as a
              whole

   Debugging options
           --print-packets
           	  Print the contents of each packet after processing it
)";

char* argString;

int main(int argc, char *argv[]) {

	argString = argv[0];

	bool printPackets = false;
	bool processPacketsIndividually = false;

	int arg = 1;
	string currentArg = argv[arg];

	while (currentArg.size() > 0 && currentArg[0] == '-') {

		if (currentArg == "--print-packets") {
			printPackets = true;
		} else if (currentArg == "-i" || currentArg == "--individual") {
			processPacketsIndividually = true;
		} else if (currentArg == "-h" || currentArg == "--help") {
			cout << usageText;
			return -1;
		} else {
			cerr << "Error: Unrecognized argument: " << currentArg << endl;
			cerr << endl;
			cout << usageText;
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
		identifier->configure(configFileArg, printPackets, processPacketsIndividually);

		// Set up the new stream callback
		follower.new_stream_callback(std::bind(&StringMatchingIdentifier::on_new_stream, identifier, _1));

	} else if (approachArg == "spid") {

		// Instantiate an identifier that uses our specific approach
		SpidIdentifier* identifier = new SpidIdentifier;

		// Configure the identifier using the config file
		identifier->configure(configFileArg, printPackets, processPacketsIndividually);

		// Set up the new stream callback
		follower.new_stream_callback(std::bind(&SpidIdentifier::on_new_stream, identifier, _1));

	} else {
		cout << usageText;
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
		cout << usageText;
		return -1;
	}
}
