#include "AttributeFingerprintHandler.h"

using namespace Tins;
using namespace std;
using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

AttributeFingerprintHandler::AttributeFingerprintHandler(){};

AttributeFingerprintHandler AttributeFingerprintHandler::AttributeFingerprintHandler(string name){
	Fingerprint attributeFingerprint;
	string attributeName = name;
	int counter = 0; // counter is the number of indices to be incremented. Will be calculated in GetMeasurements
}

void AttributeFingerprintHandler::AddObservation (byte[] packetData, DateTime packetTimestamp, PacketDirection packetDirection, int packetOrderNumberInSession){
  int* measurements;
  measurements = this.GetMeasurements(packetData,  packetTimestamp, packetDirection, packetOrderNumberInSession);
  for (int i = 0; i < counter; i++){
  	attributeFingerprint.IncrementFingerprintCounterAtIndex(int measurements[i]);
  }
}

double AttributeFingerprintHandler::GetAverageKullbackLeiblerDivergenceFrom (ProtocolModel model){

}

AttributeFingerprintHandler AttributeFingerprintHandler::MergerWith (ProtocolModel otherModel){

}

int* AttributeFingerprintHandler::GetMeasurements (byte[] packetData, DateTime packetTimestamp, PacketDirection packetDirection, int packetOrderNumberInSession){
	if this.attributeName == "size"{

	}
	else if this.attributeName == "direction"{

	}
	else if this.attributeName == "frequency"{

	}
	else if this.attributeName == "sequences"{

	}
	else if this.attributeName == "offset"{

	}
}