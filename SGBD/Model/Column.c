#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Data.h"
#include "Column.h"

Column *createColumn(char *name, DataType type)
{
	Column *col;

	/** 
	  * Check if one of parameters is NULL
	  * In this case, the function return NULL
	  */

	if ( name == NULL)
		return NULL;

	col = malloc ( sizeof ( Column ) );

	// If malloc fail, return NULL
	if (col == NULL)
		return NULL;

	// Allocate one char table, which has a length of the length of the corresponding parameter + 1
	// if it fails, return NULL
	if ( ( col->name = calloc ( strlen ( name ) + 1 , sizeof ( char ) ) ) == NULL )
		return NULL;

	col->type = type;

	// Copy the contains of the parameter in the field of Column struct
	strcpy ( col->name , name );

	return col;
}

void deleteColumn(Column *col)
{
	// Delete the name and the column
	free ( col->name );
	free ( col );
}
