#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#include "view.h"

#include "../Utilities/StringVector.h"

#include "../Model/Data.h"
#include "../Model/Tuple.h"
#include "../Model/Column.h"
#include "../Model/Table.h"
#include "../Model/Database.h"
#include "../Controler/DatabaseControler.h"
#include "../Controler/TableControler.h"

static void disp_unknown_keyword_error(char *mot, DisplayFunc fct)
{
	char* error;
	if (mot == NULL)
		return;

	error = (char*) malloc( ( sizeof(char) * strlen(mot) + ( sizeof(char) * strlen(UNKNOWN_KEYWORD) + 1 ) ) );

	if (error == NULL)
		return;

	sprintf(error, "%s%s", UNKNOWN_KEYWORD, mot);

	fct(error);

	free(error);
}

static void toUpperCase(char* phrase)
{
	for(;*phrase;phrase++)
		*phrase = toupper(*phrase);
}

static void analyseAddRequest(StringVector *request, DisplayFunc fct, Database *db)
{
	if (request->length < 2)
	{
		fct(NOT_ENOUGH_WORDS);
		return;
	}

	toUpperCase(request->tab[1]);

	if (! strcmp(request->tab[1], TABLE_KEYWORD))
	{
		addTableInDatabase(db, request, fct);
	}
	else if (! strcmp(request->tab[1], COL_KEYWORD))
	{
		addColInTable(db, request, fct);
	}
	else if (! strcmp(request->tab[1], TUPLE_KEYWORD))
	{
		addTupleInTable(db, request, fct);
	}
	else
	{
		disp_unknown_keyword_error(request->tab[1], fct);
	}
}

static void analyseDelRequest(StringVector *request, DisplayFunc fct, Database *db)
{
	if (request->length < 2)
	{
		fct(NOT_ENOUGH_WORDS);
		return;
	}

	toUpperCase(request->tab[1]);

	if (! strcmp(request->tab[1], TABLE_KEYWORD))
	{
		deleteTableFromDatabase(db, request, fct);
	}
	else if (! strcmp(request->tab[1], COL_KEYWORD))
	{
		delColFromTable(db, request, fct);
	}
	else
	{
		disp_unknown_keyword_error(request->tab[1], fct);
	}
}

static void analyseDispRequest(StringVector *request, DisplayFunc fct, Database *db)
{
	if (request->length < 2)
	{
		fct(NOT_ENOUGH_WORDS);
		return;
	}

	toUpperCase(request->tab[1]);

	if (! strcmp(request->tab[1], SET_TABLES_KEYWORD))
	{
		displayTablesFromDatabase(db, request, fct);
	}
	else if (! strcmp(request->tab[1], SET_COLS_KEWORD))
	{
		dispColsFromTable(db, request, fct);
	}
	else if (! strcmp(request->tab[1], SET_TUPLES_KEYWORD))
	{
		dispTuplesFromTable(db, request, fct);
	}
	else
	{
		disp_unknown_keyword_error(request->tab[1], fct);
	}
}

static void analyseQuitRequest(StringVector *request, DisplayFunc fct, Database *db)
{
	if (request->length > 1)
	{
		fct(TOO_MUCH_WORDS);
		return;
	}
	deleteStringVector(request);
	deleteDatabase(db);

	exit(0);
}

void analyzeRequest(StringVector *request, DisplayFunc fct, Database *db)
{
	if (request == NULL || fct == NULL || db == NULL)
		return;

	if (request->length == 0)
	{
		fct(NOT_ENOUGH_WORDS);
		return;
	}

	toUpperCase(request->tab[0]);

	if (! strcmp(request->tab[0], ADD_KEYWORD))
	{
		analyseAddRequest(request, fct, db);
	}
	else if (! strcmp(request->tab[0], DELETE_KEYWORD))
	{
		analyseDelRequest(request, fct, db);
	}
	else if (! strcmp(request->tab[0], DISPLAY_KEYWORD))
	{
		analyseDispRequest(request, fct, db);
	}
	else if (! strcmp(request->tab[0], QUIT_KEYWORD))
	{
		analyseQuitRequest(request, fct, db);
	}
	else
	{
		disp_unknown_keyword_error(request->tab[0], fct);
	}
}
