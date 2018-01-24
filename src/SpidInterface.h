#pragma once 

#include <iostream>
#include "ProtocolModel.h"
#include <limits>
#include <fstream>
#include <stdlib.h>
#include <map>


using namespace std;

void addData (const byte packetData[], int packetDirection, const unsigned long packetLength);
void writeToFile (string filename);
void readProbabilityVector (string filename);
void readCounterVector(string filename);
string compareProtocols(map<string, string> protocolMap);
void mergeWithModel(string filename);
void reset();