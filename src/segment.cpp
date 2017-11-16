#include <iostream>
#include <fstream>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

void write_stream_file(
    unsigned char* client_payload,
    const int client_len,
    unsigned char* server_payload,
    const int server_len,
    char* filename
) {
    ofstream myfile;
    myfile.open(filename);
    myfile << "********** Client Payloads **********\n";
    myfile.write((char*)client_payload, client_len);
    myfile << "\n********** Server Payloads **********\n";
    myfile.write((char*)server_payload, server_len);
    myfile.close();
}

// From https://stackoverflow.com/a/440240 because I'm lazy
void gen_random_string(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

// A stream closed properly
void on_stream_closed(Stream& stream) {
    const char* folder = "streams/";
    const char* extension = ".txt";

    int length = 6;
    char filename[6];

    gen_random_string(filename, length);

    char full_path[19];

    strcpy(full_path, folder);
    strcat(full_path, filename);
    strcat(full_path, extension);

    write_stream_file(
        stream.client_payload().data(),
        stream.client_payload().size(),
        stream.server_payload().data(),
        stream.server_payload().size(),
        full_path
    );
}

// New stream is seen
void on_new_stream(Stream& stream) {

    // Keep the payloads so that in `on_stream_closed` we can print the
    // payloads for the entire stream to files
    stream.auto_cleanup_payloads(false);

    stream.stream_closed_callback(&on_stream_closed);
}


