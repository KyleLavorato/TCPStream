# ELEC 498 Project

## Problem

### Problem Definition

There are 3 parts that make up the problem:

1. Segment all TCP packets into separate streams
2. Identify the application-layer protocol used in each packet
3. Parse each packet

### Constraints

#### Problem #2

* Must be configurable for different application layer protocols
* Must only consider TCP packets

### Nuances

#### Binary vs Text-Based Protocols

Some protocols are binary whereas others are text-based. This presents a particular challenge to a string matching approach because strings are usually text-based. It's going to be difficult if not impossible to identify binary protocols using this approach.

#### False Positives

If we're strictly matching strings to identify protocols, then we may run into false positives where we say a packet belongs to some protocol when it does not. This could occur if two protocols use the same word. There are many scenarios where this can happen:

1. When, for both protocols, the *protocol itself* uses that keyword
2. When one of the protocols allows submission of arbitrary strings, which could contain a keyword from another protocol
3. When the textual representation of some binary data happens to be the keyword by coincidence, not intent

## Solution

Problem #1 - stream segmenting - is handled by a library: [libtins](http://libtins.github.io).

Problem #2 - application layer protocol identification - is being handled by Jo, Hunter, and Troy. They are using 3 different approaches and will compare them to weigh pros and cons.

Problem #3 - packet parsing - is being handled by Kyle.

### Configuration

This section has some ideas for meeting the configurability constraint of the problem.

#### OR Expression

Pass the program a configuration file in a format like: `protocol,string1|string2|string3| ... |stringN`

```
HTML,GET|POST|PATCH
FTP,this|that
```

The algorithm will try to find each of the strings provided in the config file on each packet in the streams. If *any* of the strings are found in a packet, the packet is identified as the protocol for that line in the config file. For example, if GET or POST or PATCH was found in a packet, then that packet would be identified as HTTP.

## Installing libtins

All of the commands needed for installing libtins have been put into the file `install.sh`. Just run:

```shell
chmod +x install.sh
./install.sh
```

This has been tested on an Ubuntu-based Linux system.

## Write each stream to a file

Make sure you have a directory called `streams` to write the files to.

```shell
make
rm -f streams/*
./tcpstream PCAPS/<YOUR_FILE>.pcap
```