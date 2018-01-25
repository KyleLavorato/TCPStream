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

## Notes

* You should not enter the GENERATOR folder for any reason unless you know what you are doing, it is entirely self contained

* Unused variable warnings have been suppressed in the project compilation to prevent spam from the generated parsers