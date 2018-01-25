#include "Identifier.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <stdexcept>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>

using namespace Tins;
using namespace std;
using namespace std::placeholders;
using Tins::TCPIP::Stream;

void Identifier::configure(const string& filepath) {

    string line;
    ifstream configFile;

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

    // Set the server and client data callbacks
    stream.client_data_callback(std::bind(&Identifier::on_client_data, this, _1));
    stream.server_data_callback(std::bind(&Identifier::on_server_data, this, _1));
}

void Identifier::on_client_data(Stream& stream) {

    // Get the payload
    const vector<uint8_t> payload = stream.client_payload();

    // Identify the protocol using the custom approach
    string appLayerProtocol = identify_protocol(payload);

    // Print result
    cout << "Application layer protocol identified: " << appLayerProtocol << endl;

    // Send it to the parser if it's one of the recognized protocols. Right now
    // this is hardcoded, but it will be made dynamic.
    if (appLayerProtocol == "SAMBA") {
        parseData(payload.data(), payload.size(), SMB2_TYPE);
    } else if (appLayerProtocol == "HTTP") {
        parseData(payload.data(), payload.size(), HTTP_TYPE);
    }
}

void Identifier::on_server_data(Stream& stream) {

    // Get the payload
    const vector<uint8_t> payload = stream.server_payload();

    // Identify the protocol using the custom approach
    string appLayerProtocol = identify_protocol(payload);

    // Print result
    cout << "Application layer protocol identified: " << appLayerProtocol << endl;

    // Send it to the parser if it's one of the recognized protocols. Right now
    // this is hardcoded, but it will be made dynamic.
    if (appLayerProtocol == "SAMBA") {
        parseData(payload.data(), payload.size(), SMB2_TYPE);
    } else if (appLayerProtocol == "HTTP") {
        parseData(payload.data(), payload.size(), HTTP_TYPE);
    }
}
