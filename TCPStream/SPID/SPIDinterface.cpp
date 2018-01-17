#include "SPIDinterface.h"
#include <string>
#include <sstream>
#include <math.h>

double model[7][512];
double inf = std::numeric_limits<double>::infinity();
double threshold = 0.5;
ProtocolModel currentModel;


void addData(const byte packetData[], int packetDirection, const unsigned long packetLength){
	time_t currentTime = time(0);
	currentModel.AddObservation(packetData, currentTime, packetDirection, packetLength);
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
    for (int i = 0; i < 7; i++){
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
    myFile.open (filename);
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
    for (int i = 0; i < 7; i++){
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

void compareProtocols(){
    double result;
    double currentResult;
    bool flag = false;
    currentResult = inf;
    string streamType = "unidentified";
    readProbabilityVector("SPIDmodels/FTP.txt");
    result = currentModel.GetAverageKullbackLeiblerDivergenceFrom(model);
    result = fabs(result);
    cout << "FTP comparison result = " << result << endl;
    if (result < threshold){
        currentResult = result;
        streamType = "FTP";
        flag = true;
    }
    readProbabilityVector("SPIDmodels/HTTP.txt");
    result = currentModel.GetAverageKullbackLeiblerDivergenceFrom(model);
    cout << "HTTP comparison result = " << result << endl;
    if (result < threshold and result < currentResult){
        currentResult = result;
        streamType = "HTTP";
        flag = true;
    }
    readProbabilityVector("SPIDmodels/SMB.txt");
    result = currentModel.GetAverageKullbackLeiblerDivergenceFrom(model);
    cout << "SMB comparison result = " << result << endl;
    if (result < threshold and result < currentResult){
        currentResult = result;
        streamType = "SMB";
        flag = true;
    }    
    cout << "Stream type is : " << streamType << endl;
    if (flag == true){
        //exit(1);
    }
}

void mergeWithModel(string filename){
	readCounterVector(filename);
	currentModel.MergeWith(model);
	writeToFile(filename);
	currentModel.reset();
}