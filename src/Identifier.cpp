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

    // Keep the payloads so that in `on_stream_closed` we can print the
    // payloads for the entire stream to files
    stream.auto_cleanup_payloads(false);

    stream.client_data_callback(std::bind(&Identifier::on_client_data, this, _1));
    stream.server_data_callback(std::bind(&Identifier::on_server_data, this, _1));
}

void Identifier::on_client_data(Stream& stream) {

    unsigned int i;
    const vector<uint8_t> payload = stream.client_payload();

    string appLayerProtocol = identify_protocol(payload);

    // Uncomment if you'd like to print out packets that weren't identified
    //
    cout << "Application layer protocol identified: " << appLayerProtocol << endl;
    // for (i = 0; i < payload.size(); i++) {
    //     cout << payload[i];
    // }

    if (appLayerProtocol != "Unknown") {
        cout << "Application layer protocol identified: " << appLayerProtocol << endl;
        // for (i = 0; i < payload.size(); i++) {
        //     cout << payload[i];
        // }
    }

    cout << endl;
}

void Identifier::on_server_data(Stream& stream) {

    unsigned int i;
    const vector<uint8_t> payload = stream.server_payload();

    string appLayerProtocol = identify_protocol(payload);

    // Uncomment if you'd like to print out packets that weren't identified
    //
    // cout << "Application layer protocol identified: " << appLayerProtocol << endl;
    // for (i = 0; i < payload.size(); i++) {
    //     cout << payload[i];
    // }

    if (appLayerProtocol != "Unknown") {
        cout << "Application layer protocol identified: " << appLayerProtocol << endl;
        // for (i = 0; i < payload.size(); i++) {
        //     cout << payload[i];
        // }
    }

    cout << endl;
}
