#include <tins/tins.h>
#include <iostream>
#include <stddef.h>

#include "segment.h"

using namespace std;
using namespace Tins;

size_t counter(0);

bool count_packets(const PDU &) {
    counter++;
    // Always keep looping. When the end of the file is found, 
    // our callback will simply not be called again.
    return true;
}

int main(int argc, char *argv[]) {
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

	try {
		FileSniffer sniffer(stringArg);

		// Here you would call a function saved in the segment.c file instead of count_packets in the sniff loop

		sniffer.sniff_loop(count_packets);
    	cout << "There are " << counter << " packets in the pcap file\n";
	} catch (Tins::pcap_error& e) {
		cerr << "Invalid pcap location" << endl; 
		return -1;
	}
}