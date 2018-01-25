#include <iostream>
#include <string>
#include <vector>

#include "Identifier.h"

using namespace std;

class SpidIdentifier : public Identifier
{

public:

    /** Identify the given packet. */
    string identify_protocol();
    void reset_model();
    void build_model(vector<uint8_t> payload, int direction);
    //string identify_protocol(vector<uint8_t> payload);


private:

    map<string, string> protocolMap;

    void handle_config_file_line(string line, int i);

};

void on_new_stream_training(Stream& stream);
void on_client_data_training(Stream& stream);
void on_server_data_training(Stream& stream);
