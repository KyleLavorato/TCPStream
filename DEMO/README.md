# DEMO BUILD

## Usage

To compile the demo build execute:

```shell
./compile.sh
```

This script will execute the following actions

1. Genrate a parser for each protocol description located in `GENERATOR/SCL5` and copy it to `src`
2. Generate the `Parser.cpp` interface to connect the stream segmenting and parsers. The parsing interface is generated from the config file located at `configs/CONFIG.sws`.
3. Perform a full clean make of the project

## CONFIG.sws

This config file has the following format:
'''shell
[Protocol] ': [String_To_Match] {, [String_To_Match] } '> [B | L] '< [Skip_Bits] ?(-DEBUG) ';
'''
* Protocol - The protocol you are adding
* String_To_Match - Strings the protocols contain
* B | L - Whether the protocol is (B)ig or (L)ittle Endian
* Skip_Bits - The number of bits between the end of the TCP header and start of the protocol payload
* -DEBUG - Optional flag to generate stats for the indicated protocol

An example of a config line for HTTP is below:
'''shell
HTTP:HTTP/1.1,GET>B<0;
'''

## Notes

* You should not enter the GENERATOR folder for any reason unless you know what you are doing, it is entirely self contained

* Unused variable warnings have been suppressed in the project compilation to prevent spam from the generated parsers