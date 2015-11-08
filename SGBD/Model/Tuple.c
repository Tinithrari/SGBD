#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "Tuple.h"

Tuple *createTuple ( unsigned int size )
{
	Tuple *t = (Tuple*) malloc ( sizeof ( Tuple ) );

	// Check if malloc has not fail, return NULL in this case
	if (t == NULL || size == 0)
		return NULL;

	// Allocate the number of data needed for the database
	t->datas = calloc( size , sizeof ( Data* ) );

	// Set default properties
	t->nb_datas = 0;
	t->size = size;

	return t;
}

int addStrData ( Tuple *t , char* value )
{
	Data* d;

	// If the tuple is NULL, return false
	if ( t == NULL )
		return 0;

	d = createStrData(value);

	// if the data has not been allocated then return NULL
	if ( d == NULL )
		return 0;

	// Check the capacity of tuple and resize it if needed
	if ( t->nb_datas == t->size )
		t->datas = realloc( t->datas , ++t->size );

	// Add the data into the tuple and increment the number of data
	*(t->datas + t->nb_datas) = d;
	t->nb_datas++;

	return 1;
}

int addIntData (Tuple *t, int value)
{
	Data* d;

	// If the tuple is NULL
	if (d == NULL)
		return 0;

	d = createIntData(value);

	// If the data is not allocated, return false
	if ( d == NULL )
		return 0;

	// Check the capacity of tuple and resize it if needed
	if ( t->nb_datas == t->size )
		t->datas = realloc( t->datas , ++t->size );

	*(t->datas + t->nb_datas) = d;
	t->nb_datas++;

	return 1;
}

int removeData ( Tuple *t, unsigned int index )
{
	int i;

	// Check if t is not NULL and index is not out of array
	if ( t == NULL && t->size <= index )
		return 0;

	// Free the data into the array at the specified array
	free( (t->datas + index) );

	// move data in the previous slot
	for ( i = index; i < t->size - 1; i++ )
		*(t->datas + i) = *(t->datas + i + 1);

	// resize the size of array
	realloc( t->datas, --t->size );

	return 1;
}

void deleteTuple ( Tuple *t )
{
	int i;

	// if t is NULL, do nothing
	if ( t == NULL )
		return;

	// Free each data contain in the tuple
	for (i = 0; i < t->size; i++)
		deleteData(*(t->datas + i));

	// free the tuple
	free(t);
}
