#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../View/view.h"
#include "../Model/Data.h"
#include "../Model/Column.h"
#include "../Model/Tuple.h"
#include "../Model/Table.h"
#include "../Model/Database.h"
#include "Controler.h"
#include "CommandControler.h"
#include "ModelControler.h"

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

	for (;*str;str++)
		if (*str >= 'a' && *str <= 'z')
			*str = *str - 'a' + 'A';
}

static TabMot* cutStr(char* str)
{
	int i,nbMot,nbLettre,entreQuote,firstSpace;
	TabMot* tabDeMot;
	char **tab = NULL, **newPointer;

	if (str == NULL)
		return NULL;

	for (i = 0, nbMot = 0, nbLettre = 0, entreQuote = 0, firstSpace = 0; *(str + i); i++)
	{
		if (*(str + i) == '"' && !entreQuote)
		{
			entreQuote = 1;
			nbLettre++;
		}
		else if (*(str + i) == '"' && entreQuote)
		{
			entreQuote = 0;
			nbLettre++;
		}
		else if (!entreQuote && firstSpace && *(str + i) == ' ')
		{
			newPointer = (char**)realloc(tab, sizeof(char*) * (nbMot + 1));

			if (newPointer == NULL)
			{
				int j;

				for (j = 0; j < nbMot + 1; j++)
					free(*(tab + j));
				free(tab);
				return NULL;
			}

			tab = newPointer;

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
			firstSpace = 1;
			nbLettre++;
		}
	}

	newPointer = (char**)realloc(tab, sizeof(char*) * (nbMot + 1));

	if (newPointer == NULL)
	{
		int j;

		for (j = 0; j < nbMot + 1; j++)
		free(*(tab + j));
		free(tab);
		return NULL;
	}

	tab = newPointer;

	*(tab + nbMot) = (char*) malloc(sizeof(char) * (nbLettre + 1) );

	for (i = 0, nbMot = 0, nbLettre = 0, entreQuote = 0, firstSpace = 0; *(str + i); i++)
	{
		if (*(str + i) == '"')
		{
			entreQuote = !entreQuote;
			*((*(tab + nbMot)) + nbLettre) = *(str + i);
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
			firstSpace = 1;
			tab[nbMot][nbLettre] = *(str + i);
			nbLettre++;
		}
	}

	tabDeMot = (TabMot*) malloc(sizeof(TabMot));

	tabDeMot->tab = tab;
	if (tab[nbMot][nbLettre - 1] != ' ')
		nbMot++;
	tabDeMot->nbMot = nbMot;

	return tabDeMot;
}

static void deleteTabMot(TabMot *tab)
{
	int i;

	if (tab == NULL)
		return;

	for (i = 0; i < tab->nbMot; i++)
		free(*(tab->tab + i));
	free(tab->tab);
	free(tab);
}

void commandManager(Database *db, char *command, DisplayFunc fct)
{
	TabMot *substr;

	if (db == NULL || command == NULL)
		return;

	// On r�cup�re les trois premiers caract�res
	substr = cutStr(command);

	if (substr->nbMot == 0)
	{
		char* error = "%s%s", *buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_WORDS) + 1) );

		sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_WORDS);
		fct(buffer);

		free(buffer);
		return;
	}

	toUpperCase(substr->tab[0]);

	if (! strcmp(substr->tab[0], ADD_KEYWORD))
	{
		toUpperCase(substr->tab[1]);
		if (! strcmp(substr->tab[1],TABLE_KEYWORD))
		{
			if (substr->nbMot > MAX_ADD_TABLE)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_ADD_TABLE)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{
				addTableToDatabase(db, substr, fct);
			}
		}
		else if (! strcmp(substr->tab[1],COL_KEYWORD))
		{
			if (substr->nbMot > MAX_ADD_COL)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_ADD_COL)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{
				addColumnToTable(db, substr, fct);
			}
		}
		else if (! strcmp(substr->tab[1],TUPLE_KEYWORD))
		{
			if (substr->nbMot < MAX_ADD_TUPLE)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{
				addTupleToTable(db, substr, fct);
			}
		}
	}
	else if (! strcmp(substr->tab[0], DELETE_KEYWORD) )
	{
		toUpperCase(substr->tab[1]);
		if (! strcmp(substr->tab[1],TABLE_KEYWORD))
		{
			if (substr->nbMot > MAX_DEL_TABLE)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_DEL_TABLE)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{
				removeTableFromDatabase(db, substr, fct);
			}
		}
		else if (! strcmp(substr->tab[1],COL_KEYWORD))
		{
			if (substr->nbMot > MAX_DEL_COL)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_DEL_COL)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{
				removeColumnFromTable(db, substr, fct);
			}
		}
	}
	// Si le d�but ne correspond pas � un ajout ou une suppression, on v�rifie s'il s'agit d'une requ�te d'affichage, ou de quitter le programme
	else if (! strcmp(substr->tab[0], DISPLAY_KEYWORD) )
	{
		toUpperCase(substr->tab[1]);
		if (! strcmp(substr->tab[1],SET_TABLES_KEYWORD))
		{
			if (substr->nbMot > MAX_DISP_TABLE)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_DISP_TABLE)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{
				dispTable(db, substr, fct);
			}
		}
		else if (! strcmp(substr->tab[1],SET_COLS_KEWORD))
		{
			if (substr->nbMot > MAX_DISP_COL)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_DISP_COL)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{
				dispColumn(db, substr, fct);
			}
		}
		else if (! strcmp(substr->tab[1],SET_TUPLES_KEYWORD))
		{
			if (substr->nbMot > MAX_DISP_TUPLE)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else if (substr->nbMot < MAX_DISP_TUPLE)
			{
				char* error = "%s%s", *buffer;

				buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

				sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
				fct(buffer);
				free(buffer);
			}
			else
			{
				dispTuple(db, substr, fct);
			}
		}
		else
		{
			char* error = "%s%s%s", *buffer;

			buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_KEYWORD) + strlen(substr->tab[1]) + 1) );

			sprintf(buffer, error, ERROR_HEADER, UNKNOWN_KEYWORD, substr->tab[1]);
			fct(buffer);
			free(buffer);
		}
	}
	else if (! strcmp(substr->tab[0], QUIT_KEYWORD) )
	{
		if (substr->nbMot > MAX_QUIT)
		{
			char* error = "%s%s", *buffer;

			buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

			sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
			fct(buffer);
			free(buffer);
		}
		else
		{
			deleteDatabase(db);
			deleteTabMot(substr);
			exit(0);
		}
	}
	else
	{
		char* error = "%s%s%s", *buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_KEYWORD) + strlen(substr->tab[0]) + 1) );

		sprintf(buffer, error, ERROR_HEADER, UNKNOWN_KEYWORD, substr->tab[0]);
		fct(buffer);
		free(buffer);
	}
	deleteTabMot(substr);
}
