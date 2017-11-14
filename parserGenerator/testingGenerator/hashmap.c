
#include "hashmap.h"
#include "StringHash.h"
#include <arpa/inet.h>


int iSizeC7a = 0;
int iSizeC7b = 0;
int iSizeC1 = 0;
int iSizeC8 = 0;
int iSizeC5 = 0;


#define SIZEC11 256
#define ProbeValC11 389


typedef struct
{
  uint32_t m_key1; // IP
  uint32_t m_key2; // topic
  uint32_t* m_pdata;
} hashnodeIC11;

typedef struct
{
  uint32_t m_key1; // IP
  uint32_t m_key2; // topic
  uint32_t m_key3; // domain
  uint32_t* m_pdata;
} hashnodeBC11;


hashnodeIC11 hashIC11[SIZEC11];
hashnodeBC11 hashBC11[SIZEC11];

int GetNexPosC11(int pos)
{
  return (pos + ProbeValC11 ) % SIZEC11;
}

int hashPosIC11(uint32_t key1, unsigned key2)
{
  if (key1 == 0)
    key1 = 1;
  else if (key2 == 0)
    key2 = 1;

  unsigned long res = key1 * key2;
  return res % SIZEC11;
}

int hashPosBC11(uint32_t key1, unsigned key2, unsigned key3)
{
  if (key1 == 0)
    key1 = 1;
  if (key2 == 0)
    key2 = 1;
  if (key3 == 0)
    key3 = 1;

  unsigned long res = key1 * key2 * key3;
  return res % SIZEC11;
}


int insertIValueC11(uint32_t key1, uint32_t key2, uint32_t* pData)
{
     int pos = hashPosIC11(key1, key2);
     int originpos = pos;

     do
     {
       if (hashIC11[pos].m_key1 == 0 && 
           hashIC11[pos].m_key2 == 0)
       {
          hashIC11[pos].m_key1 = key1;
          hashIC11[pos].m_key2  = key2;
          hashIC11[pos].m_pdata = pData;
          return pos;
       }
       else
       {
         if (hashIC11[pos].m_key1 == key1 &&
             hashIC11[pos].m_key2 == key2)
          {
              return pos;
          }
       }

       pos = GetNexPosC11(pos);

     } while (pos != originpos);

     return -1;
}

int insertBValueC11(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t* pData)
{
     int pos = hashPosIC11(key1, key2);
     int originpos = pos;

     do
     {
       if (hashBC11[pos].m_key1 == 0 && 
           hashBC11[pos].m_key2 == 0 &&
           hashBC11[pos].m_key3 == 0)
       {
          hashBC11[pos].m_key1 = key1;
          hashBC11[pos].m_key2  = key2;
          hashBC11[pos].m_key3  = key3;
          hashBC11[pos].m_pdata = pData;
          return pos;
       }
       else
       {
         if (hashBC11[pos].m_key1 == key1 &&
             hashBC11[pos].m_key2 == key2 && 
             hashBC11[pos].m_key3 == key3)
          {
              return pos;
          }
       }

       pos = GetNexPosC11(pos);

     } while (pos != originpos);

     return -1;
}

int deleteValueBC11(uint32_t key1, uint32_t key2)
{
   for (int i = 0; i < SIZEC11; i++)
   {
      if (hashBC11[i].m_key1 == key1 && hashBC11[i].m_key2 == key2)
      {
          free(hashBC11[i].m_pdata);
          hashBC11[i].m_pdata = NULL;
          return 1;
      }
   }

   return -1;
}

int deleteValueIC11(uint32_t key1, uint32_t key2)
{
  int pos = hashPosIC11(key1, key2);
  int originpos = pos;

   do
   {
     if (hashIC11[pos].m_key1 == key1 && hashIC11[pos].m_key2 == key2)
     {
          free(hashIC11[pos].m_pdata);
          hashIC11[pos].m_pdata = NULL;
          return 1;
      }

     pos = GetNexPosC11(pos);
   }while (pos != originpos);

   return -1;
}

uint32_t* GetInsValuefromfC11(uint32_t key1, uint32_t key2)
{
  int pos = hashPosIC11(key1, key2);
  int originpos = pos;

   do
   {
     if (hashIC11[pos].m_key1 == key1 &&
         hashIC11[pos].m_key2 == key2)
     {
        return hashIC11[pos].m_pdata;
     }

     pos = GetNexPosC11(pos);

   }while (pos != originpos);

   return NULL;
}

