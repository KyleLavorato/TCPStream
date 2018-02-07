# DEMO BUILD

## Usage

To compile the demo build execute:

```shell
./compile.sh
```

This script will execute the following actions

1. Genrate a parser for each protocol description located in `GENERATOR/SCL5` and copy it to `src`
2. Generate the `Parser.cpp` interface to connect the stream segmenting and parsers. The parsing interface is generated from the config file located at `configs/CONFIG.sws`.
3. Generate the dynamic `Makefile` for the project
4. Perform a full clean make of the project

## CONFIG.sws

This config file has the following format:
```
[Protocol] ': [String_To_Match] {, [String_To_Match] } '> [B | L] '< [Skip_Bits] ?(-DEBUG) ';
```
* Protocol - The protocol you are adding
* String_To_Match - Strings the protocols contain
* B | L - Whether the protocol is (B)ig or (L)ittle Endian
* Skip_Bits - The number of bits between the end of the TCP header and start of the protocol payload
* -DEBUG - Optional flag to generate stats for the indicated protocol

An example of a config line for HTTP is below:
```
HTTP:HTTP/1.1,GET>B<0;
```

## Test Suite

The software package comes with a built in test suite to assess performance located in `../TEST`.
The test suite is a set of two different evaluation scripts to test both the accuracy and bandwidth of the system.

#### Accuracy Testing

The script `ProcessStream.sh` will evaluate TCPStream's ability to correctly identify streams for any packet captures located in `../TEST/PCAP/*` for all modes. Run the test suite in the TEST directory with the command:
```shell
./ProcessStream.sh [-Protocol]
```
* Protocol - The protocol you wish to test or -all to test overall accuracy
The test suite will complete the following actions:
* Preprocess each input pcap in the PCAP directory to segment it into numbered streams, with the protocol identified using tshark (Wireshark command line)
* The preprocessed input will be output to `TEST/EXPECTED_RESULT` for manual inspection if desired.
* Complete a full clean make of TCPStream, including generating the parsers, interface and makefile.
* Process the same input pcaps through TCPStream using both *String Matching* and *SPID* seperately.
* The results of the runs will be output to `TEST/ACTUAL_RESULT/<pcap-name>-<method>.txt` respectively.
* Perform analysis of the results and output the statistics to console.
* Provide warnings if TCPStream misses a stream in its analysis
* Output a file `Mismatch.txt` which describes all the streams that failed to be identified correctly and what the correct ID was.

#### Bandwidth Testing

The script `performanceTest.sh` will evaluate TCPStream's output bandwidth for the specified parameters. Performance is evaluated by measuring the total execution time for a packet capture of a static size. The test will be run multiple times to get a reliable average result. The results will be output to `TEST/PERFORMANCE_RESULTS` upon completion of the test. Run the test with the command
```shell
./performanceTest.sh [-m(atching) | -s(pid)] [PCAP] [NumberOfTests]
```
* [-m | -s] selects either String-Matching or SPID for the test
* PCAP is the path to the PCAP you wish to feed as input to TCPStream (It is recommended to use large PCAPs)
* NumberOfTests is the number of times you would like to execute the program to measure performance

## Notes

* You should not enter the GENERATOR folder for any reason unless you know what you are doing, it is entirely self contained

* Unused variable warnings have been suppressed in the project compilation to prevent spam from the generated parsers