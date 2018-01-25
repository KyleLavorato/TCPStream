#!/bin/bash

cd GENERATOR
./translate.sh
./interface.sh
cd ../
make clean
make