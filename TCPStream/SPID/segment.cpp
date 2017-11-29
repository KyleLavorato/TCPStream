#include <iostream>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>
#include "SPIDinterface.h"
#include "protocolModel.h"
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

ProtocolModel currentModel;
double model[4][1500];
double inf = std::numeric_limits<double>::infinity();

// This will be called when there's new client data
void on_client_data(Stream& stream) {
    int i;
    ProtocolModel tempModel;

    if (stream.is_partial_stream()) {
        cout << "Skipping partial stream" << endl;
        return;
    }

    // Get the client's payload, this is a vector<uint8_t>
    const Stream::payload_type& payload = stream.client_payload();

    // As per Kyle's request, call parseData from packet.h with the data and size
    // TODO: get the first argument here
    //parseData(argString, payload.data(), payload.size());
    //cout << "Client data:" << endl;
    //cout << payload.data() << endl;

     //cout << "Client data:" << endl;
     //cout << payload.size() << endl;


    if (payload.size() > 0) {
        tempModel = SPIDalgorithm(payload.data(), 1, tempModel, payload.size());
        currentModel.MergeWith(tempModel);
    }



    // for (i = 0; i < payload.size(); i++) {
    //    cout << hex << payload[i];
    // }

    // cout << endl;
}

// This will be called when there's new server data
void on_server_data(Stream& stream) {
    int i;
    ProtocolModel tempModel;

    if (stream.is_partial_stream()) {
        cout << "Skipping partial stream" << endl;
        return;
    }

    const Stream::payload_type& payload = stream.server_payload();

    // As per Kyle's request, call parseData from packet.h with the data and size
    // TODO: get the first argument here
    //parseData(argString, payload.data(), payload.size());
    //cout << "Server data:" << endl;
    //cout << payload.size() << endl;

    //cout << "Server data:" << endl;
    //cout << payload.size() << endl;

    if (payload.size() > 0) {
        tempModel = SPIDalgorithm(payload.data(), 0, tempModel, payload.size());
        currentModel.MergeWith(tempModel);
    }

/*    cout << "Server data:" << endl;
    for (i = 0; i < payload.size(); i++) {
        cout << hex << payload[i];
    }
    cout << endl;*/
}

void writeToFile(string filename){
    ofstream myFile;
    myFile.open (filename);
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
    for (int i = 0; i < 1500; i++){
        myFile << currentModel.packetSize.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 1500; i++){
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

void readFromFile(string filename){
    //double model[4][700];
    ifstream inFile;
    string x, y;
    int counter = 0;
    inFile.open(filename);
    if (!inFile) {
        cerr << "Unable to open file." << endl;
        exit(1);
    }
    for (int i = 0; i < 4; i++){
        getline(inFile, x);
        getline(inFile, x);
        getline(inFile, x);
        istringstream iss(x);
        counter = 0;
        while (getline(iss, y, ' ')){
            //cout << y << ' ';
            model[i][counter] = stod(y);
            counter ++;
        }
        //cout << endl;
    }
    inFile.close();
}

void compareProtocols(){
    double result, currentResult;
    currentResult = inf;
    string streamType = "unidentified";
    //writeToFile("SPIDmodels/HTTP.txt");
    readFromFile("SPIDmodels/FTP.txt");
    result = currentModel.GetAverageKullbackLeiblerDivergenceFrom(model);
    if (result < 5){
        currentResult = result;
        streamType = "FTP";
    }
    readFromFile("SPIDmodels/HTTP.txt");
    result = currentModel.GetAverageKullbackLeiblerDivergenceFrom(model);
    if (result < 5 and result < currentResult){
        currentResult = result;
        streamType = "HTTP";
    }
    cout << "Stream type is : " << streamType << endl;
}

// A stream closed properly
void on_stream_closed(Stream& stream) {
    //cout << "Stream from " << stream.client_addr_v4() << ":" << stream.client_port() << " to " << stream.server_addr_v4() << ":" << stream.server_port() << " closed" << endl;
    //writeToFile();
    compareProtocols();
}

// A stream was terminated. The second argument is the reason why it was terminated
void on_stream_terminated(Stream& stream, StreamFollower::TerminationReason reason) {
    cout << "Stream terminated." << endl;
}

// New stream is seen
void on_new_stream(Stream& stream) {
    //cout << "New stream from " << stream.client_addr_v4() << ":" << stream.client_port() << " to " << stream.server_addr_v4() << ":" << stream.server_port() << endl;

    stream.stream_closed_callback(&on_stream_closed);
    stream.client_data_callback(&on_client_data);
    stream.server_data_callback(&on_server_data);
}