#!/bin/bash 

DIR=""
CALLBACK=""

if [[ "$1" == "-h" || $# > 2 ]]; then
	printf "Usage:\t./translate.sh [DIRECTORY] [-nocallback]\n"
	printf "\targuments are optional"
	echo "DIRECTORY is an additional directory to move the output files to"
	echo "This script will always copy generated files into ../testingGenerator"
	echo "-nocallback tells the parser generator whether to include callback generation"
	exit 1
fi

for i in $*
do
	if [ "$i" == "-nocallback" ]
	then
		CALLBACK=$i
		continue
   	fi
	if [[ "$DIR" == ""  && "$i" != "-nocallback"  && "$i" != "*.scl5" ]];
    then
	    DIR=$i
	fi
done

./UID.sh SMB2.scl5 $DIR $CALLBACK
#./UID.sh RTPS.scl5 $DIR $CALLBACK
#./UID.sh IGMP.scl5 $DIR $CALLBACK
#./UID.sh NTP.scl5 $DIR $CALLBACK
#./UID.sh ARP.scl5 $DIR $CALLBACK

# UDP
#./UID.sh UDP.scl5 $DIR $CALLBACK
#./IMPORTS.sh UDP.scl5

# echo $CALLBACK
# echo $DIR