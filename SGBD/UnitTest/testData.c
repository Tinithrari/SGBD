#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../Model/Data.h"

#define SUCCESS_STRING "Unit Test for Data has been executed succesfully\n"
#define STR_TEST "Hello World !"
#define INT_TEST 8

int main(void)
{
	Data *myData;

	myData = createStrData(STR_TEST);

	if (myData != NULL)
	{
		assert(! strcmp(myData->value.str, STR_TEST));
		assert(! strcmp(myData->type, STR));
		deleteData(myData);
	}
	else
		printf("myData non alloué");

	myData = createIntData(INT_TEST);

	if (myData != NULL)
	{
		assert(myData->value.integer == INT_TEST);
		assert(! strcmp(myData->type, INT));
		deleteData(myData);
	}
	else
		printf("myData non alloué 2");

	printf(SUCCESS_STRING);
}
