#!/bin/bash 

DIR=""
CALLBACK=""

if [[ "$1" == "-h" || $# > 2 ]]; then
	printf "Usage:\t./translate.sh [DIRECTORY] [-nocallback] [-debug]\n"
	printf "\targuments are optional\n\n"
	printf "DIRECTORY is an additional directory to move the output files to\n"
	printf "This script will always copy generated parsers into ../TCPStream\n"
	printf "[-nocallback] disables callback generation\n"
	printf "[-debug] includes print statements for each field parsed\n"
	exit 1
fi

for i in $*
do
	if [ "$i" == "-nocallback" ]
	then
		CALLBACK=$i
		continue
   	fi
   	if [ "$i" == "-debug" ]
	then
		CALLBACK=$i
		continue
   	fi
	if [[ "$DIR" == ""  && "$i" != "-nocallback" && "$i" != "-debug" && "$i" != "*.scl5" ]];
    then
	    DIR=$i
	fi
done

./UID.sh SMB2.scl5 $DIR $CALLBACK
