#include "hashmap.h"


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





void insertchar(Table * t,int Key, char * Value, int  size){

	insertcharlvl(t, Key, Value, size, 1);

	return;

}


void insertcharlvl(Table *tab ,int Key, char* Value, int size, int lvl){

	if (lvl > 5) {

		return;

	}

	int adr = hash(Key, lvl);

	if (tab->table == NULL){

		tab->table = (Table **)calloc(32, sizeof(Table *));

		for (int i = 0; i < 32; i++){

			tab->bitmap[i] = 0;

			tab->table[i] = (Table *)calloc(1, sizeof(Table));

		}

	}

	if (tab->table[adr]->Key == 0) {

		tab->table[adr]->Key = Key;

		tab->table[adr]->Value = (char *)calloc(size, sizeof(char));

		tab->table[adr]->Value = &(*(Value));

		tab->table[adr]->Size = size;

		tab->bitmap[adr] = 1;

		return;

	}
	else {



		lvl++;

		int adr2 = hash(Key, lvl);

		if (tab->table[adr]->bitmap[adr2] == 0) {



			int t = 0;

			for (int i = 0; i < 32; i++)

				t += tab->table[adr]->bitmap[i];







			if (t != 0){

				Table ** buff = (Table **)calloc((t + 1), sizeof(Table *));

				for (int i = 0; i < (t + 1); i++)

					buff[i] = (Table *)calloc(1, sizeof(Table));



				int window = 0;



				for (int i = 0; i < adr2; i++)

					window += tab->table[adr]->bitmap[i];



				for (int i = 0; i < (t + 1); i++){

					if (i == window){

						buff[i]->Key = Key;

						buff[i]->Value = (char *)calloc(size, sizeof(char));

						buff[i]->Value = &(*(Value));

						buff[i]->Size = size;

						for (int j = 0; j < 32; j++){

							buff[i]->bitmap[j] = 0;

						}

					}

					else if (i < window) {

						buff[i] = tab->table[adr]->table[i];

					}

					else if (i > window){

						buff[i] = tab->table[adr]->table[i - 1];

					}

				}



				tab->table[adr]->table = buff;

				tab->table[adr]->bitmap[adr2] = 1;

				return;

			}

			else {

				tab->table[adr]->bitmap[adr2] = 1;

				tab->table[adr]->table = (Table **)calloc(32, sizeof(Table *));

				tab->table[adr]->table[0] = (Table *)calloc(1, sizeof(Table));

				tab->table[adr]->table[0]->Key = Key;

				tab->table[adr]->table[0]->Value = (char *)calloc(size, sizeof(char));

				tab->table[adr]->table[0]->Value = &(*(Value));

				tab->table[adr]->table[0]->Size = size;

				for (int i = 0; i < 32; i++){

					tab->table[adr]->table[0]->bitmap[i] = 0;

				}

				return;

			}

		}

		else {

			lvl++;

			int k = 0;

			for (int i = 0; i < adr2; i++)

				k += tab->table[adr]->bitmap[i];

			for (int i = 0; i <= k; i++)

				insertcharlvl(tab->table[adr]->table[k],Key, Value, size, lvl);

		}

	}

}


Table * fullsearch(Table *t ,int Key){

	return search(t , Key, 1);

}

Table* search(Table *tab , int Key_s, int lvl){

	int adr = hash(Key_s, lvl);

	if (lvl > 5) return NULL;

	int t = 0;
	if (tab->table != NULL){

		for (int i = 0; i < 32; i++)

			t += tab->table[adr]->bitmap[i];

	}

	else {

		return NULL;

	}

	if (tab->table[adr]->Key != 0 || t>0){

		if (tab->table[adr]->Key == Key_s){

			return tab->table[adr];

		}
		else {

			if (t == 0){

				return NULL;

			}

			lvl++;

			int adr2 = hash(Key_s, lvl);

			if (tab->table[adr]->bitmap[adr2] == 1){

				int numofptr = 0;

				for (int i = 0; i < adr2; i++)

					if (tab->table[adr]->bitmap[i] == 1) numofptr++;

				if (tab->table[adr]->table[numofptr]->Key == Key_s)

					return tab->table[adr]->table[numofptr];

				lvl++;

				return search(tab->table[adr]->table[numofptr], Key_s, lvl);

			}
			else {

				return NULL;

			}

		}

	}
	else { return NULL; }



}

