#include <iostream>
#include <string>
#include <vector>

#include "Identifier.h"

using namespace std;

class StringMatchingIdentifier : public Identifier
{
protected:
	vector<unsigned char*> packets;

public:
	StringMatchingIdentifier();
	~StringMatchingIdentifier();

    /**
     * Called for each line in the config file. Use this function to actually
     * do the parsing of your config file.
     */
    void handleConfigFileLine(string line, int i);

    /** Identify the given packet. */
    string identify(unsigned char*);
};