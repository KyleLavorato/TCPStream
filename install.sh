#!/bin/bash

echo -e "\nsudo apt-get install libpcap-dev libssl-dev cmake\n"
sudo apt-get install libpcap-dev libssl-dev cmake

echo -e "\nCloning libtins\n"
git clone https://github.com/mfontanini/libtins

echo -e "\ncd libtins\n"
cd libtins

echo -e "\nmkdir build\n"
mkdir build

echo -e "\nmkdir build\n"
cd build

echo -e "\ncmake ../ -DLIBTINS_ENABLE_CXX11=1\n"
cmake ../ -DLIBTINS_ENABLE_CXX11=1

echo -e "\nmake\n"
make

echo -e "\nsudo make install\n"
sudo make install

echo -e "\nsudo ldconfig\n"
sudo ldconfig

echo -e "\ncd ../../\n"
cd ../../

echo -e "\nrm -rf libtins\n"
rm -rf libtins

echo -e "\nlibtins installed successfully\n"

echo -e "\nInstalling tshark for test suite\n"
sudo apt-get install tshark
echo -e "\ntshark installed successfully\n"

echo -e "\nInstalling boost library\n"
sudo apt-get install libboost-all-dev
echo -e "\boost installed successfully\n"

echo -e "\nInstalling TXL\n"
sudo ./SUPPORT/txl10.6e.linux64/InstallTxl
echo -e "\nTXL installed successfully"