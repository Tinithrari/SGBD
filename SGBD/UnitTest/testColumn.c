#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../Model/Column.h"

#define NAME "id"
#define TYPE "int"
#define SUCCESS "Unit Test for Column has been executed succesfully"

int main(void)
{
	Column *col;

	col = createColumn(NAME, TYPE);

	assert ( ! strcmp ( col->name , NAME ) );
	assert ( ! strcmp ( col->type , TYPE ) );

	removeColumn ( col );

	printf("%s\n", SUCCESS);
}