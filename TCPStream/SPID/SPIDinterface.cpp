#include <iostream>
#include "SPIDinterface.h"
#include "protocolModel.h"


void SPIDalgorithm(const byte packetData[], int packetDirection, ProtocolModel currentModel){
	cout <<"SPIDalgorithm begin"<<endl;
	//cout << packetData[0] << endl;
	string filename = "FTP.txt";
	time_t currentTime = time(0);
	//ProtocolModel currentModel;
	//cout <<"about to add observatoins" << endl;
	currentModel.AddObservation(packetData, currentTime, packetDirection);
	//cout << "addobservation end" << endl;
	//for (int i = 0; i < 2; i++){
	//	cout << "i " << i << endl;
	//	cout << currentModel.packetSource.attributeFingerprint.probabilityDistributionVector[i][0] << endl;;
	//}
	cout << "SPIDalgorithm end" << endl;
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



