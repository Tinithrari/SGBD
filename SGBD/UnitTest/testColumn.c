#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../Model/Data.h"
#include "../Model/Column.h"

#define NAME "id"
#define SUCCESS "Unit Test for Column has been executed succesfully"

int main(void)
{
	Column *col;

	col = createColumn(NAME, INT);

	assert ( ! strcmp ( col->name , NAME ) );
	assert (col->type == INT );

	deleteColumn ( col );

	printf("%s\n", SUCCESS);
}
