#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../View/view.h"
#include "controler.h"

#include "../Utilities/StringVector.h"

#include "../Model/Data.h"
#include "../Model/Tuple.h"
#include "../Model/Column.h"
#include "../Model/Table.h"
#include "../Model/Database.h"

#include "DatabaseControler.h"

const char illegalChar[] = {'*', '<', '>', '=', '.', '\0'};

/**
 * retourne \0 si la chaine n'est pas illégal, sinon le retourne le caractère illégal
 */
static char illegalName(char* str)
{
	for (;*str; str++)
	{
		int i;

		for (i = 0; illegalChar[i]; i++)
			if (*str == illegalChar[i])
				return *str;
	}
	return '\0';
}

static void disp_table_control_error(char *header, char *arg, DisplayFunc fct)
{
	char* error;
	if (header == NULL || arg == NULL || fct == NULL)
		return;

	error = (char*) malloc( ( sizeof(char) * strlen(header) + ( sizeof(char) * strlen(arg) + 1 ) ) );

	if (error == NULL)
		return;

	sprintf(error, "%s%s", header, arg);

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
		return;
	}

	if (illegalName(request->tab[2]))
	{
		char illChar[1];
		*illChar = illegalName(request->tab[2]);

		disp_table_control_error(ILLEGAL_NAME, request->tab[2], fct);
		disp_table_control_error(ILLEGAL_CHARACTER, illChar, fct);
		return;
	}

	t = createTable(request->tab[2]);
	addTable(db, t);

	fct("OK");
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

	fct("OK");
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

	fct("OK");
}