void print(Table *t){

	printf("************\nKey: %d\nValue: %s\n************\n", t->Key, t->Value);

}



void newTable(Table* t) {

	t->table = (Table **)calloc(32, sizeof(Table *));

	for (int i = 0; i < 32; i++){

		t->bitmap[i] = 0;

		t->table[i] = (Table *)calloc(1, sizeof(Table));

	}

}

 void deleteTable(Table *t) {

	 for (int i = 0; i < 32; i++){
		 free(t->table[i] = (Table *)calloc(1, sizeof(Table)));
	 }
	 free(t->table);

}

 Table* getparant(Table *tab, int Key_s, int lvl){
	 int adr = hash(Key_s, lvl);

	 if (lvl > 5) return NULL;

	 int t = 0;
	 if (tab->table != NULL){

		 for (int i = 0; i < 32; i++)

			 t += tab->table[adr]->bitmap[i];

	 }

	 else {

		 return NULL;

	 }

	 if (tab->table[adr]->Key != 0 || t>0){

		 if (tab->table[adr]->Key == Key_s){

			 return tab;

		 }
		 else {

			 if (t == 0){

				 return NULL;

			 }

			 lvl++;

			 int adr2 = hash(Key_s, lvl);

			 if (tab->table[adr]->bitmap[adr2] == 1){

				 int numofptr = 0;

				 for (int i = 0; i < adr2; i++)

					 if (tab->table[adr]->bitmap[i] == 1) numofptr++;

				 if (tab->table[adr]->table[numofptr]->Key == Key_s)

					 return tab->table[adr];

				 lvl++;

				 return search(tab->table[adr]->table[numofptr], Key_s, lvl);

			 }
			 else {

				 return NULL;

			 }

		 }

	 }
	 else { return NULL; }



 }


int getlvl(Table *tab, int Key_s, int lvl){
	 int adr = hash(Key_s, lvl);

	 if (lvl > 5) return NULL;

	 int t = 0;
	 if (tab->table != NULL){

		 for (int i = 0; i < 32; i++)

			 t += tab->table[adr]->bitmap[i];

	 }

	 else {

		 return NULL;

	 }

	 if (tab->table[adr]->Key != 0 || t>0){

		 if (tab->table[adr]->Key == Key_s){

			 return lvl;

		 }
		 else {

			 if (t == 0){

				 return NULL;

			 }

			 lvl++;

			 int adr2 = hash(Key_s, lvl);

			 if (tab->table[adr]->bitmap[adr2] == 1){

				 int numofptr = 0;

				 for (int i = 0; i < adr2; i++)

					 if (tab->table[adr]->bitmap[i] == 1) numofptr++;

				 if (tab->table[adr]->table[numofptr]->Key == Key_s)

					 return lvl;

				 lvl++;

				 return lvl;

			 }
			 else {

				 return NULL;

			 }

		 }

	 }
	 else { return NULL; }



 }

void deletekey(Table *tab, int key){
	int adr = hash(key, getlvl(tab, key, 1));
	Table * par = getparant(tab, key, 1);
	par->bitmap[adr] = 0;
	Table *p = fullsearch(tab, key);
	if (p != NULL){
	p->Key = 0;
	p->Size = 0;
	p->Value = NULL;
	for (int i = 0; i < 32; i++)
		p->bitmap[i] = 0;
	deleteTable(p);
	par->table[adr] = NULL;
}
