#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Identifier
{
protected:
    vector<unsigned char*> packets;

public:
    Identifier();
    ~Identifier();
    
    /**
     * Reads a config file and returns the lines of the file as a vector of 
     * strings.
     */
    void readConfigFile(string filepath);

    /** Reads a stream file and returns the packets in it in a vector. */
    void readStreamFile(string filepath);

    /** Accessor for the packets vector */
    vector<unsigned char*> get_packets();

    /**
     * Called for each line in the config file. Use this function to actually
     * do the parsing of your config file.
     */
    virtual void handleConfigFileLine(string line, int i) = 0;

    /** Identify the given packet. */
    virtual string identify(unsigned char*) = 0;

};
