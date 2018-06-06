#!/bin/bash

txl ../configs/CONFIG.sws TXL/generateInterface.txl $1 -idchars '/.' > SOURCE/Parser.cpp
txl ../configs/CONFIG.sws TXL/generateInterfaceHeader.txl $1 -idchars '/.' > SOURCE/Parser.h

rm ../src/Parser.cpp
rm ../src/Parser.h

cp SOURCE/Parser.cpp ../src/
cp SOURCE/Parser.h ../src/
