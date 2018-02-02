#!/bin/bash


if [[ "$1" == "" || "$1" == "-h" ]]; then
	printf "USAGE: ./performanceTest.sh [-m(atching) | -s(pid)] [PCAP] [ExecutionNumber]\n"
	printf "\t\n"
	echo "Please provide the binary and pcap locations"
	exit 1
fi

rm -r PERFORMANCE_RESULTS
mkdir PERFORMANCE_RESULTS

BINARY="../DEMO/TCPStream file"
PCAP="$2"
TIMES="$3"
NAME="PERFORMANCE_RESULTS/`basename $2 .pcap`.csv"

if [[ "$1" == "-m" ]]; then
	TYPE="string-matching ../DEMO/configs/string-matching-config.txt"
	PTYPE="string-matching"
fi
if [[ "$1" == "-s" ]]; then
	TYPE="spid ../DEMO/configs/spid-config-testing.txt"
	PTYPE="SPID"
fi

for i in $(seq 1 $TIMES)
do

	TIME=$({ time $BINARY $TYPE $PCAP ; } 2>&1 | grep real | sed 's/real[ \t]//')
	MIN=$(echo "$TIME" | cut -d'm' -f1)
	SEC=$(echo $TIME | cut -d'm' -f2 | sed 's/s//')
	TOTTIME=$(bc -l <<< "$MIN*60+$SEC")

	SIZE=$(du -sm $PCAP | sed 's/[ \t].*//')
	THROUGHPUT=$(bc -l <<< "$SIZE/$TOTTIME")
	BANDWIDTH=$(bc -l <<< "$THROUGHPUT*8")

	if [ ! -f $NAME ]
	then
	    touch $NAME
	    printf "Binary,Pcap,Time(s),Size(mb),Throughput(mb/s),Bandwidth(MBit/s)\n" >> $NAME
	fi


	printf "%s,%s,%s,%s,%s,%s\n" "$PTYPE" "$PCAP" "$TOTTIME" "$SIZE" "$THROUGHPUT" "$BANDWIDTH" >> $NAME
done