uint32_t* GetBindValuefromfC11(uint32_t key1, uint32_t key2, uint32_t key3)
{
  int pos = hashPosBC11(key1, key2, key3);
  int originpos = pos;

   do
   {
     if (hashBC11[pos].m_key1 == key1 &&
         hashBC11[pos].m_key2 == key2 &&
         hashBC11[pos].m_key3 == key3)
     {
        return hashBC11[pos].m_pdata;
     }

     pos = GetNexPosC11(pos);
   }while (pos != originpos);

   return NULL;
}


#define SIZEFact8 256
#define ProbeValFact8 389


typedef struct
{
  uint32_t m_key1; //IP Address
  uint32_t m_key2; //domain ID
  uint32_t m_data; // token ID
} hashFact8;

hashFact8 hashF8[SIZEFact8];



int hashPosFact8(uint32_t key1, uint32_t key2)
{
  if (key1 == 0)
    key1 = 1;
  if (key2 == 0)
    key2 = 1;

  unsigned res = key1 * key2;
  return res % SIZEFact8;
}

int GetNextPosFact8(int pos)
{
  return (pos + ProbeValFact8 ) % SIZEFact8;

}

int insertValueFact8( uint32_t key1, uint32_t key2, uint32_t data)
{
  int pos = hashPosFact8(key1, key2);

     int originpos = pos;

     do
     {
       if (hashF8[pos].m_key1 == 0)
       {
          hashF8[pos].m_key1 = key1;
          hashF8[pos].m_key2 = key2;
          hashF8[pos].m_data = data;
          return pos;
       }
       else
       {
        if (hashF8[pos].m_key1 == key1 &&
            hashF8[pos].m_key2 == key2)
        {
          return pos;
        }

       }

       pos = GetNextPosFact8(pos);

     } while (pos != originpos);

     return -1;

}

uint32_t GetValuefromfact8(uint32_t key1, uint32_t key2)
{
  for (int i = 0; i < SIZEFact8; i++)
  {
    if (hashF8[i].m_key1 == key1 &&
          hashF8[i].m_key2 == key2)
    {
      return hashF8[i].m_data;
    }
  }

  return 0;
}


#define SIZEC7ab 256 
#define ProbeValC7ab 389


typedef struct 
{
      uint32_t m_key1;      // host IP
      uint32_t m_key2;      // group address
      uint32_t m_key3;      // domain ID
      uint32_t* m_pdata;
} hashNodeC7;

hashNodeC7 hashC7a[SIZEC7ab];
hashNodeC7 hashC7b[SIZEC7ab];


int hashPosC7a(uint32_t key1, uint32_t key2, uint32_t key3)
{
  if (key1 == 0)
    key1 = 1;
  if (key2 == 0)
    key2 = 1;
  if (key3 == 0)
    key3 = 1;

  unsigned long retVal =  key1 * key2 * key3;
  return retVal % SIZEC7ab;
}

int GetNexPosC7a(int pos)
{
  return (pos + ProbeValC7ab ) % SIZEC7ab;
}

int insertValueC7a(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t* data)
{
     int pos = hashPosC7a(key1, key2, key3);

     int originpos = pos;

     do
     {
       if (hashC7a[pos].m_key1 == 0)
       {
          hashC7a[pos].m_key1 = key1;
          hashC7a[pos].m_key2 = key2;
          hashC7a[pos].m_key3 = key3;
          hashC7a[pos].m_pdata = data;

          iSizeC7a++;

          if (iSizeC7a > (SIZEC7ab / 4))
          {
              FILE* fp = fopen("Hash/log.txt", "w"); 
              if (fp != NULL)
              {
                if (iSizeC7a + 1 == (SIZEC7ab / 4))
                  fprintf(fp, "touched 1/4th of hash C7a");
                else if (iSizeC7a + 1 == (SIZEC7ab / 2))
                  fprintf(fp, "touched 1/2th of hash C7a"); 
                else if (iSizeC7a + 1 == ((3 * SIZEC7ab) / 4))
                  fprintf(fp, "touched 3/4th of hash C7b");
                else if (iSizeC7a == SIZEC7ab)
                  fprintf(fp, "filled hash C7b");

                fclose(fp);
              }

          }

          return pos;
       }
       else
       {
        if (hashC7a[pos].m_key1 == key1 &&
            hashC7a[pos].m_key2 == key2 &&
            hashC7a[pos].m_key3 == key3)
          {
            return pos;
          }

       }

       pos = GetNexPosC7a(pos);

     } while (pos != originpos);

     return -1;
}


