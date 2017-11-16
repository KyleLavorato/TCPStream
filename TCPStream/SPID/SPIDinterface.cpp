#include <iostream>
#include "SPIDinterface.h"
#include "protocolModel.h"

ProtocolModel currentModel;

void SPIDalgorithm(char *progname, byte packetData[], int packetDirection){
	string filename = "FTP.txt";
	time_t currentTime = time(0);

	currentModel.AddObservation(packetData, currentTime, packetDirection);
	for (int i = 0, i < 2; i++){
		cout << currentModel.packetSource.attributeFingerprint.probabilityDistributionVector[i][0];
	}
	count << endl;
}



	// //data to be used in SPID algorithm
	// time_t currentTime = time(0);
	// int packetDirection = 1;
	// int length = payload.size();
	// byte packetData [length];
	// for (i = 0; i < payload.size(); i++){
	// 	packetData[i] = payload[i];
	// }

	// currentModel.AddObservation(packetData, currentTime, packetDirection);



