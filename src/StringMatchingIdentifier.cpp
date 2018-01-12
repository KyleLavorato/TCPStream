#include "StringMatchingIdentifier.h"

void StringMatchingIdentifier::handle_config_file_line(string line, int i) {

    size_t pos = 0;

    // Get the protocol
    pos = line.find(":");
    string protocol = line.substr(0, pos);
    protocols.push_back(protocol);
    line.erase(0, pos + 1);

    cout << "Protocol: " << protocol << endl;

    // Get the strings to match for that protocol
    string stringToMatch;

    while ((pos = line.find(",")) != string::npos) {
        stringToMatch = line.substr(0, pos);
        cout << "String to match: " << stringToMatch << endl;
        stringsToMatch[protocol].push_back(stringToMatch);
        line.erase(0, pos + 1);
    }
}

string StringMatchingIdentifier::identify(unsigned char*) {

    /* TODO */

    return "Unknown";
}
