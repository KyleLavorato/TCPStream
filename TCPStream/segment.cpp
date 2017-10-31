#include <iostream>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

// This will be called when there's new client data
void on_client_data(Stream& stream) {

    if (stream.is_partial_stream()) {
        cout << "Skipping partial stream" << endl;
        return;
    }

    // Get the client's payload, this is a vector<uint8_t>
    const Stream::payload_type& payload = stream.client_payload();
    int i;

    cout << "Client data:" << endl;

    for (i = 0; i < payload.size(); i++) {
        cout << payload[i];
    }

    cout << endl;
}

// This will be called when there's new server data
void on_server_data(Stream& stream) {

    if (stream.is_partial_stream()) {
        cout << "Skipping partial stream" << endl;
        return;
    }

    const Stream::payload_type& payload = stream.client_payload();
    int i;

    cout << "Server data:" << endl;

    for (i = 0; i < payload.size(); i++) {
        cout << payload[i];
    }

    cout << endl;
}

// A stream closed properly
void on_stream_closed(Stream& stream) {
    cout << "Stream from " << stream.client_addr_v4() << ":" << stream.client_port() << " to " << stream.server_addr_v4() << ":" << stream.server_port() << " closed" << endl;
}

// A stream was terminated. The second argument is the reason why it was terminated
void on_stream_terminated(Stream& stream, StreamFollower::TerminationReason reason) {
    cout << "Stream terminated." << endl;
}

// New stream is seen
void on_new_stream(Stream& stream) {
    cout << "New stream from " << stream.client_addr_v4() << ":" << stream.client_port() << " to " << stream.server_addr_v4() << ":" << stream.server_port() << endl;

    stream.stream_closed_callback(&on_stream_closed);
    stream.client_data_callback(&on_client_data);
    stream.server_data_callback(&on_server_data);
}

