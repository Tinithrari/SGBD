#include <stdlib.h>
#include <string.h>

#include "view.h"
#include "controler.h"

#include "../Utilities/StringVector.h"

#include "../Model/Data.h"
#include "../Model/Tuple.h"
#include "../Model/Column.h"
#include "../Model/Table.h"
#include "../Model/Database.h"

#include "DatabaseControler.h"

static void disp_table_control_error(char *header, char *arg, DisplayFunc fct)
{
	char* error;
	if (header == NULL || arg == NULL || fct == NULL)
		return;

	error = (char*) malloc( ( sizeof(char) * strlen(header) + ( sizeof(char) * strlen(arg) + 1 ) ) );

	if (error == NULL)
		return;

	ssprintf(error, "%s%s", header, arg);

	fct(error);

	free(error);
}

void addTableInDatabase(Database *db, StringVector *request, DisplayFunc fct)
{
	Table *t;

	if (db == NULL || request == NULL || fct == NULL)
		return;

	if (request->length < 3)
	{
		fct(NOT_ENOUGH_WORDS);
		return;
	}

	if (getTableByName(db, request->tab[2]))
	{
		disp_table_control_error(EXISTING_TABLE, request->tab[2], fct);
	}

	t = createTable(request->tab[2]);
	addTable(db, t);
}

void deleteTableFromDatabase(Database *db, StringVector *request, DisplayFunc fct)
{
	Table *t;

	if (db == NULL || request == NULL || fct == NULL)
		return;


	if (request->length < 3)
	{
		fct(NOT_ENOUGH_WORDS);
		return;
	}

	if (! removeTable(db, request->tab[2]))
	{
		disp_table_control_error(UNKNOWN_TABLE, request->tab[2], fct);
	}
}

void displayTablesFromDatabase(Database *db, StringVector *request, DisplayFunc fct)
{
	int i;
	if (db == NULL || request == NULL || fct == NULL)
		return;

	if (request->length > 2)
	{
		fct(TOO_MUCH_WORDS);
		return;
	}

	for (i = 0; i < db->nb_table; i++)
		fct( (*(db->tables + i))->name );
}
