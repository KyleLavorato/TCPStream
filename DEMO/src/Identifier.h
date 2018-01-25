#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>

#include "Parser.h"

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;

class Identifier
{

public:

    /**
     * Reads the given config file and uses internal configuration strategy
     * specified in the handle_config_line method.
     */
    void configure(const string& filepath);

    /** When a new stream is seen */
    void on_new_stream(Stream& stream);

    /** When new client data arrives */
    void on_client_data(Stream& stream);

    /** When new server data arrives */
    void on_server_data(Stream& stream);

    /** When stream is closed */
    void on_stream_closed(Stream& stream);

    /** Identify the given packet. */
    virtual void build_model(vector<uint8_t> payload, int direction) = 0;

    virtual string identify_protocol();

    virtual void reset_model();


private:
    
    /**
     * Called for each line in the config file. Use this function to actually
     * do the parsing of your config file.
     */
    virtual void handle_config_file_line(string line, int i) = 0;

};
