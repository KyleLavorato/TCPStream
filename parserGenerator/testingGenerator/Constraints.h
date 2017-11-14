/**
 * File:    callback.h
 *
 * Purpose: Concrete data structures for IGMP.
 *
 * Revision History:
 *
 * 1.0  - Ali ElShakankiry - June 2016
 *  - Initial Version
 * 
 *2.0	- Siam Hasan - August 2016
 *  - Mighty second version
 */
#ifndef CONST_H
#define CONST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int instantiateC7a(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t data, FILE* traceFileCons);
int evaluateC7a(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t data, FILE* traceFileCons);
int destroyC7a(uint32_t key1, uint32_t key2, uint32_t key3, FILE* traceFileCons);

int instantiateC7b(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t data, FILE* traceFileCons);
int evaluateC7b(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t data, FILE* traceFileCons);
int destroyC7b(uint32_t key1, uint32_t key2, uint32_t key3, FILE* traceFileCons);


int instantiateC8(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t* data, FILE* traceFileCons);
int evaluateC8(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t* data, FILE* traceFileCons);
int destroyC8(uint32_t key1, uint32_t key2, uint32_t key3, FILE* traceFileCons);

 
int instantiateC1(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons);
int bindC1(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons);
int evaluateC1(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons);
int destroyC1(uint32_t key1, uint32_t key2, FILE* traceFileCons);

int instantiateC5(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons);
int bindC5(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons);
int evaluateC5(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons);
int destroyC5(uint32_t key1, uint32_t key2, FILE* traceFileCons);

int instantiateC11(uint32_t key1, uint32_t key2, uint32_t data, FILE* traceFileCons);
int bindC11(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t data, int split, FILE* traceFileCons);
int evaluateC11(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t data1, uint32_t data2, FILE* traceFileCons);
int destroyC11(uint32_t key1, uint32_t key2, FILE* traceFileCons);

int InsertValueFact8(uint32_t key1, uint32_t key2, uint32_t data);
uint32_t GetValueFact8(uint32_t key1, uint32_t key2);

void PrintEvaluateStats();

void initializeConstraints();
void finalizeConstraints();

void clearAll();


#endif /* CALLBACK_H */

////*******************************************************************************************************//////////
