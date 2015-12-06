#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "view.h"

#include "../Utilities/StringVector.h"

#include "../Model/Data.h"
#include "../Model/Tuple.h"
#include "../Model/Column.h"
#include "../Model/Table.h"
#include "../Model/Database.h"

static void disp_unknown_keyword_error(char *mot)
{
	char* error;
	if (mot == NULL)
		return;

	error = (char*) malloc( ( sizeof(char) * strlen(mot) + ( sizeof(char) * strlen(UNKNOWN_KEYWORD) + 1 ) ) );

	if (error == NULL)
		return;

	ssprintf(error, "%s%s", UNKNOWN_KEYWORD, mot);

	fct(error);

	free(error);
}

static void toUpperCase(char* phrase)
{
	for(;*phrase;phrase++)
		*phrase = toUpper(*phrase);
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

	}
	else if (! strcmp(request->tab[1], COL_KEYWORD))
	{

	}
	else if (! strcmp(request->tab[1], TUPLE_KEYWORD))
	{

	}
	else
	{
		disp_unknown_keyword_error(request->tab[1]);
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

	}
	else if (! strcmp(request->tab[1], COL_KEYWORD))
	{

	}
	else if (! strcmp(request->tab[1], TUPLE_KEYWORD))
	{

	}
	else
	{
		disp_unknown_keyword_error(request->tab[1]);
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

	}
	else if (! strcmp(request->tab[1], SET_COLS_KEWORD))
	{

	}
	else if (! strcmp(request->tab[1], SET_TUPLES_KEYWORD))
	{

	}
	else
	{
		disp_unknown_keyword_error(request->tab[1]);
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
		disp_unknown_keyword_error(request->tab[0]);
	}
}
