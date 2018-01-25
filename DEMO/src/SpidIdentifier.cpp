#include "SpidIdentifier.h"
#include "SpidInterface.h"

void SpidIdentifier::handle_config_file_line(string line, int i) {
    size_t pos = 0;

    // Get the protocol
    pos = line.find(":");
    string protocol = line.substr(0, pos);

    line.erase(0, pos + 1);

    // Get the strings to match for that protocol
    pos = line.find(";");
    string trainingFile = line.substr(0, pos);
    line.erase(0, pos + 1);
    string modelFile = line;

    // Store the protocol and the model file so that they're associated, so that
    // when we do the identifying we know which protocol is used with.
    protocolMap[protocol] = modelFile;

    SnifferConfiguration config;
    if (protocol == "HTTP"){
        config.set_filter("tcp port http");
    }
    else if (protocol == "FTP"){
        config.set_filter("tcp port ftp");
    }
    else if (protocol == "SAMBA"){
        config.set_filter("tcp port 139 || tcp port 445");
    }
    // Read the training file
    Tins::TCPIP::StreamFollower follower;
    FileSniffer sniffer(trainingFile, config);

    follower.new_stream_callback(&on_new_stream_training);

    // Start sniffing, forwarding all packets to our follower
    sniffer.sniff_loop([&](PDU& pdu) {
        follower.process_packet(pdu);
        return true;
    });

    // Write the model file
    writeToFile(modelFile);
    reset();
}

void on_new_stream_training(Stream& stream) {
    stream.auto_cleanup_payloads(false);
    stream.client_data_callback(&on_client_data_training);
    stream.server_data_callback(&on_server_data_training);
}

void on_client_data_training(Stream& stream) {
    const vector<uint8_t> payload = stream.client_payload();
    
    // Train
    if (payload.size() > 0)
        addData(payload.data(), 1, payload.size());
}

void on_server_data_training(Stream& stream) {
    const vector<uint8_t> payload = stream.server_payload();
    
    // Train
    if (payload.size() > 0)
        addData(payload.data(), 0, payload.size());    
}


string SpidIdentifier::identify_protocol() {

    // Creating new model based on given payload
    //addData(payload.data(), direction, payload.size());

    // Using model to identify protocol by comparing to models generated during
    // config
    return compareProtocols(protocolMap);
}

void SpidIdentifier::build_model(vector<uint8_t> payload, int direction){
    addData(payload.data(), direction, payload.size());
}

void SpidIdentifier::reset_model(){
    reset();
}