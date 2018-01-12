#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <tins/tcp_ip/stream_follower.h>
#include <tins/tins.h>

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

    /** When a stream closes successfully */
    void on_stream_closed(Stream& stream);

    /** Identify the given packet. */
    virtual string identify(unsigned char*) = 0;


private:
    
    /**
     * Called for each line in the config file. Use this function to actually
     * do the parsing of your config file.
     */
    virtual void handle_config_file_line(string line, int i) = 0;

};
