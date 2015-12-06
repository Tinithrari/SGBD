#include <stdlib.h>

#include "view.h"
#include "controler.h"

#include "../Utilities/StringVector.h"

#include "../Model/Data.h"
#include "../Model/Tuple.h"
#include "../Model/Column.h"
#include "../Model/Table.h"
#include "../Model/Database.h"

#include "TableControler.h"

static int isNumeric(char *param)
{
	if (param == NULL)
		return 0;

	for (;*param && *param >= '0' && *param <= '9'; param++);

	return *param == '\0';
}

static int isString(char *param)
{
	if (param == NULL || *param != '"')
		return 0;

	for (param++; *param; param++)
		if (*param == '"' && *(param + 1) == '\0')
			return 1;
		else
			return 0;
	return 0;
}

static void toUpperCase(char* phrase)
{
	for(;*phrase;phrase++)
		*phrase = toUpper(*phrase);
}

static void disp_classic_error(char *header, char *arg, DisplayFunc fct)
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

void addColInTable(Database *db, StringVector *request, DisplayFunc fct)
{
	Table *t;
	Column *c;

	if (db == NULL || request == NULL || fct == NULL)
		return;

	if (request->length < 5)
	{
		fct(NOT_ENOUGH_WORDS);
	}
	else if (request->length > 5)
	{
		fct(TOO_MUCH_WORDS);
	}

	if (! (t = getTableByName(db, request->tab[2])) )
	{
		disp_classic_error(UNKNOWN_TABLE, request->tab[2], fct);
		return;
	}

	if (getColumn(t, request->tab[3]))
	{
		disp_classic_error(EXISTING_COL, request->tab[3], fct);
		return;
	}

	toUpperCase(request->tab[4]);

	if ( strcmp(request->tab[4], TYPE_INT) && strcmp(request->tab[4], TYPE_STRING) )
	{
		disp_classic_error(UNKNOWN_TYPE, request->tab[4]);
		return;
	}

	c = createColumn(request->tab[3], ! strcmp(request->tab[4], TYPE_INT) ? INT : STR);

	addColumn(t, c);
}

void addTupleInTable(Database *db, StringVector *request, DisplayFunc fct)
{

}

void delColFromTable(Database *db, StringVector *request, DisplayFunc fct)
{

}

void delTupleFromTable(Database *db, StringVector *request, DisplayFunc fct)
{

}

void dispColsFromTable(Database *db, StringVector *request, DisplayFunc fct)
{

}
void dispTuplesFromTable(Database *db, StringVector *request, DisplayFunc fct)
{

}