int deleteValueC7a(uint32_t key1, uint32_t key2, uint32_t key3)
{
     int pos = hashPosC7a(key1, key2, key3);

     int originpos = pos;

     do
     {

       if (hashC7a[pos].m_key1 == key1 &&
           hashC7a[pos].m_key2 == key2 &&
           hashC7a[pos].m_key3 == key3)
       {
          free(hashC7a[pos].m_pdata);
          return 1;
       }

       pos = GetNexPosC7a(pos);

     }while (pos != originpos);

     return -1;

}

uint32_t* GetValuefromC7a(uint32_t key1, uint32_t key2, uint32_t key3)
{
     int pos = hashPosC7a(key1, key2, key3);

     int originpos = pos;

     do
     {

       if (hashC7a[pos].m_key1 == key1 &&
           hashC7a[pos].m_key2 == key2 &&
           hashC7a[pos].m_key3 == key3)
       {
          return hashC7a[pos].m_pdata;
       }

       pos = GetNexPosC7a(pos);

     }while (pos != originpos);


  return NULL;
}

int hashPosC7b(uint32_t key1, uint32_t key2, uint32_t key3)
{
  if (key1 == 0)
    key1 = 1;
  if (key2 == 0)
    key2 = 1;
  if (key3 == 0)
    key3 = 1;

  unsigned long retVal =  key1 * key2 * key3;
  return retVal % SIZEC7ab;
}

int GetNexPosC7b(int pos)
{
  return (pos + ProbeValC7ab ) % SIZEC7ab;
}

int insertValueC7b(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t* data)
{
     int pos = hashPosC7b(key1, key2, key3);

     int originpos = pos;

     do
     {
       if (hashC7b[pos].m_key1 == 0)
       {
          hashC7b[pos].m_key1 = key1;
          hashC7b[pos].m_key2 = key2;
          hashC7b[pos].m_key3 = key3;
          hashC7b[pos].m_pdata = data;

          iSizeC7b++;

          if (iSizeC7b > (SIZEC7ab / 4))
          {
              FILE* fp = fopen("Hash/log.txt", "w"); 
              if (fp != NULL)
              {
                if (iSizeC7b + 1 == (SIZEC7ab / 4))
                  fprintf(fp, "touched 1/4th of hash C7a");
                else if (iSizeC7b + 1 == (SIZEC7ab / 2))
                  fprintf(fp, "touched 1/2th of hash C7a"); 
                else if (iSizeC7b + 1 == ((3 * SIZEC7ab) / 4))
                  fprintf(fp, "touched 3/4th of hash C7b");
                else if (iSizeC7b == SIZEC7ab)
                  fprintf(fp, "filled hash C7b");

                fclose(fp);
              }

          }

          return pos;
       }
       else
       {
        if (hashC7b[pos].m_key1 == key1 &&
            hashC7b[pos].m_key2 == key2 &&
            hashC7b[pos].m_key3 == key3)
          {
            return pos;
          }

       }

       pos = GetNexPosC7b(pos);

     } while (pos != originpos);

     return -1;
}

int deleteValueC7b(uint32_t key1, uint32_t key2, uint32_t key3)
{
     int pos = hashPosC7b(key1, key2, key3);

     int originpos = pos;

     do
     {

       if (hashC7b[pos].m_key1 == key1 &&
           hashC7b[pos].m_key2 == key2 &&
           hashC7b[pos].m_key3 == key3)
       {
          free(hashC7b[pos].m_pdata);
          return 1;
       }

       pos = GetNexPosC7b(pos);

     }while (pos != originpos);

     return -1;

}

uint32_t* GetValuefromC7b(uint32_t key1, uint32_t key2, uint32_t key3)
{
     int pos = hashPosC7b(key1, key2, key3);

     int originpos = pos;

     do
     {

       if (hashC7b[pos].m_key1 == key1 &&
           hashC7b[pos].m_key2 == key2 &&
           hashC7b[pos].m_key3 == key3)
       {
          return hashC7b[pos].m_pdata;
       }

       pos = GetNexPosC7b(pos);

     }while (pos != originpos);


  return NULL;
}

