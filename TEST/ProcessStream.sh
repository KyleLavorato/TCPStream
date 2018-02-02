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
	COUNT=1

	# Loop over all intermediates in folder
	for i in `ls -v INTERMEDIATE/*.txt`; do
		if grep -q "FTP" $i; then
			printf "[$COUNT] protocol: FTP\n" >> $tmpfile
		elif grep -q "FTP-DATA" $i; then
			printf "[$COUNT] protocol: FTP\n" >> $tmpfile
		elif grep -q "SMB" $i; then
			printf "[$COUNT] protocol: SAMBA\n" >> $tmpfile
		elif grep -q "HTTP" $i; then
			printf "[$COUNT] protocol: HTTP\n" >> $tmpfile
		elif grep -q "TCP" $i; then
			:
		else
			printf "[$COUNT] protocol: FAILED\n" >> $tmpfile
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
#./makemake.sh -q
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

rm -r ACTUAL_RESULT
mkdir ACTUAL_RESULT

#../DEMO/TCPStream file string-matching ../DEMO/configs/string-matching-config.txt PCAP/our-ftp.pcap > ACTUAL_RESULT/AAA.txt

mkdir SpidModels
for j in PCAP/*; do
	filename=`basename $j .pcapng`
	filename=`basename $filename .pcap`
	filename=`basename $filename .cap`
	#echo ACTUAL_RESULT/$filename.txt
	#touch ACTUAL_RESULT/$filename_STRING.txt
	../DEMO/TCPStream file string-matching ../DEMO/configs/string-matching-config.txt $j > ACTUAL_RESULT/$filename-STRING.txt
	../DEMO/TCPStream file spid ../DEMO/configs/spid-config-testing.txt $j > ACTUAL_RESULT/$filename-SPID.txt
done
rm -r SpidModels

########## End Processing ##########

########## Results Calculation ##########

#sleep 2
echo -en "                               \r"
echo -en "Analyzing Results\r"
echo -en '\n[################    ] 80%'
echo -en "\033[F\r"

# Find number of errors between actual and expected
ERRORS=0
ERRORM=0
tmpfile=$(mktemp /tmp/ProcessStream.XXXXXX)
for j in EXPECTED_RESULT/*.txt; do
	## Test SPID
	RESULT=$(diff $j ACTUAL_RESULT/`basename $j .txt`-SPID.txt | grep "^>" | wc -l)
	if (( $RESULT > 0 )); then
		echo -e "Mismatch in `basename $j .txt`-SPID\n" >> $tmpfile
		diff $j ACTUAL_RESULT/`basename $j .txt`-SPID.txt >> $tmpfile
	fi
	ERRORS=$((ERRORS+RESULT))
	
	## Test String-Matching
	RESULT=$(diff $j ACTUAL_RESULT/`basename $j .txt`-STRING.txt | grep "^>" | wc -l)
	if (( $RESULT > 0 )); then
		echo -e "Mismatch in `basename $j .txt`-STRING\n" >> $tmpfile
		diff $j ACTUAL_RESULT/`basename $j .txt`-STRING.txt >> $tmpfile
	fi
	ERRORM=$((ERRORM+RESULT))
done
touch Mismatch.txt
rm Mismatch.txt
cat $tmpfile > Mismatch.txt
rm "$tmpfile"

echo -en "                               \r"
echo -en "Complete | Results Below\r"
echo -en '\n[####################] 100%'
echo -en '\n\n'

# Find total number of streams
ATTEMPTS=0
for j in EXPECTED_RESULT/*.txt; do
	LINES=$(cat $j | wc -l)
	
	# Test for String-Matching
	LINESACT=$(cat ACTUAL_RESULT/`basename $j .txt`-STRING.txt | wc -l)
	MISSING=$((LINES-LINESACT))
	if (( $MISSING > 0 )); then
		echo -en "WARNING: `basename $j .txt`-STRING.txt is missing $MISSING stream(s)\n"
	fi

	# Test for SPID
	LINESACT=$(cat ACTUAL_RESULT/`basename $j .txt`-SPID.txt | wc -l)
	MISSING=$((LINES-LINESACT))
	if (( $MISSING > 0 )); then
		echo -en "WARNING: `basename $j .txt`-SPID.txt is missing $MISSING stream(s)\n"
	fi

	ATTEMPTS=$((ATTEMPTS+LINES))
done

# Find percent failed
PERCENTS=$(awk "BEGIN { pc=100*${ERRORS}/${ATTEMPTS}; i=int(pc); print (pc) }")
PERCENTM=$(awk "BEGIN { pc=100*${ERRORM}/${ATTEMPTS}; i=int(pc); print (pc) }")

# Find successes
SUCCESS=$((ATTEMPTS-ERRORS))
SUCCESM=$((ATTEMPTS-ERRORM))

echo -en "\nSPID Results\n"
echo "Successful Matches: $SUCCESS"
echo "Identifications Failed: $ERRORS"
echo "Total Attempts: $ATTEMPTS"
printf "Failure Rate: %0.2f%%\n" $PERCENTS
echo -en "\n\nString-Matching Results\n"
echo "Successful Matches: $SUCCESM"
echo "Identifications Failed: $ERRORM"
echo "Total Attempts: $ATTEMPTS"
printf "Failure Rate: %0.2f%%\n" $PERCENTM
echo -en "\n\nMismatches printed to Mismatch.txt\n"

########## End Results ##########