#!/bin/bash
txl CONFIG/Config.sws TXL/generateInterface.txl -idchars '/.' > parser.c
txl CONFIG/Config.sws TXL/generateInterfaceHeader.txl -idchars '/.' > parser.h
