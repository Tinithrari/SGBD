#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "Column.h"
#include "Tuple.h"
#include "Table.h"

Table *createTable ( char *name )
{
	Table *table;

	// Check if the table is NULL, in this case, return NULL
	if ( name == NULL )
		return NULL;

	// Try to allocate the table and check if the allocation has been done successfully
	if ( ( table = (Table*)malloc( sizeof(Table) ) ) == NULL )
		return NULL;

	// Set default value
	table->name = (char*) calloc( ( strlen(name) + 1 ), sizeof(char) );

	if (table->name == NULL)
	{
		free(table);
		return NULL;
	}

	table->name = strcpy(table->name, name);
	table->nbColumn = 0;
	table->nbTuple = 0;
	table->tuples = NULL;
	table->columns = NULL;

	// return the table
	return table;
}

int addColumn ( Table *table, Column *column )
{
	DataValue nullValue;
	int i;
    Column** newPointer;
	// Check if the table and the column exist, return 0 if not exist
	if (table == NULL || column == NULL)
		return 0;

	// Reallocation or allocation of memory to add the column, if it fails, return 0
	if ( ( newPointer = (Column**)realloc(table->columns, (table->nbColumn + 1) * sizeof(Column*) ) ) == NULL )
		return 0;

	nullValue.str = NULLVALUE;

	// Set the new value of the tuple equals to "NULL"
	for (i = 0; i < table->nbTuple; i++)
		addData( *(table->tuples + i), createData(STR, nullValue));

    table->columns = newPointer;

	// Add the column into the table
	*(table->columns + (table->nbColumn)) = column;

	(table->nbColumn)++;

	return 1;
}

int addTuple ( Table *table, Tuple *tuple )
{
	int i;
    Tuple** newPointer;
	// Check if the table and the tuple exist, return 0 if they not
	if (table == NULL || tuple == NULL)
		return -3;

	// Check if there are not too much argument in the tuple
	if (tuple->nb_datas > table->nbColumn)
		return -2;

	// Check if there are no problem with type
	for (i = 0; i < tuple->nb_datas; i++)
		if ( (*(tuple->datas + i))->type != (*(table->columns + i))->type &&
				!( (*(tuple->datas + i))->type == STR && !strcmp( (*(tuple->datas + i))->value.str, NULLVALUE) ))
			return i + 1;

	// Reallocation or allocation of memory to add the tuple, if it fails, return 0
	if ( (newPointer = (Tuple**) realloc( table->tuples, (table->nbTuple + 1) * sizeof(Tuple*) )) == NULL )
		return -1;

    table->tuples = newPointer;

	*(table->tuples + table->nbTuple) = tuple;

	table->nbTuple++;

	return 0;
}

int getColumnIndex ( Table *table, char *name )
{
	int index;

	// Check if the table and the name are NULL, return -1 in this case
	if (table == NULL || name == NULL)
		return -1;

	// Browse the array of column and return the index if it found the name of the column
	for (index = 0; index < table->nbColumn; index++)
		if (! strcmp(name, ( *( table->columns + index ) )->name ) )
			return index;

	// If it not found the column index, return -1
	return -1;
}

Column *getColumn ( Table *table, char *name )
{
	int index;

	// Check if the table and the name are NULL, return NULL in this case
	if (table == NULL || name == NULL || table->columns == NULL)
			return NULL;

	// Browse the array of column and return the column if it the name of the column has been found
	for (index = 0; index < table->nbColumn; index++)
		if (! strcmp(name, ( *( table->columns + index ) )->name ) )
			return *( table->columns + index );

	// If there are no column with this name, return NULL
	return NULL;
}

int removeColumn ( Table *table, char *name )
{
	int indexOfColumn, indexOfTuple, i;
	Column** newPointer;

	// If the name is NULL or the column doesn't exists, or the table has no column, return 0
	if ( name == NULL || table == NULL || ( indexOfColumn = getColumnIndex(table, name) ) == -1 )
		return 0;

	// Delete the column of the list and decrease the number of column
	deleteColumn( *(table->columns + indexOfColumn) );
	--(table->nbColumn);

	// Reorganize the column in the array
	for (i = indexOfColumn; i < (table->nbColumn); i++)
		*(table->columns + i) = *(table->columns + i + 1);

	newPointer = (Column**)realloc(table->columns, (table->nbColumn) * sizeof(Column*));

	table->columns = newPointer;

	// Browse the tuple and delete the data associated to the column
	for (indexOfTuple = 0; indexOfTuple < table->nbTuple; indexOfTuple++)
		removeData( *(table->tuples + indexOfTuple),  indexOfColumn);

	return 1;
}

void deleteTable (Table *table)
{
	int i;
	// If the table doesn't exists, return 0
	if ( table == NULL )
		return;

	// Delete all the column and tuple
	for (i = 0; i < table->nbColumn; i++)
		deleteColumn(*(table->columns + i));

	for (i = 0; i < table->nbTuple; i++)
		deleteTuple(*(table->tuples + i));

	// Free the table
	free(table->name);
	free(table->columns);
	free(table->tuples);
	free(table);
}
