CPPFLAGS = -g #-std=c++11 #-Wnoc++11-extensions
LDFLAGS = -g
OBJS= SMB2_Generated.o ARP_Generated.o UDP_Generated.o IGMP_Generated.o RTPS_Generated.o NTP_Generated.o putilities.o packet.o StringHash.o hashmap.o Constraints.o callback.o

LEARNOBJS= SMB2_Generated.o ARP_Generated.o UDP_Generated.o IGMP_Generated.o RTPS_Generated.o NTP_Generated.o putilities.o packet.o StringHash.o hashmap.o Constraints.o callback.o

all: pcapparse pcapdebug pcapparseLearn pcapdebugLearn

pcapparse:  pmain.o $(OBJS)
	gcc -o pcapparse pmain.o $(OBJS) -lpcap 

pcapdebug: pmain.o $(OBJS)
	gcc -O0 -o pcapdebug pmain.o $(OBJS) -lpcap

pcapparseLearn:  pmain.o $(LEARNOBJS)
	gcc -o pcapparseLearn pmain.o $(OBJS) -lpcap 

pcapdebugLearn: pmain.o $(LEARNOBJS)
	gcc -O0 -o pcapdebugLearn pmain.o $(OBJS) -lpcap

clean:
	rm -f *.o ./pcapparse ./pcapdebug ./pcapparseLearn ./pcapdebugLearn

# MAIN
pmain.o: globals.h pglobals.h 
#main.o: globals.h pglobals.h #callback.h

# PARSER 
UDP_Generated.o: globals.h pglobals.h UDP_Generated.h
IGMP_Generated.o: globals.h pglobals.h IGMP_Generated.h
RTPS_Generated.o: globals.h pglobals.h RTPS_Generated.h
ARP_Generated.o: globals.h pglobals.h ARP_Generated.h
SMB2_Generated.o: globals.h pglobals.h SMB2_Generated.h
putilities.o: putilities.h

#ConstraintsF.o: ConstraintsF.h
Constraints.o: Constraints.h	
#hashmapF.o: hashmapF.h
hashmap.o: hashmap.h

packet.o: globals.h packet.h
pglobals.h: packet.h
	touch pglobals.h

StringHash.o: StringHash.h
# CONSTRAINT ENGINE

callback.o: globals.h cglobals.h Constraints.o StringHash.h IGMP_Generated.h RTPS_Generated.h

callbackLearn.o: callback.cpp globals.h cglobals.h Constraints.o StringHash.h IGMP_Generated.h RTPS_Generated.h
	gcc -DLEARN -g -c -o callbackLearn.o
# DO NOT DELETE
