#include "StringMatchingIdentifier.h"

void StringMatchingIdentifier::handle_config_file_line(string line, int i) {

    size_t pos = 0;

    // Get the protocol
    pos = line.find(":");
    string protocol = line.substr(0, pos);
    protocols.push_back(protocol);
    line.erase(0, pos + 1);

    // Get the strings to match for that protocol
    string token;

    while ((pos = line.find(",")) != string::npos) {
        token = line.substr(0, pos);
        tokens[protocol].push_back(token);
        line.erase(0, pos + 1);
    }

    // Handle the last case so we don't require a trailing comma in the config
    // file on each line
    token = line;
    tokens[protocol].push_back(token);
    line.erase(0, pos + 1);
}

string StringMatchingIdentifier::identify_protocol(vector<uint8_t> payload) {

    unsigned int i, j;
    string payload_as_string;

    // Convert the payload to a string so we can use the string::find() method
    // for the substring search
    for (i = 0; i < payload.size(); i++) {
        payload_as_string.push_back((char)payload[i]);
    }

    for (i = 0; i < protocols.size(); i++) {
        string protocol = protocols[i];

        for (j = 0; j < tokens[protocol].size(); j++) {
            string token = tokens[protocol][j];

            // Could use Knuth-Morris-Pratt, or use the built-in find which might
            // use that anyway, if not something better
            if ((payload_as_string).find(token) != string::npos) {
                return protocol;
            }
        }
    }

    return "Unknown";
}
