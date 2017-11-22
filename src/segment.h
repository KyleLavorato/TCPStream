#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

// A stream closed properly
void on_stream_closed(Stream& stream);

// New stream is seen
void on_new_stream(Stream& stream);

// Writes the client and server payload data from a stream to a file
void write_stream_file(
    unsigned char* client_payload,
    const int client_len,
    unsigned char* server_payload,
    const int server_len,
    string filename
);

// Generates a random string
void gen_random_string(char *s, const int len);

// Checks if a folder exists or not
bool folder_exists(const char* name);