#define SIZEC5 256
#define ProbeValC5 389

typedef struct 
{
      uint32_t m_key1;      // host IP
      uint32_t m_key2;      // group address
      uint32_t* m_pdata;
} hashnodeC5;

hashnodeC5 hashC5[SIZEC5];

int hashPosC5(uint32_t key1, uint32_t key2)
{
  if (key1 == 0)
    key1 = 1;
  else if (key2 == 0)
    key2 = 1;

  unsigned long res = key1 * key2;
  return res % SIZEC5;
}

int GetNexPosC5(int pos)
{
  return (pos + ProbeValC5 ) % SIZEC5;
}

int insertValueC5(uint32_t key1, uint32_t key2, uint32_t* data)
{
  int pos = hashPosC5(key1, key2);

   int originpos = pos;

   do
   {
     if (hashC5[pos].m_key1 == 0)
     {
        hashC5[pos].m_key1 = key1;
        hashC5[pos].m_key2  = key2;
        hashC5[pos].m_pdata = data;
        
        iSizeC5++;

        if (iSizeC5 > (SIZEC5 / 4))
          {
              FILE* fp = fopen("Hash/log.txt", "w"); 
              if (fp != NULL)
              {
                if (iSizeC5 + 1 == (SIZEC5 / 4))
                  fprintf(fp, "touched 1/4th of hash C5\n");
                else if (iSizeC5 + 1 == (SIZEC5 / 2))
                  fprintf(fp, "touched 1/2th of hash C5\n"); 
                else if (iSizeC5 + 1 == ((3 * SIZEC5) / 4))
                  fprintf(fp, "touched 3/4th of hash C5\n");
                else if (iSizeC5 == SIZEC5)
                  fprintf(fp, "filled hash C5\n"); 
                
                fclose(fp);
              }
          }

        return pos;
     }
     else
     {
       if (hashC5[pos].m_key1 == key1 &&
           hashC5[pos].m_key2 == key2)
        {
          return pos;
        }
     }

     pos = GetNexPosC5(pos);

   } while (pos != originpos);

   return -1;
}

int deleteValueC5(uint32_t key1, uint32_t key2)
{
  int pos = hashPosC5(key1, key2);
  int originpos = pos;
  do
  {
    if (hashC5[pos].m_key1 == key1 &&
           hashC5[pos].m_key2 == key2)
    {
       iSizeC5--;

       hashC5[pos].m_key1 = 0;
       free(hashC5[pos].m_pdata);
       hashC5[pos].m_pdata = NULL;
    }

    pos = GetNexPosC5(pos);

  }while (pos != originpos);

  return 0;
}

uint32_t* GetValuefromC5(uint32_t key1, uint32_t key2)
{
     int pos = hashPosC5(key1, key2);
     int originpos = pos;

     do
     {
       if (hashC5[pos].m_key1 == key1 &&
           hashC5[pos].m_key2 == key2)
       {
          return hashC5[pos].m_pdata;
       }

       pos = GetNexPosC5(pos);

     }while (pos != originpos);

     return NULL;
}

#define SIZEC8 256
#define ProbeValC8 389

typedef struct 
{
  uint32_t m_key1; // Source IP
  uint32_t m_key2; // domain ID
  uint32_t m_key3; // topic key
  uint32_t* m_pdata;
} hashnodeC8;


hashnodeC8 hashC8[SIZEC8];


int hashPosC8(uint32_t key1, uint32_t key2, uint32_t key3)
{
  if (key1 == 0)    
    key1 = 1;
  else if (key2 == 0)
    key2 = 1;
  else if (key3 == 0)
    key3 = 1;

  unsigned long res = key1 * key2 * key3;
  return res % SIZEC8;
}

int GetNexPosC8(int pos)
{
  return (pos + ProbeValC8 ) % SIZEC8;
}

