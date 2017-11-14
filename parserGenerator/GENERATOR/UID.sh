#!/bin/bash

# echo "Transforming $1". . .
DIR=""
CALLBACK=""

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

for i in $*
do
	if [ "$i" == "-nocallback" ]
	then
		CALLBACK="-nocallback"
		continue
   	fi
	if [[ "$DIR" == ""  && "$i" != "-nocallback"  && "$i" != *".scl5" ]];
    then
	    DIR=$i
	fi
done

# Unique naming for all declarations
#echo "Naming declarations -> "$filename"_declarations.scl5"
txl SCL5/$1 TXL/UID_declarations.txl > SCL5/"$filename"_declarations.scl5

# Unique naming for all References
#echo "Naming references -> "$filename"_UID.scl5"
txl SCL5/"$filename"_declarations.scl5 TXL/UID_references.txl -idchars '$' > SCL5/"$filename"_UID.scl5 # -idchars '$'

# Callback annotation
txl SCL5/"$filename"_UID.scl5 TXL/callback_annotation.txl -idchars '$' > SCL5/"$filename"_UID_callbackAnnotated.scl5

# Checking imports of file
#txl "$filename"_UID.scl5 TXL/checkImports.txl > /dev/null

# Generate annotated scl5 file for source optimizations
#echo "Creating annotated scl5 -> "$filename"_UID_annotated.scl5"
txl SCL5/"$filename"_UID_callbackAnnotated.scl5 TXL/generateOptimizations.txl -idchars '$' > SCL5/"$filename"_UID_annotated.scl5

# Generate C header file for scl5 file
#echo "Creating header file -> "$filename"_Generated.h.unsorted"
txl SCL5/"$filename"_UID_annotated.scl5 TXL/generateHeader.txl -idchars '$' > SCL5/"$filename"_Generated.h.unsorted

# Generate C header sorted file 
#echo "Creating header file -> "$filename"_Generated.h"
txl SCL5/"$filename"_Generated.h.unsorted TXL/sortHeader.Txl -idchars '$' > SOURCE/"$filename"_Generated.h

#echo "Creating source file -> "$filename"_Generated.c"
txl -s 140 SCL5/"$filename"_UID_annotated.scl5 TXL/generateSource.txl -idchars '$' - $CALLBACK > SOURCE/"$filename"_Generated.c
# -s 140 fixes problem

#sleep 1
#mv "$filename"_Generated.c testingGenerator/

if [[ "$DIR" != "" ]]; then
	cp SOURCE/"$filename"_Generated.h SOURCE/"$filename"_Generated.c $DIR
else
	cp SOURCE/"$filename"_Generated.h SOURCE/"$filename"_Generated.c ../testingGenerator/
fi

# Check imports in a module against table of exports from all module
#txl renamedFULL.scl5 checkImports.txl -idchars '$'
