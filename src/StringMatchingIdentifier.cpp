#include "StringMatchingIdentifier.h"

class StringMatchingIdentifier : public Idenfier
{
private:
    vector<string> protocols;
    map<string, vector<string>> stringsToMatch;

public:
    StringMatchingIdentifier();
    ~StringMatchingIdentifier();
    
    void handleConfigFileLine(string line, int i) {

        size_t pos = 0;

        // Get the protocol
        pos = line.find(":");
        string protocol = line.substr(0, pos);
        this.protocols.push_back(protocol);
        line.erase(0, pos + 1);

        cout << "Protocol: " << protocol << endl;

        // Get the strings to match for that protocol
        string stringToMatch;

        while ((pos = line.find(",")) != string::npos) {
            stringToMatch = line.substr(0, pos);
            cout << "String to match: " << stringToMatch << endl;
            this.stringsToMatch[protocol].push_back(stringToMatch);
            line.erase(0, pos + 1);
        }   

    }

    string identify(unsigned char*) {

        /* TODO */

        return "Unknown";
    }
};