#pragma once 

#include <iostream>
#include "protocolModel.h"
#include <limits>
#include <fstream>
#include <stdlib.h>


using namespace std;

ProtocolModel SPIDalgorithm (const byte packetData[], int packetDirection, ProtocolModel currentModel, const unsigned long packetLength);
void writeToFile (string filename,const ProtocolModel currentModel);
void readFromFile (string filename);
void compareProtocols(ProtocolModel currentModel);
