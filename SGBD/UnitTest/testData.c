#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../Model/Data.h"

#define SUCCESS_STRING "Unit Test for Data has been executed succesfully"
#define STR_TEST "Hello World !"
#define INT_TEST 8

int main(void)
{
	Data *myData;
	DataValue val;

	val.str = STR_TEST;
	myData = createData(STR, val);

	if ( myData != NULL )
	{
		assert(! strcmp( myData->value.str, STR_TEST ) );
		assert(myData->type == STR );
		deleteData(myData);
	}
	else
		printf("myData non alloué");

	val.integer = INT_TEST;
	myData = createData( INT, val );

	if ( myData != NULL )
	{
		assert(myData->value.integer == INT_TEST);
		assert(myData->type == INT);
		deleteData( myData );
	}
	else
		printf("myData non alloué 2");

	printf("%s\n", SUCCESS_STRING);
}
