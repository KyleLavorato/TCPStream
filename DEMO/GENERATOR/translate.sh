#!/bin/bash 

DIR=""
CALLBACK=""
PARAM=""

if [[ "$1" == "-h" || $# > 2 ]]; then
	printf "Usage:\t./translate.sh [DIRECTORY] [-nocallback]\n"
	printf "\targuments are optional"
	echo "DIRECTORY is an additional directory to move the output files to"
	echo "This script will always copy generated files into SOURCE"
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
   	if [ "$i" == "-debug" ]
	then
		CALLBACK=$i
		continue
   	fi
   	if [ "$i" == "-q" ]
	then
		PARAM=$i
		continue
   	fi
	if [[ "$DIR" == ""  && "$i" != "-nocallback" && "$i" != "-debug" && "$i" != "*.scl5" ]];
    then
	    DIR=$i
	fi
done

TYPE=""
for i in SCL5/*.scl5; do
    ./UID.sh `basename $i` $DIR $CALLBACK $PARAM
done