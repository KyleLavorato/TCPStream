#ifndef __NODE_H__
#define __HNODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

enum eNodeType {
	op,
	leafStr,
	leafInt
};

enum eOperator{
	viol, //violation tree root
	aff, //affirmation
	andOp,
	orOp,
	eqOp,
	notEqOp
};

union data{
  const char* sData;
  uint32_t iData;
  enum eOperator eOp; 
};

struct node{
   union data vValue;
   int iPosChildren; //position of the array where the its children start to be allocated
   int iNumChildren; //number of positions that the children occupy in the array
   enum eNodeType eType; //operator, leafString or leafInteger
};

#endif