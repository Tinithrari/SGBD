#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Data.h"

Data *createStrData(char* str)
{

	Data *data;
   /*
	* Check if the string is NULL
	* In this case, send an error message on the standard error output
	* And return NULL
	*/
	if (str == NULL)
	{
		fprintf(stderr, "Error : string not specified");
		return NULL;
	}

	// Dynamic allocation of a data structure
	data = (Data *) malloc(sizeof(Data));

	// Check if the struct is not allocated, return NULL in this case
	if (data == NULL)
		return NULL;

	// Fill the data structure
	data->value.str = calloc( strlen(str) + 1 , sizeof(char) );
	strcpy(data->value.str, str);
	data->type = STR;

	return data;
}

Data *createIntData(int integer)
{
	Data *data;

	// Dynamic allocation of a data structure
	data = (Data *) malloc(sizeof(Data));

	// Check if data is not allocated, return NULL in this case
	if (data == NULL)
		return NULL;

	// Fill the data structure
	data->value.integer = integer;
	data->type = INT;

	return data;
}

void deleteData(Data *data)
{
// If data is NULL, do nothing
	if (data == NULL)
		return;

	if (! strcmp(data->type, STR))
		free(data->value.str);

	free(data);
}
