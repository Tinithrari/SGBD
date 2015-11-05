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

int removeStrData ( Tuple *t , char* value )
{
	int i;

	for ( i = 0; i < t->nb_datas; i++ )
	{
		// Check if the type is corresponding with value researched
		// In this case, check if the values are equal, then delete it
		if ( ! strcmp( (*(t->datas + i))->type , STR ) )
			if ( ! strcmp ( (*(t->datas + i) )->value.str , value ) )
			{
				int j;

				// Delete the data
				deleteData ( t->datas[i] );

				// decale the oter data
				for (j = i; j < t->size - 1; j++)
					t->datas[j] = t->datas[j + 1];

				t->nb_datas--;

				// Resize the tuple
				t->datas = realloc( t->datas , --t->size );

				return 1;
			}
	}
	return 0;
}

int removeIntData ( Tuple *t, int value)
{
	int i;

	for ( i = 0; i < t->nb_datas; i++ )
	{
		// Check if the type is corresponding with value researched
		// In this case, check if the values are equal, then delete it
		if ( ! strcmp( (*(t->datas + i))->type , INT ) )
			if ( t->datas[i]->value.integer == value )
			{
				int j;

				// Delete the data
				deleteData ( t->datas[i] );

				// Decale the other data
				for (j = i; j < t->size - 1; j++)
					t->datas[j] = t->datas[j + 1];

				t->nb_datas--;

				// Resize the tuple
				t->datas = realloc( t->datas , --(t->size) );

				return 1;
			}
	}
	return 0;
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
