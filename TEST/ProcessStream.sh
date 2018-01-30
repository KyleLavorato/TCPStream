#!/bin/bash

END=$(tshark -r ~/Documents/498/PCAPS/onesmb.pcapng -T fields -e tcp.stream | sort -n | tail -1)
for ((i=0;i<=END;i++))
do
    echo $i
    tshark -r ~/Documents/498/PCAPS/onesmb.pcapng -qz follow,tcp,ascii,$i > follow-stream-$i.txt
done

# Delete old intermediate folder; create new

# Send follows to an intermediate folder

# Loop over all intermediates in folder

# grep for string pattern
# 221 Goodbye. for FTP
# SMB for SMB
# HTTP for HTTP

# Output to temp file, stream# ($1), Protocol

# end loop

# Write temp to file named same as pcap

######## Have entire script loop over a pcap folder