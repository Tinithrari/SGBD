#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../Model/Data.h"
#include "../Model/Column.h"
#include "../Model/Tuple.h"
#include "../Model/Table.h"

#define MY_INT_DATA 5
#define COLUMN_NAME "FirstColumn"
#define TABLE_NAME "FirstTable"
#define SUCCESS "DONE !"

int main()
{
	Data* data;
	DataValue val;
	Column* col;
	Tuple* tuple;
	Table* table;

	val.integer = MY_INT_DATA;

	data = createData(INT, val);

	col = createColumn(COLUMN_NAME, INT);

	assert(col != NULL);
	assert(! strcmp(col->name, COLUMN_NAME) );
	assert(col->type == INT);

	tuple = createTuple(1);
	addData(tuple, data);

	table = createTable(TABLE_NAME);

    assert(table != NULL);
	// Test l'ajout d'une colonne, puis d'un tuple
	assert(addColumn(table, col));
	assert(addTuple(table, tuple));

	// Test pour vérifier que les données soient bien enregistré
	assert(! strcmp(getColumn(table, COLUMN_NAME)->name, col->name));
	assert( (*(table->tuples))->size == tuple->size);

	// Teste la suppression de colonne
	assert(removeColumn(table, COLUMN_NAME));

	data = createData(INT, val);
	tuple = createTuple(1);
	addData(tuple, data);

	// Teste un ajout incorrecte de tuple
	assert(! addTuple(table, tuple));

	deleteTuple(tuple);

	printf("%s\n", SUCCESS);
}
