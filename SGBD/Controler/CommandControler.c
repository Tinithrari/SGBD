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


typedef struct
{
	char** tab;
	int nbMot;
} TabMot;

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

static TabMot* cutStr(char* str)
{
	int i,nbMot,nbLettre,entreQuote,firstSpace;
	TabMot* tabDeMot;
	char** tab;

	tab = (char**) malloc(sizeof(char*));

	for (i = 0, nbMot = 0, nbLettre = 0, entreQuote = 0, firstSpace = 0; *(str + i); i++)
	{
		if (*(str + i) == '"')
		{
			entreQuote = !entreQuote;
			nbLettre++;
		}
		else if (!entreQuote && firstSpace && *(str + i) == ' ')
		{
			char **newPointer;
			newPointer = realloc(tab, sizeof(char*) * (nbMot + 1));
			*(tab + nbMot) = (char*) malloc(sizeof(char) * (nbLettre + 1) );
			nbMot++;
			nbLettre = 0;
			firstSpace = 0;
		}
		else if(!entreQuote && !firstSpace && *(str + i) == ' ')
		{

		}
		else
		{
			nbLettre++;
		}
	}

	for (i = 0, nbMot = 0, nbLettre = 0, entreQuote = 0, firstSpace = 0; *(str + i); i++)
	{
		if (*(str + i) == '"')
		{
			entreQuote = !entreQuote;
			*(*(tab + nbMot) + nbLettre) = *(str + i);
			nbLettre++;
		}
		else if (!entreQuote && firstSpace && *(str + i) == ' ')
		{
			nbMot++;
			nbLettre = 0;
		}
		else if(!entreQuote && !firstSpace && *(str + i) == ' ')
		{
		}
		else
		{
			*(*(tab + nbMot) + nbLettre) = *(str + i);
			nbLettre++;
		}
	}

	tabDeMot = (TabMot*) malloc(sizeof(TabMot));

	tabDeMot->tab = tab;
	tabDeMot->nbMot = nbMot;

	return tab;
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
	else if (! strcmp(substr, DISPLAY_KEYWORD) )
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
	}
	free(substr);
}
