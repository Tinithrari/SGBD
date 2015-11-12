#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Column.h"

Column *createColumn(char *name, char *type)
{
	Column *col;

	/** 
	  * Check if one of parameters is NULL
	  * In this case, the function return NULL
	  */

	if ( name == NULL || type == NULL )
		return NULL;

	col = malloc ( sizeof ( Column ) );

	// If malloc fail, return NULL
	if (col == NULL)
		return NULL;

	// Allocate two char table, which has a length of the length of the corresponding parameter + 1 
	col->name = calloc ( strlen ( name ) + 1 , sizeof ( char ) );
	col->type = calloc ( strlen ( type ) + 1 , sizeof ( char ) );

	// Copy the contains of the parameter in the field of Column struct
	strcpy ( col->name , name );
	strcpy ( col->type , type );

	return col;
}

void deleteColumn(Column *col)
{
	// Delete the name and the type of the column
	free ( col->name );
	free ( col->type );

	// Delete the column
	free ( col );
}
