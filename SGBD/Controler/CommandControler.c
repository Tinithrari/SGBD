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
#include "Controler.h"

#define MAX_ADD_TABLE 3
#define MAX_ADD_COL 5
#define MAX_ADD_TUPLE 4

#define MAX_DEL_TABLE 3
#define MAX_DEL_COL 3

#define MAX_DISP_TABLE 2
#define MAX_DISP_COL 3
#define MAX_DISP_TUPLE 3

#define MAX_QUIT 1

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

	return tabDeMot;
}

void commandManager(Database *db, char *command, DisplayFunc fct)
{
	TabMot *substr;

	if (db == NULL || command == NULL)
		return;

	// On récupère les trois premiers caractères
	substr = cutStr(command);

	if (substr->nbMot == 0)
	{
		char* error = "%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_WORDS) + 1) );

		sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_WORDS);
		fct(buffer);

		free(buffer);
		return;
	}

	toUpperCase(substr->tab[0]);

	if (! strcmp(substr->tab[0], ADD_KEYWORD))
	{
		if (! strcmp(substr->tab[1],TABLE_KEYWORD))
		{
			if (substr->nbMot > MAX_ADD_TABLE)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_ADD_TABLE)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{

			}
		}
		else if (! strcmp(substr->tab[1],COL_KEYWORD))
		{
			if (substr->nbMot > MAX_ADD_COL)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_ADD_COL)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{

			}
		}
		else if (! strcmp(substr->tab[1],TUPLE_KEYWORD))
		{
			if (substr->nbMot < MAX_ADD_TUPLE)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{

			}
		}
	}
	else if (! strcmp(substr->tab[0], DELETE_KEYWORD) )
	{
		if (! strcmp(substr->tab[1],TABLE_KEYWORD))
		{
			if (substr->nbMot > MAX_DEL_TABLE)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_DEL_TABLE)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{

			}
		}
		else if (! strcmp(substr->tab[1],COL_KEYWORD))
		{
			if (substr->nbMot > MAX_DEL_COL)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_DEL_COL)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{

			}
		}
	}
	// Si le début ne correspond pas à un ajout ou une suppression, on vérifie s'il s'agit d'une requête d'affichage, ou de quitter le programme
	else if (! strcmp(substr->tab[0], DISPLAY_KEYWORD) )
	{
		if (! strcmp(substr->tab[1],TABLE_KEYWORD))
		{
			if (substr->nbMot > MAX_DISP_TABLE)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_DISP_TABLE)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else {

			}
		}
		else if (! strcmp(substr->tab[1],COL_KEYWORD))
		{
			if (substr->nbMot > MAX_DISP_COL)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_DISP_COL)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{

			}
		}
		else if (! strcmp(substr->tab[1],TUPLE_KEYWORD))
		{
			if (substr->nbMot > MAX_DISP_TUPLE)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_DISP_TUPLE)
			{
				char* error = "%s%s", buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{

			}
		}
	}
	else if (! strcmp(substr->tab[0], QUIT_KEYWORD) )
	{
		if (substr->nbMot > MAX_QUIT)
		{
			char* error = "%s%s", buffer;

			buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

			sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
			fct(buffer);
			free(buffer);
		}
		else
		{

		}
	}
	else
	{
		char* error = "%s%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_KEYWORD) + strlen(substr->tab[0]) + 1) );

		sprintf(buffer, error, ERROR_HEADER, UNKNOWN_KEYWORD, substr->tab[0]);
		fct(buffer);
		free(buffer);
	}
	free(substr);
}
