# TCPStream

## Software Introduction

TCPStream is a standalone application that sniffs network traffic and captures only the TCP packets, reorganizes them into their appropriate streams, and then sends those streams of data to a parsing interface to verify proper packet protocol structure.

### Software Features

1. Fully generic operation, allowing modular addition and subtraction of protocols the user wishes to detect and segment, through the use of configuration files
2. Fully generic parsing interface, allowing modular swapping of parsing tools for any detected protocols
3. Operation in both live sniffing mode and input feed of a packet capture file
4. A full automated test suite to determine accuracy and bandwidth performance on any implementation
5. A modular identification system, allowing for plug and play identification algorithms

### Identification Algorithms

The application currently supports two algorithms for the identification of assembled streams as a specific protocol.
1. String Matching is a stragety where common header strings for a protocol are matched in data packets to identify the protocol
2. Statistical Protocol IDentification (SPID) is an algorithm where a training sample is provided to build a fingerprint of standard traffic for each protocol that is present on the network. Incoming streams are then statistically compared to the fingerprints to identify the stream.

### Dependencies

TCPStream depends on the [libtins](http://libtins.github.io) and [Boost C++](https://www.boost.org/) to compile. The generic interface and build scripts require the [TXL compiler](https://txl.ca) and the test suite requires the [tshark](https://www.wireshark.org/docs/man-pages/tshark.html) library to operate.

For easy installation of all dependencies run the `install.sh` script.

## Application

### Compilation and Installation

To compile the application build execute:

```shell
./compile.sh
```

This script will execute the following actions

1. Generate a parser for each protocol description located in `GENERATOR/SCL5` and copy it to `src`
2. Generate the `Parser.cpp` interface to connect the stream segmenting and parsers. The parsing interface is generated from the config file located at `configs/CONFIG.sws`.
3. Generate the dynamic `Makefile` for the project
4. Perform a full clean make of the project

## Configuration Files

### Parsing and Build Configuration

The config file `CONFIG.sws` defines the parsing interface for each defined protocol and defines which protocols must be built into the make file. The file follows the following format:
```
[Protocol] ': [String_To_Match] {, [String_To_Match] } '> [B | L] '< [Skip_Bits] ?(-DEBUG) ';
```
* Protocol - The protocol that is to be added
* String_To_Match - Strings the protocols contain
* B | L - Whether the protocol is (B)ig or (L)ittle Endian
* Skip_Bits - The number of bits between the end of the TCP header and start of the protocol payload
* -DEBUG - Optional flag to generate stats for the indicated protocol

An example of a config line for HTTP is below:
```
HTTP:HTTP/1.1,GET>B<0;
```

### String Matching Configuration

The config file `string-matching-config.txt` defines protocols and strings that the string matching algorithm will attempt to identify protocols with. The file has the following format:
```
[Protocol] ': [String_To_Match]
```
* Protocol - The protocol that is to be identified
* String_To_Match - Strings the protocols contain

An example of a config line for HTTP is below:
```
HTTP:HTTP/1.1
```

### SPID Configuration

The config file `spid-config.txt` defines protocols and training data to build the models for each of those protocols, as well as a location to store the model. The file has the following format:
```
[Protocol] ': [Training_Data_Path] '; [Model_Path]
```
* Protocol - The protocol that is to be identified
* Training_Data_Path - The location to the training data packet capture
* Model_Path - The location where the build model can be stored

An example of a config line for HTTP is below:
```
HTTP:PCAP/http.pcap;Models/HTTP.txt
```

## Test Suite

The software package comes with a built in test suite to assess performance located in `TestSuite`.
The test suite is a set of two different evaluation scripts to test both the accuracy and bandwidth of the system.

### Accuracy Testing

The script `ProcessStream.sh` will evaluate TCPStream's ability to correctly identify streams for any packet captures located in `TestSuite/PCAP/*` for all modes. Run the test suite in the TestSuite directory with the command:
```shell
./ProcessStream.sh [-Protocol]
```
* Protocol - The protocol you wish to test or -all to test overall accuracy
The test suite will complete the following actions:
* Preprocess each input pcap in the PCAP directory to segment it into numbered streams, with the protocol identified using tshark (Wireshark command line)
* The preprocessed input will be output to `TestSuite/EXPECTED_RESULT` for manual inspection if desired.
* Complete a full clean make of TCPStream, including generating the parsers, interface and makefile.
* Process the same input pcaps through TCPStream using both *String Matching* and *SPID* seperately.
* The results of the runs will be output to `TestSuite/ACTUAL_RESULT/<pcap-name>-<method>.txt` respectively.
* Perform analysis of the results and output the statistics to console.
* Provide warnings if TCPStream misses a stream in its analysis
* Output a file `Mismatch.txt` which describes all the streams that failed to be identified correctly and what the correct ID was.

Example packet captures are provided in the `TestSuite/PCAP/[protocol]` directories.

### Bandwidth Testing

The script `performanceTest.sh` will evaluate TCPStream's output bandwidth for the specified parameters. Performance is evaluated by measuring the total execution time for a packet capture of a static size. The test will be run multiple times to get a reliable average result. The results will be output to `TestSuite/PERFORMANCE_RESULTS` upon completion of the test. Run the test with the command
```shell
./performanceTest.sh [-m(atching) | -s(pid)] [PCAP] [NumberOfTests]
```
* [-m | -s] selects either String-Matching or SPID for the test
* PCAP is the path to the PCAP you wish to feed as input to TCPStream (It is recommended to use large PCAPs)
* NumberOfTests is the number of times you would like to execute the program to measure performance
