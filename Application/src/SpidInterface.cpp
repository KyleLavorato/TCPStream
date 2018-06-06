
#include "SpidInterface.h"
#include <string>
#include <sstream>
#include <math.h>

double model[8][512];
double inf = std::numeric_limits<double>::infinity();
ProtocolModel currentModel;

// TODO: Don't have the threshold hardcoded. Maybe put this in the config file?
double threshold = 2.0;


void addData(const byte packetData[], int packetDirection, const unsigned long packetLength, int portNum){
	time_t currentTime = time(0);
	currentModel.AddObservation(packetData, currentTime, packetDirection, packetLength, portNum);
}

void readCounterVector(string filename){
	ifstream inFile;
    string x, y;
    int counter = 0;
    inFile.open(filename);
    if (!inFile) {
        cerr << "Unable to open file." << endl;
        exit(1);
    }
    for (int i = 0; i < 8; i++){
        getline(inFile, x);
        getline(inFile, x);
        istringstream iss(x);
        counter = 0;
        while (getline(iss, y, ' ')){
            //cout << y << ' ';
            model[i][counter] = stod(y);
            counter ++;
        }
        getline(inFile, x);
        //cout << endl;
    }
    inFile.close();
}

void writeToFile(string filename){
    ofstream myFile;

    // FIXME: Check if folder for file exists first
    myFile.open(filename);

    myFile << "Byte Frequency" << endl;
    for (int i = 0; i < 256; i++){
        myFile << currentModel.byteFrequency.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 256; i++){
        myFile << currentModel.byteFrequency.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
    }
    myFile << endl;
    myFile << "Size" << endl;
    for (int i = 0; i < 300; i++){
        myFile << currentModel.packetSize.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 300; i++){
        myFile << currentModel.packetSize.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
    }
    myFile << endl;
    myFile << "Direction" << endl;
    for (int i = 0; i < 2; i++){
        myFile << currentModel.packetSource.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 2; i++){
        myFile << currentModel.packetSource.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
    }
    myFile << endl;
    myFile << "Offset" << endl;
    for (int i = 0; i < 257; i++){
        myFile << currentModel.byteOffsets.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 257; i++){
        myFile << currentModel.byteOffsets.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
    }
    myFile << endl;
    myFile << "DirNumSize" << endl;
    for (int i = 0; i < 260; i++){
        myFile << currentModel.dirNumSize.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 260; i++){
        myFile << currentModel.dirNumSize.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
    }
    myFile << endl;
    myFile << "DirFreq" << endl;
    for (int i = 0; i < 512; i++){
        myFile << currentModel.dirFreq.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 512; i++){
        myFile << currentModel.dirFreq.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
    }
    myFile << endl;
    myFile << "DirSize" << endl;
    for (int i = 0; i < 300; i++){
        myFile << currentModel.dirSize.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 300; i++){
        myFile << currentModel.dirSize.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
    }
    myFile << endl;
    myFile << "PortNumber" << endl;
    for (int i = 0; i < 512; i++){
        myFile << currentModel.portNumber.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 512; i++){
        myFile << currentModel.portNumber.attributeFingerprint.probabilityDistributionVector[i][1] << " ";
    }
    myFile << endl;
    myFile.close();
}

void readProbabilityVector(string filename){
    ifstream inFile;
    string x, y;
    int counter = 0;
    inFile.open(filename);
    if (!inFile) {
        cerr << "Unable to open file." << endl;
        exit(1);
    }
    for (int i = 0; i < 8; i++){
        getline(inFile, x);
        getline(inFile, x);
        getline(inFile, x);
        istringstream iss(x);
        counter = 0;
        while (getline(iss, y, ' ')){
            //cout << y << ' ';
            model[i][counter] = stod(y);
            counter ++;
        }
        //cout << endl;
    }
    inFile.close();
}

string compareProtocols(map<string, string> protocolMap){
    double result;
    double currentResult;

    currentResult = inf;
    string streamType = "Unknown";

    string protocol;
    string modelFile;

    for (const auto &myPair : protocolMap) {
        protocol = myPair.first;
        modelFile = myPair.second;

        // Set up global `model`
        readProbabilityVector(modelFile);

        // Get the divergence between the current model and the model built up from
        // the files
        result = currentModel.GetAverageKullbackLeiblerDivergenceFrom(model);
        //cout << protocol << ": " << result << endl;
        // Lower is better
        if (result < threshold && result < currentResult){
            currentResult = result;
            streamType = protocol;
        }
    }

    return streamType;
}

void mergeWithModel(string filename){
	readCounterVector(filename);
	currentModel.MergeWith(model);
	writeToFile(filename);
	currentModel.reset();
}

void reset(){
    currentModel.reset();
}