#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>

#ifndef HASHMAP
typedef struct Table {

	int Key;

	void * Value;

	int Size;

	int bitmap[32];

	Table ** table;

} Table;

long long int pow_new(int num, int power);
long long int calculhash(int Key);
int getfivebits(long long int H, int id);
int hash(int Key, int Order);
void insertchar(Table * t, int Key, char * Value, int  size);
void insertcharlvl(Table *tab, int Key, char* Value, int size, int lvl);
Table * fullsearch(Table *t, int Key);
Table* search(Table *tab, int Key_s, int lvl);
void print(Table *t);
void newTable(Table* t);
void deleteTable(Table *t);
void deletekey(Table *tab, int key);
Table* getparant(Table *tab, int Key_s, int lvl);
int getlvl(Table *tab, int Key_s, int lvl);
#endif
