#!/bin/bash


# Delete old intermediate folder; create new
rm -r INTERMEDIATE
mkdir INTERMEDIATE
rm -r EXPECTED_RESULT
mkdir EXPECTED_RESULT
COUNT=0

for j in PCAP/*; do
	# Send follows to an intermediate folder
	END=$(tshark -r $j -T fields -e tcp.stream | sort -n | tail -1)
	for ((i=0;i<=END;i++))
	do
	    #echo $i
	    tshark -r $j -qz follow,tcp,ascii,$i > INTERMEDIATE/follow-stream-$i.txt
	done

	tmpfile=$(mktemp /tmp/ProcessStream.XXXXXX)
	COUNT=0

	# Loop over all intermediates in folder
	for i in INTERMEDIATE/*.txt; do
		if grep --quiet SMB $i; then
			printf "$COUNT, SMB\n" >> $tmpfile
		elif grep --quiet HTTP $i; then
			printf "$COUNT, HTTP\n" >> $tmpfile
		elif grep --quiet Goodbye. $i; then
			printf "$COUNT, FTP\n" >> $tmpfile
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
