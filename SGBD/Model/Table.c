#include <stdlib.h>

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
	if ( ( table = malloc( sizeof(Table) ) ) == NULL )
		return NULL;

	// Set default value
	table->name = name;
	table->nbColumn = 0;
	table->nbTuple = 0;

	// return the table
	return table;
}

int addColumn ( Table *table, Column *column )
{
	// Check if the table and the column exist, return 0 if not exist
	if (table == NULL && column == NULL)
		return 0;

	// Reallocation or allocation of memory to add the column, if it fails, return 0
	if ( realloc(table->columns, sizeof(Column*) * ++(table->nbColumn) ) == NULL )
		return 0;

	// Add the column into the table
	*(table->columns + table->nbColumn) = column;

	return 1;
}

int addTuple ( Table *table, Tuple *tuple )
{
	// Check if the table and the tuple exist, return 0 if they not
	if (table == NULL && tuple == NULL)
		return 0;

	// Check if there are enough column to add a tuple
	if (table->nbTuple + 1 > table->nbColumn)
		return 0;

	// Reallocation or allocation of memory to add the tuple, if it fails, return 0
	if ( realloc(table->tuples, sizeof(Tuple*) * ++(table->nbTuple) ) == NULL )
		return 0;

	*(table->tuples + table->nbTuple) = tuple;

	return 1;
}

static int getColumnIndex(Table *table, char *name)
{
	int index;

	// Check if the table and the name are NULL, return -1 in this case
	if (table == NULL && name == NULL)
		return -1;

	// Browse the array of column and return the index if it found the name of the column
	for (index = 0; index < table->nbColumn; index++)
		if (! strcmp(name, ( *( table->columns + index ) )->name ) )
			return index;

	// If it not found the column index, return -1
	return -1;
}

int removeColumn ( Table *table, char *name )
{
	int indexOfColumn, indexOfTuple;

	// If the name is NULL or the column doesn't exists, or the table has no column, return 0
	if ( name == NULL && table->columns == NULL && ( indexOfColumn = getColumnIndex(name) ) == -1 )
		return 0;

	// Delete the column of the list and decrease the number of column
	removeColumn( *(table->columns + indexOfColumn) );
	--(table->nbColumn);

	// Browse the tuple and delete the data associated to the column
	for (indexOfTuple = 0; indexOfTuple < table->nbTuple; indexOfTuple++)
		deleteData( removeData( *(table->tuples + indexOfTuple), indexOfColumn) );

	return 1;
}

int deleteTable (Table *table)
{
	// If the table doesn't exists, return 0
	if ( table == NULL )
		return 0;

	// Delete all the column and tuple
	for (;table->nbColumn;)
		removeColumn(*table->columns);

	// Free the table
	free(table->columns);
	free(table->tuples);
	free(table);

	return 1;
}
