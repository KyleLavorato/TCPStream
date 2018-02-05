#pragma once

#include "Parser.h"

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
using Tins::TCPIP::StreamFollower;

class Identifier
{

public:

    /**
     * Reads the given config file and uses internal configuration strategy
     * specified in the handle_config_line method.
     */
    void configure(const string& filepath, bool printPackets, bool processPacketsIndividually, string method);

    /** When a new stream is seen */
    void on_new_stream(Stream& stream);

    /** When a stream finishes */
    void handle_full_stream(Stream& stream);

    /** When a stream finishes */
    void handle_terminated_stream(Stream& stream, StreamFollower::TerminationReason reason);

    /** When new client data arrives */
    void on_client_data(Stream& stream);

    /** When new server data arrives */
    void on_server_data(Stream& stream);

    /** Send a packet to the parser to be processed */
    void sendPacketToParser(vector<uint8_t> packet, string protocol);

    /**
     * Identify and print out a packet's application layer procotol
     *
     * This is mainly used for demonstration purposes. Down the road, this
     * doesn't need to be here.
     */
    void processPacket(vector<uint8_t> packet);

    /** Identify the given packet. */
    virtual string identify_protocol(vector<uint8_t> payload) = 0;
    virtual void reset_model() = 0;
    virtual void handle_data(vector<uint8_t> payload, int dir, int port) = 0;


protected:

    /**
     * Flag to say whether you should print packets or not
     */
    bool shouldPrintPackets;

    /**
     * Flag to say whether you should process packets individually. The default
     * is to process the entire stream at once instead.
     */
    bool shouldProcessPacketsIndividually;

    /**
     * Keeps track of how many streams have been processed
     */
    unsigned int streamNum;

    /**
     * The approach that is being taken.  SPID requires some extra steps
     */
    string approach;


private:
    
    /**
     * Called for each line in the config file. Use this function to actually
     * do the parsing of your config file.
     */
    virtual void handle_config_file_line(string line, int i) = 0;

};
