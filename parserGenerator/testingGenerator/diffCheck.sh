#!/bin/bash

temp_file=$(mktemp)

# Compare edited generator output to working generator to ensure nothing is broken
for f in *.h *.c
do
	A="../../testingGenerator/$f"
	DIFF=$(diff $f $A)
	if [ "$DIFF" != "" ]
	then
		echo "$f Has Been Modified"
		echo "$f" >> "$temp_file"
		diff $f $A >> "$temp_file"
	fi
done

# DIFF=$(diff RTPS_Generated.c ../walkCallback/RTPS_Generated.c)
# if [ "$DIFF" != "" ]
# 	then
# 		echo "The .c file does not match"
# 		echo "** RTPS.c **" >> "$temp_file"
# 		diff RTPS_Generated.c ../walkCallback/RTPS_Generated.c >> "$temp_file"
# fi

cat "$temp_file" > diffResults.txt
rm ${temp_file}