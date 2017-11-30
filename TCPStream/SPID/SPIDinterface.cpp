#include "SPIDinterface.h"
#include <string>
#include <sstream>

double model[4][1500];
double inf = std::numeric_limits<double>::infinity();


ProtocolModel SPIDalgorithm(const byte packetData[], int packetDirection, ProtocolModel currentModel, const unsigned long packetLength){
	//cout <<"SPIDalgorithm begin"<<endl;
	//cout << packetData[0] << endl;
	string filename = "FTP.txt";
	time_t currentTime = time(0);
	//ProtocolModel currentModel;
	//cout <<"about to add observatoins" << endl;
	currentModel.AddObservation(packetData, currentTime, packetDirection, packetLength);
	//cout << "addobservation end" << endl;
	//for (int i = 0; i < 2; i++){
	//	cout << "i " << i << endl;
	//	cout << currentModel.packetSource.attributeFingerprint.probabilityDistributionVector[i][0] << endl;;
	//}
	//cout << "SPIDalgorithm end" << endl;
	return currentModel;
}

void writeToFile(string filename,const ProtocolModel currentModel){
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
    for (int i = 0; i < 1500; i++){
        myFile << currentModel.packetSize.attributeFingerprint.probabilityDistributionVector[i][0] << " ";
    }
    myFile << endl;
    for (int i = 0; i < 1500; i++){
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
    myFile.close();
}

void readFromFile(string filename){
    ifstream inFile;
    string x, y;
    int counter = 0;
    inFile.open(filename);
    if (!inFile) {
        cerr << "Unable to open file." << endl;
        exit(1);
    }
    for (int i = 0; i < 4; i++){
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

// string compareModel(string filename, double* currentResult, string potentialType, ProtocolModel currentModel){
// 	readFromFile(filename);
// 	double result;
// 	result = currentModel.GetAverageKullbackLeiblerDivergenceFrom(model);
//     //cout << "FTP comparison result = " << result << endl;
//     cout << "HERE" << endl;
//     if (result < 1 and result < *currentResult){
//     	cout << "NOW" << endl;
//         *currentResult = result;
//         return potentialType;
//         //streamType = "FTP";
//     }
// }

void compareProtocols(ProtocolModel currentModel){
    double result;
    double currentResult;
    bool flag = false;
    currentResult = inf;
    string streamType = "unidentified";
    //writeToFile("SPIDmodels/SMB.txt", currentModel);
    //streamType = compareModel("SPIDmodels/FTP.txt", currentResult, "FTP", currentModel);
    //streamType = compareModel("SPIDmodels/HTTP.txt", currentResult, "HTTP", currentModel);
    //streamType = compareModel("SPIDmodels/SMB.txt", currentResult, "SMB", currentModel);
    readFromFile("SPIDmodels/FTP.txt");
    result = currentModel.GetAverageKullbackLeiblerDivergenceFrom(model);
    cout << "FTP comparison result = " << result << endl;
    if (result < 1){
        currentResult = result;
        streamType = "FTP";
        flag = true;
    }
    readFromFile("SPIDmodels/HTTP.txt");
    result = currentModel.GetAverageKullbackLeiblerDivergenceFrom(model);
    cout << "HTTP comparison result = " << result << endl;
    if (result < 1 and result < currentResult){
        currentResult = result;
        streamType = "HTTP";
        flag = true;
    }
    readFromFile("SPIDmodels/SMB.txt");
    result = currentModel.GetAverageKullbackLeiblerDivergenceFrom(model);
    cout << "SMB comparison result = " << result << endl;
    if (result < 1 and result < currentResult){
        currentResult = result;
        streamType = "SMB";
        flag = true;
    }    
    cout << "Stream type is : " << streamType << endl;
    if (flag == true){
        //exit(1);
    }
}
