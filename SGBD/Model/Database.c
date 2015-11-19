#include <stdlib.h>
#include <string.h>

#include "Table.h"
#include "Database.h"

Database *createDatabase()
{
	Database *db = (Database*) malloc(sizeof(Database));

	db->nb_table = 0;
	db->tables = NULL;

	return db;
}

int addTable(Database *db, Table* table)
{
	Table **newPointer;

	if (db == NULL || table == NULL)
		return 0;

	newPointer = (Table**) realloc(db->tables, (db->nb_table + 1) * sizeof(Table*));

	if (newPointer == NULL)
		return 0;

	db->tables = newPointer;

	*(db->tables + db->nb_table + 1) = table;

	++(db->nb_table);

	return 1;
}

Table *getTableByName(Database *db, char *name)
{
	int i;

	if (db == NULL || name == NULL)
		return NULL;

	for (i = 0; i < db->nb_table; i++)
		if ( ! strcmp( (*(db->tables + i) )->name, name) )
			return (*(db->tables + i) );

	return NULL;
}

int removeTable(Database *db, char *name)
{
	int i,j;
	Table *table;

	if (db == NULL || name == NULL)
		return 0;

	for (i = 0; i < db->nb_table; i++)
		if ( ! strcmp( (*(db->tables + i) )->name, name) )
		{
			table = *(db->tables + i);
			break;
		}

	if (table == NULL)
		return 0;

	deleteTable(table);

	for (j = i; j < db->nb_table - 1; j++)
		*(db->tables + j) = *(db->tables + j + 1);

	realloc(db->tables, (db->nb_table - 1) * sizeof(Table*));

	return 1;
}

void deleteDatabase(Database *db)
{
	int i;

	if (db == NULL)
		return;

	for (i = 0; i < db->nb_table; i++)
		deleteTable( *(db->tables + i));

	free(db->tables);
	free(db);
}
