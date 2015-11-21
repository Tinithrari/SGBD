#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../View/view.h"
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
	*(sub + i) = '\0';

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
		char* error = "%s%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_KEYWORD) + strlen(command) + 1) );

		sprintf(buffer, error, ERROR_HEADER, UNKNOWN_KEYWORD, command);
		fct(buffer);

		free(buffer);
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
			char* error = "%s%s%s", buffer;

			buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_KEYWORD) + strlen(substr) + 1) );

			sprintf(buffer, error, ERROR_HEADER, UNKNOWN_KEYWORD, substr);
			fct(buffer);

			free(buffer);
			free(substr);

			return;
		}
	}
}
