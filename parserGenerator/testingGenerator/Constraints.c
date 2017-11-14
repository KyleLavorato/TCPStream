#include "Constraints.h"
#include "hashmap.h"
#include "StringHash.h"
#include <arpa/inet.h>
#include "globals.h"


int iC7a = 0;
int iC7b = 0;
int iC1 = 0;
int iC8 = 0;
int iC5 = 0;
int iC11 = 0;


void initializeConstraints()
{
	if (learnmode == 1)
		return;
	
	LoadC8FromFacts();
}

void finalizeConstraints()
{
	if (learnmode == 0)
		return;

	SaveC8ToFacts();
}

static int clearFlag = 0;

void clearAll()
{
	if (clearFlag == 0)
	{
		clearC1();
		clearC5();
		clearC7a();
		clearC7b();
		clearC8();
		clearC11();

		clearFlag++;
	}
}

void PrintEvaluateStats()
{	
	if (traceFileCons)
	{
		fprintf(traceFileCons, "C1 Evaluated: %d\n", iC1);
		fprintf(traceFileCons, "C5 Evaluated: %d\n", iC5);
		fprintf(traceFileCons, "C7a Evaluated: %d\n", iC7a);
		fprintf(traceFileCons, "C7b Evaluated: %d\n", iC7b);
		fprintf(traceFileCons, "C8 Evaluated: %d\n", iC8);
		fprintf(traceFileCons, "C11 Evaluated: %d\n", iC11);
	}

	printf("C1 Evaluated: %d\n", iC1);
	printf("C5 Evaluated: %d\n", iC5);
	printf("C7a Evaluated: %d\n", iC7a);
	printf("C7b Evaluated: %d\n", iC7b);
	printf("C8 Evaluated: %d\n", iC8);
	printf("C11 Evaluated: %d\n", iC11);
}


int instantiateC7a(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t data, FILE* traceFileCons)
{
	uint32_t* c = (uint32_t*) malloc(sizeof(uint32_t) * 2);
    memset(c, 0, sizeof(uint32_t));

    c[0] = data;

	return insertValueC7a(key1, key2, key3, c);
}

int evaluateC7a(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t data, FILE* traceFileCons)
{
	if (learnmode == 1)
		return 1;


	uint32_t* p =  GetValuefromC7a(key1, key2, key3);

	if (p == NULL)
		return -1;

	iC7a++;

	if (p[0] == data)
	{
		char* topic = stringForHash(data);

		struct in_addr addr;
		addr.s_addr = htonl(key1); 
		char *token = inet_ntoa(addr);

		if (traceFileCons)
			fprintf(traceFileCons, "C7a :: Participant %s is publishing and subscribing at the same topic: %s\n", token, topic);
		else
			printf("C7a :: Participant %s is publishing and subscribing at the same topic: %s\n", token, topic);

		return -1;
	}

	return 1;
}

int destroyC7a(uint32_t key1, uint32_t key2, uint32_t key3, FILE* traceFileCons)
{
	return deleteValueC7a(key1, key2, key3);
}

int instantiateC7b(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t data, FILE* traceFileCons)
{
	uint32_t* c = (uint32_t*) malloc(sizeof(uint32_t) * 2);
    memset(c, 0, sizeof(uint32_t));
    c[0] = data;

	return insertValueC7b(key1, key2, key3, c);
}

int evaluateC7b(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t data, FILE* traceFileCons)
{
	if (learnmode == 1)
		return 1;

	uint32_t* p =  GetValuefromC7b(key1, key2, key3);

	if (p == NULL)
		return -1;

	iC7b++;

	if (p[0] == data)
	{
		char* topic = stringForHash(data);

		struct in_addr addr;
		addr.s_addr = htonl(key1); 
		char *token = inet_ntoa(addr);

		if (traceFileCons)
			fprintf(traceFileCons, "C7b :: Participant %s is publishing and subscribing at the same topic: %s\n", token, topic);
		else
			printf("C7b :: Participant %s is publishing and subscribing at the same topic: %s\n", token, topic);
		return -1;
	}

	return 1;
}

int destroyC7b(uint32_t key1, uint32_t key2, uint32_t key3, FILE* traceFileCons)
{
	return deleteValueC7b(key1, key2, key3);
}

int instantiateC1(uint32_t key1, uint32_t key2, uint32_t data, 
				  FILE* traceFileCons)
{
	uint32_t* c = (uint32_t*) malloc(sizeof(uint32_t) * 2);
    memset(c, 0, sizeof(uint32_t));
    c[0] = data;

	return insertValueC1(key1, key2, c);
}

int bindC1(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons)
{
	uint32_t* p = GetValuefromC1(key1, key2);
	if (p == NULL)
	{
		if (traceFileCons)
			fprintf(traceFileCons, "C1 :: Order of arrival mismatch\n");
		else
			printf("C1 :: Order of arrival mismatch\n");
	}

	if (p[1] == 0)
	{
		p[1] = data;
		return 1;
	}

	return -1;
}

int evaluateC1(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons)
{
	iC1++;

	uint32_t* p = GetValuefromC1(key1, key2);
	if ((p[0] == p[1] && p[1] == data))
	{
		
		struct in_addr addr;
		addr.s_addr = htonl(key1); 
		char *token = inet_ntoa(addr);

		if (traceFileCons)
			fprintf(traceFileCons, "C1 :: Frequent membership reports from: %s\n", token);
		else
			printf("C1 :: Frequent membership reports from: %s\n", token);

		return -1;
	}

	return 1;
}

