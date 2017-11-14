#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

int insertValueFact8( uint32_t key1, uint32_t key2, uint32_t data);
uint32_t GetValuefromfact8(uint32_t key1, uint32_t key2);


int insertValueC7a(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t* data);
int deleteValueC7a(uint32_t key1, uint32_t key2, uint32_t key3);
uint32_t* GetValuefromC7a(uint32_t key1, uint32_t key2, uint32_t key3);
void clearC7a();

int insertValueC7b(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t* data);
int deleteValueC7b(uint32_t key1, uint32_t key2, uint32_t key3);
uint32_t* GetValuefromC7b(uint32_t key1, uint32_t key2, uint32_t key3);
void clearC7b();


int insertValueC5(uint32_t key1, uint32_t key2, uint32_t* data);
int deleteValueC5(uint32_t key1, uint32_t key2);
uint32_t* GetValuefromC5(uint32_t key1, uint32_t key2);
void clearC5();


int insertValueC8(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t* data);
int deleteValueC8(uint32_t key1, uint32_t key2, uint32_t key3);
uint32_t* GetValuefromfC8( uint32_t key1, uint32_t key2, uint32_t key3);
void clearC8();

void LoadC8FromFacts();
void SaveC8ToFacts();


int insertValueC1(uint32_t key1, uint32_t key2, uint32_t* data);
int deleteValueC1(uint32_t key1, uint32_t key2);
uint32_t* GetValuefromC1(uint32_t key1, uint32_t key2);
void clearC1();




int insertIValueC11(uint32_t key1, uint32_t key2, uint32_t* pData);
int insertBValueC11(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t* pData);

int deleteValueIC11(uint32_t key1, uint32_t key2);
int deleteValueBC11(uint32_t key1, uint32_t key2);

uint32_t* GetInsValuefromfC11(uint32_t key1, uint32_t key2);
uint32_t* GetBindValuefromfC11(uint32_t key1, uint32_t key2, uint32_t key3);

void clearC11();

#endif