int insertValueC8(uint32_t key1, uint32_t key2, uint32_t key3, uint32_t* data)
{
     int pos = hashPosC8(key1, key2, key3);

     int originpos = pos;

     do
     {
       if (hashC8[pos].m_key1 == 0)
       {
          hashC8[pos].m_key1 = key1;
          hashC8[pos].m_key2  = key2;
          hashC8[pos].m_key3 = key3;

          hashC8[pos].m_pdata =  data;


          if (iSizeC8 > (SIZEC8 / 4))
          {
              FILE* fp = fopen("Hash/log.txt", "w"); 
              if (fp != NULL)
              {
                if (iSizeC8 + 1 == (SIZEC8 / 4))
                  fprintf(fp, "touched 1/4th of hash C8\n");
                else if (iSizeC8 + 1 == (SIZEC8 / 2))
                  fprintf(fp, "touched 1/2th of hash C8\n"); 
                else if (iSizeC8 + 1 == ((3 * SIZEC8) / 4))
                  fprintf(fp, "touched 3/4th of hash C8\n");
                else if (iSizeC8 == SIZEC8)
                  fprintf(fp, "filled hash C8\n"); 
                
                fclose(fp);
              }
          }

          return pos;
       }
       else
       {
         if (hashC8[pos].m_key1 == key1 &&
             hashC8[pos].m_key2 == key2 && 
             hashC8[pos].m_key3 == key3)
          {
            return pos;
          }
       }

       pos = GetNexPosC8(pos);

     } while (pos != originpos);

     return -1;
}

int deleteValueC8(uint32_t key1, uint32_t key2, uint32_t key3)
{
  int pos = hashPosC8(key1, key2, key3);
  int originpos = pos;

   do
   {
     if (hashC8[pos].m_key1 == key1 &&
         hashC8[pos].m_key2 == key2 &&
         hashC8[pos].m_key3 == key3)
     {
        free(hashC8[pos].m_pdata);
        return 1;
     }

     pos = GetNexPosC8(pos);

   }while (pos != originpos);


  return -1;
}

uint32_t* GetValuefromfC8(uint32_t key1, uint32_t key2, uint32_t key3)
{
  int pos = hashPosC8(key1, key2, key3);
  int originpos = pos;

   do
   {
     if (hashC8[pos].m_key1 == key1 &&
         hashC8[pos].m_key2 == key2 &&
         hashC8[pos].m_key3 == key3)
     {
        return hashC8[pos].m_pdata;
     }

     pos = GetNexPosC8(pos);

   }while (pos != originpos);


  return NULL;
}

void LoadC8FromFacts()
{
    int scanned = 0;

    char token1[256];
    char token2[256];
    char token3[256];
    char token4[256];
    char token5[256];
    char token6[256];
    char token7[256];
    char token8[256];
    char token9[256];
    char token10[256];
    char token11[256];

    FILE* fp = fopen("Facts/C8.txt", "r");
    if (fp == NULL)
      return;

    while ((scanned = fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", 
                 token1, token2, token3, token4,
                 token5, token6, token7, token8,
                 token9, token10, token11)) !=  EOF) {
    
        if(scanned == 11){
          uint32_t key1 = inet_addr(token1);
          uint32_t key2 = atoi(token2);
          uint32_t key3 = hashForString((const char*)token3);

          uint32_t* c = (uint32_t*) malloc(sizeof(uint32_t) * 8);
          memset(c, 0, sizeof(uint32_t));

          c[0] = atoi(token4);
          c[1] = atoi(token5);
          c[2] = atoi(token6);
          c[3] = atoi(token7);
          c[4] = atoi(token8);
          c[5] = atoi(token9);
          c[6] = atoi(token10);
          c[7] = atoi(token11);

          insertValueFact8(key1, key2, key3);
          insertValueC8(key1, key2, key3, c);
          
        }
        else {
            printf("Ivalid Input format in C8 facts Lists\n");
            break;
        }
    } 

   fclose(fp);  
}


void SaveC8ToFacts()
{
  
  FILE* fp = fopen("Facts/C8.txt", "w"); 
  if (fp == NULL)
    return;

  for (int i = 0; i < SIZEC8; i++)
  {
    if (hashC8[i].m_key1 == 0)
      continue;

    struct in_addr addr;
    addr.s_addr = htonl(hashC8[i].m_key1); 
    char *token1 = inet_ntoa(addr);


    char token2[256];
    sprintf(token2, "%d", hashC8[i].m_key2);

    char* token3 = stringForHash(hashC8[i].m_key3);

    uint32_t* c = hashC8[i].m_pdata;

    fprintf(fp, "%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", token1, token2, token3,
          c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);

    free(c);
  }

   fclose(fp);
}

