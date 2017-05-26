#include "hashmap.h"


int main(){

	int Key = 54;

	int arraysize = 50;

	Table map;
	newTable(&map);

	for (int i = 51; i < 305; i++){

		if (i % 2 == 0){

			insertchar(&map, i, "Vasya", 5);

		}

		else {

			insertchar(&map, i, "Volodya", 7);

		}

	}

	for (int i = 51; i < 305; i++)

		if (fullsearch(&map, i) != NULL)

			print(&(*(fullsearch(&map, i))));

	deleteTable(&map);

	system("PAUSE");

	return 0;

}
