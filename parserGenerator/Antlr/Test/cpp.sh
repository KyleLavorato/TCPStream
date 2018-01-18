#!/bin/bash

g++ -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux AntlrTest.cpp -o AntlrTest -L/usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server/ -ljvm