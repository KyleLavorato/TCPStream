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
    
    void readConfigFile(string filepath) {
        string line;
        ifstream configFile;
        configFile.open(configFileName);
        if (!configFile.is_open()) {
            cerr << "Error: Unable to open config file." << endl;
            throw new Error("Unable to open config file.");
        }
        int i = 0;
        while (getline(configFile, line)) {
            this.handleConfigFileLine(line, i);
            i++;
        }
        configFile.close();
    }

    void readStreamFile(string filepath) {
        const string CLIENT_HEADER = "********** Client Payloads **********";
        const string SERVER_HEADER = "********** Server Payloads **********";
        unsigned char* line;
        ifstream streamFile;
        streamFile.open(filepath);
        if (!streamFile.is_open()) {
            cerr << "Error: Unable to open stream file." << endl;
            throw new Error("Unable to open stream file.");
        }
        while (getline(streamFile, line)) {
            if (line == CLIENT_HEADER || line == SERVER_HEADER) { continue; }

            /*
             * TODO
             *
             * Here we need to store each packet into `this.packets`. We need a
             * way of separating the packets from each other when reading from
             * the stream file. We know that a single packet can extend over 
             * several lines, so using \n as a delimiter won't work. We could
             * try looking for two \n's in a row though.
             */

            cout << line << endl;
        }
        streamFile.close();
    }

    vector<unsigned char*> get_packets() {
        return this.packets;
    }
};
