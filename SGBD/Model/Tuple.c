#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "Tuple.h"

Tuple *createTuple ( unsigned int size )
{
	Tuple *t = (Tuple*) malloc ( sizeof ( Tuple ) );

	// Check if malloc has not fail, return NULL in this case
	if (t == NULL || size == 0)
    {
        free(t);
		return NULL;
    }

	// Allocate the number of data needed for the database
	t->datas = calloc( size , sizeof ( Data* ) );

	// Set default properties
	t->nb_datas = 0;
	t->size = size;

	return t;
}

int addData ( Tuple *t , Data* data )
{
    Data **newPointer;
	// If the tuple or the data are NULL, return false
	if ( t == NULL  || data == NULL )
		return 0;

	// Check the capacity of tuple and resize it if needed
	if ( t->nb_datas == t->size )
    {
		if ( (newPointer = (Data**)realloc( t->datas , (t->size + 1) * sizeof( Data* ) )) == NULL)
			return 0;

		t->size++;
        t->datas = newPointer;
    }

	// Add the data into the tuple and increment the number of data
	*(t->datas + t->nb_datas) = data;
	t->nb_datas++;

	return 1;
}


int removeData ( Tuple *t, unsigned int index )
{
	int i;
	Data** newPointer;

	// Check if t is not NULL and index is not out of array
	if ( t == NULL || t->size <= index )
		return 0;

	// Free the data into the array at the specified array
	deleteData( *(t->datas + index) );

	// move data in the previous slot
	for ( i = index; i < (t->nb_datas - 1); i++ )
		*(t->datas + i) = *(t->datas + i + 1);

	// resize the size of array
	if ( (t->nb_datas - 1))
	{
		if ( ( newPointer = (Data**)realloc( t->datas, (t->nb_datas - 1) * sizeof(Data*) )) == NULL )
			return 0;
		else
		{
			(t->size) = t->nb_datas - 1;
			t->datas = newPointer;
		}
	}

    (t->nb_datas)--;

	return 1;
}

void deleteTuple ( Tuple *t )
{
	int i;

	// if t is NULL, do nothing
	if ( t == NULL )
		return;

	// Free each data contain in the tuple
	for (i = 0; i < t->nb_datas; i++)
		deleteData( *(t->datas + i) );

	// free the tuple
	free(t->datas);
	free(t);
}

Data *getDataByIndex( Tuple *tuple, unsigned int index )
{
	// If the tuple is NULL or the index is out of array
	if (tuple == NULL || tuple->nb_datas < index )
		return NULL;

	return *(tuple->datas + index);
}
