#ifndef CGLOBALS_H
#define  CGLOBALS_H

//#include <vector>
//#include <map>
//#include <ctime>
#include <stdint.h>

/*struct KeyToQueue
{
	uint32_t NetAddress;
	uint32_t GroupAddress;

	bool const operator==(const KeyToQueue &o) const {
        return NetAddress == o.NetAddress && GroupAddress == o.GroupAddress;
    }

     bool const operator<(const KeyToQueue &o) const {
        return NetAddress < o.NetAddress && GroupAddress < o.GroupAddress;
    }
};

struct QueryQueue
{
	long ArrivalTime;
	std::vector<uint32_t> MemberIPAddress;
};

struct MemberPool
{
	std::map<KeyToQueue, std::vector<QueryQueue> > MembersWithQuery;
	std::map<uint32_t, uint32_t> MembersWithoutQuery;	
	std::map<KeyToQueue, std::clock_t > AnticipatedTimer;
};
*/
#endif