int destroyC1(uint32_t key1, uint32_t key2, FILE* traceFileCons)
{
	return deleteValueC1(key1, key2);
}

int evaluateC8(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t* data, FILE* traceFileCons)
{
	if (learnmode == 1)
	{
		InsertValueFact8(key1, key2, key3);
		return 1;
	}

	iC8++;

	uint32_t* p = GetValuefromfC8(key1, key2, key3);


	struct in_addr addr;
	addr.s_addr = htonl(key1); 
	char *token = inet_ntoa(addr);

	if (p == NULL)
	{
		if (traceFileCons)
			fprintf(traceFileCons, "C8 :: Publisher publishing from untrusted source: %s\n", token);
		else
			printf("C8 :: Publisher publishing from untrusted source: %s\n", token);

	}

	int iMismatch = 0;
	for (int i = 0; i < 8; i++)
	{
		if (data[i] != p[i])
		{
			iMismatch = 1;
			break;
		}
	}

	if (iMismatch)
		return 1;

	if (traceFileCons)
		fprintf(traceFileCons, "C8 :: QoS Setting is changed for publisher: %d\n", key1);
	else
		printf("C8 :: QoS Setting is changed for publisher: %d\n", key1);

	

	return -1;
}

int destroyC8(uint32_t key1, uint32_t key2, uint32_t key3, FILE* traceFileCons)
{
	return deleteValueC8(key1, key2, key3);
}

int instantiateC8(uint32_t key1, uint32_t key2, uint32_t key3, 
				  uint32_t* data, FILE* traceFileCons)
{
	uint32_t* c = (uint32_t*) malloc(sizeof(uint32_t) * 2);
    memcpy(c, data, 8 * sizeof(uint32_t));

	return insertValueC8(key1, key2, key3, c);
}

int instantiateC5(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons)
{
	uint32_t* c = (uint32_t*) malloc(sizeof(uint32_t) * 2);
    memset(c, 0, sizeof(uint32_t));

    c[0] = data;

	return insertValueC5(key1, key2, c);
}

int bindC5(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons)
{
	uint32_t* p = GetValuefromC5(key1, key2);

	if (p == NULL)
		return -1;

	p[1] = data;
	return 1;
}

int evaluateC5(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons)
{
	if (learnmode == 1)
		return 1;

	uint32_t* p = GetValuefromC5(key1, key2);
	if (p == NULL)
		return -1;

	iC5++;

	if ((p[0] == p[1] && p[1] == data))
		return 1;

	struct in_addr addr;
	addr.s_addr = htonl(key1); 
	char *token = inet_ntoa(addr);

   if (traceFileCons) 
   		fprintf(traceFileCons, "C5 :: Participant is not valid member of any multicast group : %s\n", token);
   	else
   		printf("C5 :: Participant is not valid member of any multicast group : %s\n", token);
	return -1;
}

int destroyC5(uint32_t key1, uint32_t key2, FILE* traceFileCons)
{
	return deleteValueC5(key1, key2);
}

int instantiateC11(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons)
{
	uint32_t* c = (uint32_t*) malloc(sizeof(uint32_t) * 2);
    memset(c, 0, sizeof(uint32_t));

    c[0] = data;

	if (insertIValueC11(key1, key2, c) == -1)
	{
		if (traceFileCons)
			fprintf(traceFileCons, "Warning:: C11 --> Number of publihsers reached at maximum.\n");

		return -1;
	}

	return 1;
}


int bindC11(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t data, int split, FILE* traceFileCons)
{
	uint32_t* ins = GetInsValuefromfC11(key1, key2);

	if (ins == NULL)
	{
		if (traceFileCons)
			fprintf(traceFileCons, "Error:: C11 --> Publisher did not arrive.\n");

		return -1;
	}

	uint32_t* bind = GetBindValuefromfC11(key1, key2, key3);

	if (bind != NULL)
	{
		if (!split)
		{
			if (traceFileCons)
				fprintf(traceFileCons, "Error:: C11 --> Subscribers is sending multiple packets.\n");

			return -1;
		}
	}

	ins[1] = data;

	if (insertBValueC11(key1, key2, key3, ins) == -1)
	{
		if (traceFileCons)
			fprintf(traceFileCons, "Warning:: C11 --> Number of publihsers reached at maximum.\n");

		return -1;
	}

	
	return 1;
}

int evaluateC11(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t data1, uint32_t data2, FILE* traceFileCons)
{
	if (learnmode == 1)
		return 1;

	iC11++;

	uint32_t* bind = GetBindValuefromfC11(key1, key2, key3);

	if (bind == NULL)
	{
		if (traceFileCons)
			fprintf(traceFileCons, "Error:: C11 --> Subscriber did not arrive.\n");

		return -1;
	}


	if (bind[0] == data1 && bind[1] == data2)
		return 1;

   if (traceFileCons) 
   		fprintf(traceFileCons, "Invalid Channel between %X %X\n", data1, data2);
   
	return -1;
}

int destroyC11(uint32_t key1, uint32_t key2, FILE* traceFileCons)
{
	if (deleteValueIC11(key1, key2) == -1 || deleteValueBC11(key1, key2) == -1)
	{
		if (traceFileCons)
			fprintf(traceFileCons, "Error:: C11 --> No tree found.\n");

		return -1;
	}

	return 1;

}

int InsertValueFact8(uint32_t key1, uint32_t key2, uint32_t data)
{
	return insertValueFact8(key1, key2, data);
}

uint32_t GetValueFact8(uint32_t key1, uint32_t key2)
{
	return GetValuefromfact8(key1, key2);
}

