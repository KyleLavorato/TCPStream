# ELEC 498 Project

## Problem

### Problem Definition

Identify the protocol used in packets.

### Constraints

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

### Configuration

This section has some ideas for meeting the configurability constraint of the problem.

#### OR Expression

Pass the program a configuration file in a format like: protocol,string1|string2|string3| ... |stringN

---
HTML,GET|POST|PATCH
FTP,this|that
---

The algorithm will try to find each of the strings provided in the config file on each packet in the streams. If *any* of the strings are found in a packet, the packet is identified as the protocol for that line in the config file. For example, if GET or POST or PATCH was found in a packet, then that packet would be identified as HTTP.

## Installing libtins

All of the commands needed for installing libtins have been put into the file `install.sh`. Just run:

```shell
chmod +x install.sh
./install.sh
```

This has been tested on an Ubuntu-based Linux system.

