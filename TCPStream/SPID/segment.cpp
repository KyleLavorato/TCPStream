#include <iostream>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>
#include "SPIDinterface.h"
#include "protocolModel.h"
#include <fstream>

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

ProtocolModel currentModel;

// This will be called when there's new client data
void on_client_data(Stream& stream) {
    int i;

    if (stream.is_partial_stream()) {
        cout << "Skipping partial stream" << endl;
        return;
    }

    // Get the client's payload, this is a vector<uint8_t>
    const Stream::payload_type& payload = stream.client_payload();

    // As per Kyle's request, call parseData from packet.h with the data and size
    // TODO: get the first argument here
    //parseData(argString, payload.data(), payload.size());
    cout << "Client data:" << endl;
    cout << payload.data() << endl;
    if (payload.size() > 0) {
        SPIDalgorithm(payload.data(), 1, currentModel);
    }


    //cout << "Client data:" << endl;

    //for (i = 0; i < payload.size(); i++) {
    //    cout << hex << payload[i];
    //}

    //cout << endl;
}

// This will be called when there's new server data
void on_server_data(Stream& stream) {
    int i;

    if (stream.is_partial_stream()) {
        cout << "Skipping partial stream" << endl;
        return;
    }

    const Stream::payload_type& payload = stream.client_payload();

    // As per Kyle's request, call parseData from packet.h with the data and size
    // TODO: get the first argument here
    //parseData(argString, payload.data(), payload.size());
    cout << "Server data:" << endl;
    cout << payload.size() << endl;
    if (payload.size() > 0) {
        SPIDalgorithm(payload.data(), 0, currentModel);
    }

    //cout << "Server data:" << endl;
    //for (i = 0; i < payload.size(); i++) {
    //    cout << hex << payload[i];
    //}
    cout << endl;
}

void writeToFile(){
    ofstream myFile;
    myFile.open ("SPIDmodels/FTP.txt");
    myFile << "Byte Frequency" << endl;
    for (int i = 0; i < 256; i++){
        myFile << currentModel.byteFrequency.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 256; i++){
        myFile << currentModel.byteFrequency.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
    }
    myFile << endl;
    myFile << "Size" << endl;
    for (int i = 0; i < 700; i++){
        myFile << currentModel.packetSize.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 700; i++){
        myFile << currentModel.packetSize.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
    }
    myFile << endl;
    myFile << "Direction" << endl;
    for (int i = 0; i < 2; i++){
        myFile << currentModel.packetSource.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 2; i++){
        myFile << currentModel.packetSource.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
    }
    myFile << endl;
    myFile << "Offset" << endl;
    for (int i = 0; i < 257; i++){
        myFile << currentModel.byteOffsets.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 257; i++){
        myFile << currentModel.byteOffsets.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
    }
    myFile << endl;
    myFile.close();
}

// A stream closed properly
void on_stream_closed(Stream& stream) {
    cout << "Stream from " << stream.client_addr_v4() << ":" << stream.client_port() << " to " << stream.server_addr_v4() << ":" << stream.server_port() << " closed" << endl;
    writeToFile();
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