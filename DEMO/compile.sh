#!/bin/bash

cd GENERATOR
./makemake.sh
./translate.sh
./interface.sh
cd ../
make clean
make