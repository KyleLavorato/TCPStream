#!/bin/bash

DIR=""
CALLBACK=""
PARAM=""

if [[ "$1" == "" || "$1" == "-h" ]]; then
	printf "Usage:\t./UID.sh [FILENAME]\n"
	printf "\t./UID.sh [FILENAME] [DIRECTORY]\n"
	echo "DIRECTORY is the directory to move the output files to"
	exit 1
fi

filename=$(echo $1 | cut -d '.' -f 1)
extension=$(echo $1 | cut -d '.' -f 2)

mkdir -p SCL5
mkdir -p SOURCE
mkdir -p INTERMEDIATE

for i in $*
do
	if [ "$i" == "-nocallback" ]
	then
		CALLBACK="-nocallback"
		continue
   	fi
   	if [ "$i" == "-debug" ]
	then
		CALLBACK="-debug"
		continue
   	fi
   	if [ "$i" == "-q" ]
	then
		PARAM="-q"
		continue
   	fi
	if [[ "$DIR" == ""  && "$i" != "-nocallback" && "$i" != "-debug"  && "$i" != *".scl5" ]];
    then
	    DIR=$i
	fi
done

# Unique naming for all declarations
txl SCL5/$1 TXL/UID_declarations.txl $PARAM > INTERMEDIATE/"$filename"_declarations.scl5

# Unique naming for all References
txl INTERMEDIATE/"$filename"_declarations.scl5 TXL/UID_references.txl $PARAM -idchars '$' > INTERMEDIATE/"$filename"_UID.scl5 # -idchars '$'

# Callback annotation
txl INTERMEDIATE/"$filename"_UID.scl5 TXL/callback_annotation.txl $PARAM -idchars '$' > INTERMEDIATE/"$filename"_UID_callbackAnnotated.scl5

# Generate annotated scl5 file for source optimizations
txl INTERMEDIATE/"$filename"_UID_callbackAnnotated.scl5 TXL/generateOptimizations.txl $PARAM -idchars '$' > INTERMEDIATE/"$filename"_UID_annotated.scl5

# Generate C header file for scl5 file
txl INTERMEDIATE/"$filename"_UID_annotated.scl5 TXL/generateHeader.txl $PARAM -idchars '$' > INTERMEDIATE/"$filename"_Generated.h.unsorted

# Generate C header sorted file 
txl INTERMEDIATE/"$filename"_Generated.h.unsorted TXL/sortHeader.Txl $PARAM -idchars '$' > SOURCE/"$filename"_Generated.h

txl -s 140 INTERMEDIATE/"$filename"_UID_annotated.scl5 TXL/generateSource.txl $PARAM -idchars '$' - $CALLBACK > SOURCE/"$filename"_Generated.cpp


if [[ "$DIR" != "" ]]; then
	cp SOURCE/"$filename"_Generated.h SOURCE/"$filename"_Generated.cpp $DIR
fi

sed -i 's/PDU \*/PDUP \*/g' SOURCE/"$filename"_Generated.h
sed -i 's/PDU \*/PDUP \*/g' SOURCE/"$filename"_Generated.cpp

rm ../src/"$filename"_Generated.h 
rm ../src/"$filename"_Generated.cpp

cp SOURCE/"$filename"_Generated.cpp ../src/
cp SOURCE/"$filename"_Generated.h ../src/