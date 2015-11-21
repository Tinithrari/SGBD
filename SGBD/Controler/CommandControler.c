#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../VIew/view.h"
#include "Data.h"
#include "Column.h"
#include "Tuple.h"
#include "Table.h"
#include "Database.h"
#include "CommandControler.h"

/*
 * Convert lower case character of a char* to upper case character
 */
static void toUpperCase(char *str)
{
	if (str == NULL)
		return;

	for (;;str++)
		if (*str >= 'a' && *str <= 'z')
			*str = *str - 'a' + 'A';
}

char* getStrBeforeCarac(char* str, char delimiter)
{
	int i;
	char* sub;

	if (str == NULL)
		return NULL;

	for (i = 0; *(str + i) && *(str + i) != delimiter; i++);

	if (! *(str + i))
		return NULL;

	sub = (char*) malloc( sizeof(char) * (i + 1) );

	sub = strncpy(sub, str, i);

	return sub;
}

void commandManager(Database *db, char *command, DisplayFunc fct)
{
	char *substr;

	if (db == NULL || command == NULL)
		return;

	// On récupère les trois premiers caractères
	substr = getStrBeforeCarac(command, ' ');

	if (substr == NULL)
	{
		char* error = "%s%s%s";

		sprintf(error, ERROR_HEADER, UNKNOWN_KEYWORD, command);
		fct(error);
		return;
	}

	toUpperCase(substr);

	if (! strcmp(substr, ADD_KEYWORD))
	{

	}
	else if (! strcmp(substr, DELETE_KEYWORD) )
	{

	}
	// Si le début ne correspond pas à un ajout ou une suppression, on vérifie s'il s'agit d'une requête d'affichage, ou de quitter le programme
	else
	{
		free(substr);
		substr = substring(command, 0, 4);
		toUpperCase(substr);

		if (! strcmp(substr, DISPLAY_KEYWORD) )
		{

		}
		else if (! strcmp(substr, QUIT_KEYWORD) )
		{

		}
		else
		{
			char* error = "%s%s%s";

			sprintf(error, ERROR_HEADER, UNKNOWN_KEYWORD, substr);
			fct(error);
			return;
		}
	}
}
