#pragma once 

#include <iostream>
#include "protocolModel.h"
#include <limits>
#include <fstream>
#include <stdlib.h>


using namespace std;

void addData (const byte packetData[], int packetDirection, const unsigned long packetLength);
void writeToFile (string filename);
void readProbabilityVector (string filename);
void readCounterVector(string filename);
void compareProtocols();
void mergeWithModel(string filename);