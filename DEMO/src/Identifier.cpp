#include "Identifier.h"

void Identifier::configure(const string& filepath, bool printPackets, bool processPacketsIndividually) {

    string line;
    ifstream configFile;

    shouldPrintPackets = printPackets;
    shouldProcessPacketsIndividually = processPacketsIndividually;

    configFile.open(filepath);

    if (!configFile.is_open()) {
        cerr << "Error: Unable to open config file." << endl;
        throw runtime_error("Unable to open config file.");
    }

    int i = 0;

    while (getline(configFile, line)) {
        handle_config_file_line(line, i);
        i++;
    }

    configFile.close();
}

void Identifier::on_new_stream(Stream& stream) {

    // Don't get rid of client or server payloads, keep them so they can be
    // processed at the end of the stream
    stream.auto_cleanup_payloads(false);

    // Set the callbacks
    stream.client_data_callback(std::bind(&Identifier::on_client_data, this, _1));
    stream.server_data_callback(std::bind(&Identifier::on_server_data, this, _1));

    if (shouldProcessPacketsIndividually) {
        stream.stream_closed_callback(std::bind(&Identifier::on_stream_closed, this, _1));
    }
}

void Identifier::on_client_data(Stream& stream) {
    const vector<uint8_t> payload = stream.client_payload();
    if (shouldProcessPacketsIndividually) processPacket(payload);
    sendPacketToParser(payload, identify_protocol(payload));
}

void Identifier::on_server_data(Stream& stream) {
    const vector<uint8_t> payload = stream.server_payload();
    if (shouldProcessPacketsIndividually) processPacket(payload);
    sendPacketToParser(payload, identify_protocol(payload));
}

// TODO: Make this dynamic
//
// Send the packet to the parser if it's one of the recognized protocols.
// Right now this is hardcoded, but it should be made dynamic.
void Identifier::sendPacketToParser(vector<uint8_t> packet, string protocol) {
    if (protocol == "SAMBA") {
        parseData(packet.data(), packet.size(), SMB2_TYPE);
    } else if (protocol == "HTTP") {
        parseData(packet.data(), packet.size(), HTTP_TYPE);
    }
}

void Identifier::on_stream_closed(Stream& stream) {
    processPacket(stream.client_payload());
    processPacket(stream.server_payload());
}

void Identifier::processPacket(vector<uint8_t> packet) {

    // Identify the protocol for each stream using the custom approach
    string appLayerProtocol = identify_protocol(packet);
    cout << "protocol: " << appLayerProtocol << endl;

    // Print the packets if told to (this comes from a command line flag)
    if (shouldPrintPackets) {
        for (unsigned int i = 0; i < packet.size(); i++) {
            cout << packet[i];
        }
        cout << endl;
    }
}
