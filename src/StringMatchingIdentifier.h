#include <iostream>
#include <string>
#include <vector>

#include "Identifier.h"

using namespace std;

class StringMatchingIdentifier : public Identifier
{

public:

    /** Identify the given packet. */
    string identify(unsigned char*);


private:

    vector<string> protocols;
    map<string, vector<string>> stringsToMatch;

    void handle_config_file_line(string line, int i);

};