#define SIZEC1 256
#define ProbeValC1 389

typedef struct 
{
  uint32_t m_key1; // Source IP
  uint32_t m_key2; // group address
  uint32_t* m_pdata;
} hashnodeC1;

hashnodeC1 hashC1[SIZEC1];




int hashPosC1(uint32_t key1, unsigned key2)
{
  if (key1 == 0)
    key1 = 1;
  else if (key2 == 0)
    key2 = 1;

  unsigned long res = key1 * key2;
  return res % SIZEC1;
}

int GetNexPosC1(int pos)
{
  return (pos + ProbeValC1 ) % SIZEC1;
}

int insertValueC1(uint32_t key1, uint32_t key2, uint32_t* data)
{
     int pos = hashPosC1(key1, key2);
     int originpos = pos;

     do
     {
       if (hashC1[pos].m_key1 == 0)
       {
          hashC1[pos].m_key1 = key1;
          hashC1[pos].m_key2  = key2;
          hashC1[pos].m_pdata = data;

          if (iSizeC1 > (SIZEC1 / 4))
          {
              FILE* fp = fopen("Hash/log.txt", "w"); 
              if (fp != NULL)
              {
                if (iSizeC1 + 1 == (SIZEC1 / 4))
                  fprintf(fp, "touched 1/4th of hash C1\n");
                else if (iSizeC1 + 1 == (SIZEC1 / 2))
                  fprintf(fp, "touched 1/2th of hash C1\n"); 
                else if (iSizeC1 + 1 == ((3 * SIZEC1) / 4))
                  fprintf(fp, "touched 3/4th of hash C1\n");
                else if (iSizeC1 == SIZEC1)
                  fprintf(fp, "filled hash C1\n"); 

                fclose(fp);
              }
          }

          return pos;
       }
       else
       {
         if (hashC1[pos].m_key1 == key1 &&
             hashC1[pos].m_key2 == key2)
        {
            return pos;
        }
       }

       pos = GetNexPosC1(pos);

     } while (pos != originpos);

     return -1;
}

int deleteValueC1(uint32_t key1, uint32_t key2)
{
    int pos = hashPosC1(key1, key2);
    int originpos = pos;

   do
   {
     if (hashC1[pos].m_key1 == key1 &&
         hashC1[pos].m_key2 == key2)
      {
        free(hashC1[pos].m_pdata);
        return 1;
      }

     pos = GetNexPosC1(pos);
   }while (pos != originpos);

   return -1;
}

uint32_t* GetValuefromC1(uint32_t key1, uint32_t key2)
{
    int pos = hashPosC1(key1, key2);
    int originpos = pos;

   do
   {
     if (hashC1[pos].m_key1 == key1 &&
         hashC1[pos].m_key2 == key2)
      {
        return hashC1[pos].m_pdata;
      }

     pos = GetNexPosC1(pos);
   }while (pos != originpos);

   return NULL;
}

void clearC7a()
{
  for (int i = 0; i < SIZEC7ab; i++)
  {
    if (hashC7a[i].m_key1 != 0)
      free(hashC7a[i].m_pdata);
  }
}

void clearC7b()
{
  for (int i = 0; i < SIZEC7ab; i++)
  {
    if (hashC7b[i].m_key1 != 0)
      free(hashC7b[i].m_pdata);
  }
}

void clearC8()
{
  for (int i = 0; i < SIZEC8; i++)
  {
    if (hashC8[i].m_key1 != 0)
      free(hashC8[i].m_pdata);
  }
}


void clearC1()
{
  for (int i = 0; i < SIZEC1; i++)
  {
    if (hashC1[i].m_key1 != 0)
      free(hashC1[i].m_pdata);
  }
}


void clearC11()
{
  for (int i = 0; i < SIZEC11; i++)
  {
    if (hashIC11[i].m_key1 != 0)
      free(hashIC11[i].m_pdata);
    if (hashBC11[i].m_key1 != 0)
      free(hashBC11[i].m_pdata);
  }
}


void clearC5()
{
  for (int i = 0; i < SIZEC5; i++)
  {
    if (hashC5[i].m_key1 != 0)
      free(hashC5[i].m_pdata);
  }
}




