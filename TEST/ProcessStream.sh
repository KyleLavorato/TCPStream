#!/bin/bash

if [[ "$1" == "-h" ]]; then
	printf "Usage:\t./ProcessStream.sh\n"
	printf "\tThe script will evaluate the matching accuracy of TCPStream\n"
	printf "\tagainst all pcaps in TEST/PCAP/*.pcap\n"
	printf "The script will perform a clean compile of TCPStream\n"
	exit 1
fi

########## Preprocess Pcaps for Result Checking ##########

echo -en "                               \r"
echo -en "Preprocessing Pcaps\r"
echo -en '\n[                    ] 0%'
echo -en "\033[F\r"

# Delete old intermediate folder; create new
mkdir INTERMEDIATE
rm -r EXPECTED_RESULT
mkdir EXPECTED_RESULT
COUNT=0

for j in PCAP/*; do
	# Send follows to an intermediate folder
	END=$(tshark -r $j -T fields -e tcp.stream | sort -n | tail -1)
	for ((i=0;i<=END;i++))
	do
	    tshark -r $j -Y "tcp.stream eq $i" > INTERMEDIATE/$i.txt
	done

	tmpfile=$(mktemp /tmp/ProcessStream.XXXXXX)
	COUNT=0

	# Loop over all intermediates in folder
	for i in `ls -v INTERMEDIATE/*.txt`; do
		if grep -q "FTP" $i; then
			printf "$COUNT, FTP\n" >> $tmpfile
		elif grep -q "FTP-DATA" $i; then
			printf "$COUNT, FTP\n" >> $tmpfile
		elif grep -q "SMB" $i; then
			printf "$COUNT, SMB\n" >> $tmpfile
		elif grep -q "HTTP" $i; then
			printf "$COUNT, HTTP\n" >> $tmpfile
		else
			printf "$COUNT, FAILED\n" >> $tmpfile
		fi
		COUNT=$((COUNT+1))
		rm $i
	done

	# Write temp to file named same as pcap
	filename=`basename $j .pcapng`
	filename=`basename $filename .pcap`
	filename=`basename $filename .cap`
	cat $tmpfile > EXPECTED_RESULT/$filename.txt
	rm "$tmpfile"
done
rm -r INTERMEDIATE

########## End Preprocessing ##########

########## Build TCPStream ##########

echo -en "                               \r"
echo -en "Generating TCPStream Parsers\r"
echo -en '\n[####                ] 20%'
echo -en "\033[F\r"
#sleep 2

#cd ../DEMO/GENERATOR
#./translate.sh -q
#./interface.sh -q
#cd ../

echo -en "                               \r"
echo -en "Compiling TCPStream\r"
echo -en '\n[########            ] 40%'
echo -en "\033[F\r"

#make clean > /dev/null
#make > /dev/null
#cd ../TEST

########## End Build ##########

########## Process Pcaps with TCPStream ##########

echo -en "                               \r"
echo -en "Running TCPStream on Pcaps\r"
echo -en '\n[############        ] 60%'
echo -en "\033[F\r"

#rm -r ACTUAL_RESULT
#mkdir ACTUAL_RESULT

#for j in PCAP/*; do
	#../DEMO/shitty_wireshark -h > /dev/null
	#filename=`basename $j .pcapng`
	#filename=`basename $filename .pcap`
	#filename=`basename $filename .cap`
	#./shitty_wireshark > ACTUAL_RESULT/$filename.txt
#done

########## End Processing ##########

########## Results Calculation ##########

#sleep 2
echo -en "                               \r"
echo -en "Analyzing Results\r"
echo -en '\n[################    ] 80%'
echo -en "\033[F\r"

# Find number of errors between actual and expected
ERRORS=0
for j in ACTUAL_RESULT/*.txt; do
	RESULT=$(diff $j EXPECTED_RESULT/`basename $j` | grep "^>" | wc -l)
	ERRORS=$((ERRORS+RESULT))
done

# Find total number of streams
ATTEMPTS=0
for j in EXPECTED_RESULT/*.txt; do
	LINES=$(cat $j | wc -l)
	ATTEMPTS=$((ATTEMPTS+LINES))
done

# Find percent failed
PERCENT=$(awk "BEGIN { pc=100*${ERRORS}/${ATTEMPTS}; i=int(pc); print (pc) }")

# Find successes
SUCCESS=$((ATTEMPTS-FAILED))

echo -en "                               \r"
echo -en "Complete | Results Below\r"
echo -en '\n[####################] 100%'
echo -en '\n\n'
echo "Successful Matches: $SUCCESS"
echo "Identifications Failed: $ERRORS"
echo "Total Attempts: $ATTEMPTS"
printf "Failure Rate: %0.2f%%\n" $PERCENT

########## End Results ##########