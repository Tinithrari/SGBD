#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Column.h"
#include "Tuple.h"
#include "Data.h"
#include "Table.h"

#define MY_INT_DATA 5
#define COLUMN_NAME "FirstColumn"
#define TABLE_NAME "FirstTable"
#define SUCCESS "DONE !"

int main()
{
	Data* data;
	Column* col;
	Tuple* tuple;
	Table* table;

	data = createData(INT, MY_INT_DATA);

	col = createColumn(COLUMN_NAME, INT);
	assert(col != NULL);

	tuple = createTuple(1);
	addData(tuple, data);

	table = createTable(TABLE_NAME);

	// Test l'ajout d'une colonne, puis d'un tuple
	assert(addColumn(table, col));
	assert(addTuple(table, tuple));

	// Teste la suppression de colonne
	assert(removeColumn(table, COLUMN_NAME));

	data = createData(INT, MY_INT_DATA);
	tuple = createTuple(1);
	addData(tuple, data);

	// Teste un ajout incorrecte de tuple
	assert(! addTuple(table, tuple));

	deleteTuple(tuple);

	printf("%s\n", SUCCESS);
}
