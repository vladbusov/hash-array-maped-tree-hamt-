#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>


long long int pow_new(int num, int power){
	long long int y = num;
	if (power == 0)
		return 1;
	for (int i = 1; i < power; i++){
		y *= num;
	}
	return y;
}

long long int calculhash(int Key) {
	double A = (pow(5, 0.5) - 1) / 2;
	long long int H = long long int(10000000000 * 33 * (double(Key*A) - int(Key*A)));
	return H;
}

int getfivebits(long long int H, int id){
	int fivebits = 0;
	int k = 0;
	while (H > 0){
		if (pow_new(2, (id * 5)) > H && H >= pow_new(2, (id - 1) * 5)){
			fivebits += (H % 2)*pow_new(10, k);
			k++;
		}
		H /= 2;
	}
	int desyatichnoe = 0;
	int i = 0;
	while (fivebits>0) {
		desyatichnoe += (fivebits % 10)* pow_new(2, i);
		i++;
		fivebits /= 10;
	}

	return desyatichnoe;
}

int hash(int Key, int Order){
	if (Order > 5)
		return 0;
	return getfivebits(calculhash(Key), Order);
}


typedef struct Table {
	int Key;
	void * Value;
	int Size;
	int bitmap[32];
	Table ** table;
	Table() {
		table = (Table **)calloc(32, sizeof(Table *));
		for (int i = 0; i < 32; i++){
			bitmap[i] = 0;
			table[i] = (Table *)calloc(1, sizeof(Table));
		}
	}
	~Table() {
		table = NULL;
	}

	void insertcharlvl(int Key, char* Value, int size, int lvl){
		if (lvl > 5) {
			return;
		}
		int adr = hash(Key, lvl);
		if (table == NULL){
			table = (Table **)calloc(32, sizeof(Table *));
			for (int i = 0; i < 32; i++){
				bitmap[i] = 0;
				table[i] = (Table *)calloc(1, sizeof(Table));
			}
		}
		if (table[adr]->Key == 0) {
			table[adr]->Key = Key;
			table[adr]->Value = (char *)calloc(size, sizeof(char));
			table[adr]->Value = &(*(Value));
			table[adr]->Size = size;
			bitmap[adr] = 1;
			return;
		} else {

			lvl++;
			int adr2 = hash(Key, lvl);
			if (table[adr]->bitmap[adr2] == 0) { 
				
				int t = 0;
				for (int i = 0; i < 32; i++)
					t += table[adr]->bitmap[i];


				
				if (t != 0){
					Table ** buff = (Table **)calloc((t + 1), sizeof(Table *));
					for (int i = 0; i < (t + 1); i++)
						buff[i] = (Table *)calloc(1, sizeof(Table));

					int window = 0;

					for (int i = 0; i < adr2; i++)
						window += table[adr]->bitmap[i];

					for (int i = 0; i < (t+1); i++){
						if (i == window){
							buff[i]->Key = Key;
							buff[i]->Value = (char *)calloc(size, sizeof(char));
							buff[i]->Value = &(*(Value));
							buff[i]->Size = size;
							for (int j = 0; j < 32; j++){
								buff[i]->bitmap[j] = 0;
							}
						}
						else if (i < window ) {
							buff[i] = table[adr]->table[i];
						}
						else if (i > window){
							buff[i] = table[adr]->table[i - 1];
						}
					}

					table[adr]->table = buff;
					table[adr]->bitmap[adr2] = 1;
					return;
				}
				else {
					table[adr]->bitmap[adr2] = 1;
					table[adr]->table = (Table **)calloc(32, sizeof(Table *));
					table[adr]->table[0] = (Table *)calloc(1, sizeof(Table));
					table[adr]->table[0]->Key = Key;
					table[adr]->table[0]->Value = (char *)calloc(size, sizeof(char));
					table[adr]->table[0]->Value = &(*(Value));
					table[adr]->table[0]->Size = size;
					for (int i = 0; i < 32; i++){
						table[adr]->table[0]->bitmap[i] = 0;
					}
					return;
				}
			}
			else {
				lvl++;
				int k = 0;
				for (int i = 0; i < adr2; i++)
					k += table[adr]->bitmap[i];
				for (int i = 0; i <= k; i++)
				table[adr]->table[k]->insertcharlvl(Key, Value, size, lvl);
			} 
		}
	}
	void insertchar(int Key, char * Value, int  size){
		insertcharlvl(Key, Value, size, 1);
		return;
	}
	Table * fullsearch(int Key){
	 return search(Key, 1);
	}
	Table* search(int Key_s, int lvl){
		 int adr = hash(Key_s, lvl);
		if (lvl > 5) return NULL;
		int t = 0;


		if (table != NULL){
			for (int i = 0; i < 32; i++)
				t += table[adr]->bitmap[i];
		}
		else {
			return NULL;
		}
		


		if (table[adr]->Key != 0 || t>0){
			if (table[adr]->Key == Key_s){
					return table[adr];
			} else {
				if (t == 0){
					return NULL;
				}
				lvl++;
				int adr2 = hash(Key_s, lvl);
				if (table[adr]->bitmap[adr2] == 1){
					int numofptr = 0;
					for (int i = 0; i < adr2; i++)
						if (table[adr]->bitmap[i] == 1) numofptr++;
					if (table[adr]->table[numofptr]->Key == Key_s)
						return table[adr]->table[numofptr];
					lvl++;
					return table[adr]->table[numofptr]->search(Key_s, lvl);
				} else {
					return NULL;
				}
			}
		} else { return NULL; }
		
	}
	void print(){
		printf("************\nKey: %d\nValue: %s\n************\n", Key, Value);
	}
	
} Table;


int main(){
	int Key = 54;
	int arraysize = 50;
	Table map;

	for (int i = 51; i < 305; i++){
		if (i % 2 == 0){
			map.insertchar(i, "Vasya", 5);
		}
		else {
			map.insertchar(i, "Volodya", 7);
		}
	}
	for (int i = 51; i < 305; i++)
		if (map.fullsearch(i) != NULL )
			map.fullsearch(i)->print();
	system("PAUSE");
	return 0;
}

