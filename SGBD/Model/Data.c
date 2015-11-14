#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Data.h"

Data *createData(DataType type, DataValue value)
{
	Data *data;

	if (type == STR && value.str == NULL)
		return NULL;

	// Dynamic allocation of a data structure
	data = (Data *) malloc(sizeof(Data));

	// Check if data is not allocated, return NULL in this case
	if (data == NULL)
		return NULL;

	// Put the value into the data
	if (type == STR)
	{
		data->value.str = (char*)malloc( strlen(value.str) + 1 );
		data->value.str = value.str;
	}
	else
		data->value.integer = value.integer;

	data->type = type;

	return data;
}

void deleteData(Data *data)
{
	// If data is NULL, do nothing
	if (data == NULL)
		return;

	if (data->type == STR)
		free(data->value.str);

	free(data);
}
