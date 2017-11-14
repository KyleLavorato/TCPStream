#!/bin/bash


if [[ "$1" == "" || "$1" == "-h" ]]; then
	printf "USAGE: sh ../../performanceTest.sh ./pcapparse  ~/Development/LongStressTest.pcapng\n"
	printf "MAKE SURE YOU ARE IN YOUR OWN FOLDER SO PCAPPARSE CAN READ FACTS\n"
	printf "Usage:\t./performanceTest.sh [binary] [pcap] \n"
	printf "\t\n"
	echo "Please provide the binary and pcap locations"
	exit 1
fi

BINARY="$1"
PCAP="$2"

### 
for i in $*
do
	if [ "$i" == "" ]
	then
		CALLBACK="-nocallback"
		continue
   	fi
	
	if [ "$i" == "-nocallback" ]
	then
		CALLBACK="-nocallback"
		continue
   	fi
done
###

for i in {1..50}
do

	TIME=$({ time $BINARY $PCAP ; } 2>&1 | grep real | sed 's/real[ \t]//')
	MIN=$(echo "$TIME" | cut -d'm' -f1)
	SEC=$(echo $TIME | cut -d'm' -f2 | sed 's/s//')
	TOTTIME=$(bc -l <<< "$MIN*60+$SEC")

	SIZE=$(du -sm $PCAP | sed 's/[ \t].*//')
	THROUGHPUT=$(bc -l <<< "$SIZE/$TOTTIME")
	BANDWIDTH=$(bc -l <<< "$THROUGHPUT*8")

	if [ ! -f performance.csv ]
	then
	    touch performance.csv
	    printf "Binary,Pcap,Time(s),Size(mb),Throughput(mb/s),Bandwidth(MBit/s)\n" >> performance.csv
	fi


	printf "%s,%s,%s,%s,%s,%s\n" "$BINARY" "$PCAP" "$TOTTIME" "$SIZE" "$THROUGHPUT" "$BANDWIDTH" >> performance.csv
done