#!/bin/bash

rm ../Makefile
txl ../configs/CONFIG.sws TXL/generateMake.txl $1 -idchars '/.-+_*=$@()' -raw > ../Makefile
