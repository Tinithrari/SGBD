#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../View/view.h"
#include "controler.h"

#include "../Utilities/StringVector.h"

#include "../Model/Data.h"
#include "../Model/Tuple.h"
#include "../Model/Column.h"
#include "../Model/Table.h"
#include "../Model/Database.h"

#include "TupleControler.h"
#include "TableControler.h"

static void disp_error_cast(Data *arg1, char *arg2, DisplayFunc fct)
{
	char error[1024];

	if (arg1->type == STR)
		sprintf(error, "%s%s to %s", CANNOT_CAST, arg1->value.str, arg2);
	else
		sprintf(error, "%s%d to %s", CANNOT_CAST, arg1->value.integer, arg2);

	fct(error);
}

static void disp_classic_error(char *header, char *arg, DisplayFunc fct)
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

static char* getCartesianProduct(Database *db, StringVector *tables, DisplayFunc fct)
{
	int *compteur = (int*) calloc(tables->length, sizeof(int)),
	lastElement = tables->length - 1;
	Table* base = getTableByName(db, *(tables->tab) ), *last = getTableByName(db, tables->tab[lastElement]);
	char* res = NULL;
	int length = 0;

	if (base == NULL || last == NULL)
	{
		free(compteur);
		disp_classic_error(UNKNOWN_TABLE, base == NULL ? tables->tab[0] : tables->tab[lastElement], fct);
		return NULL;
	}

	for (;compteur[0] < base->nbTuple;)
	{
		int j, lengthBase = 0;
		char *tupleBase = NULL;

		for (j = 0; j < lastElement; j++)
		{
			char *tuple, *tmp;
			Table *t = getTableByName(db, tables->tab[j]);

			if (t == NULL)
			{
				free(res);
				free(compteur);
				free(tupleBase);

				return NULL;
			}

			tuple = (char*)tupleToString(t->tuples[compteur[j]]);

			if (tuple == NULL)
			{
				free(compteur);
				free(res);
				free(tupleBase);

				return NULL;
			}

			tmp = (char*) realloc(tupleBase, (lengthBase + strlen(tuple) + 2 ) * sizeof(char));

			if (tmp == NULL)
			{
				free(compteur);
				free(res);
				free(tuple);
				free(tupleBase);
				return NULL;
			}

			if (tupleBase == NULL)
				*tmp = '\0';

			tupleBase = tmp;

			strcat(tupleBase, tuple);

			//strcat(res, j == lastElement ? "\n" : " ");

			lengthBase += strlen(tuple);

			*(tupleBase + lengthBase++) = ' ';
			*(tupleBase + lengthBase) = '\0';

			free(tuple);
		}

		for (; compteur[lastElement] < getTableByName(db, tables->tab[lastElement])->nbTuple; compteur[lastElement]++)
		{
			char *tmp, *tuple = tupleToString(last->tuples[compteur[lastElement]]);

			tmp = realloc(res, (length + lengthBase + strlen(tuple) + 2) * sizeof(char) );

			if (tmp == NULL)
			{
				free(compteur);
				free(res);
				free(tuple);
				free(tupleBase);
				return NULL;
			}

			if (res == NULL)
				*tmp = '\0';

			res = tmp;

			strcat(res, tupleBase);
			strcat(res, tuple);

			length += strlen(tuple) + strlen(tupleBase);

			*(res + length++) = '\n';
			*(res + length) = '\0';

			free(tuple);
		}

		for (j = lastElement; j > 0 && compteur[j] == getTableByName(db, tables->tab[j])->nbTuple; j--)
		{
			compteur[j] = 0;
			compteur[j - 1]++;

			for (j = 0; j <= lastElement; j++)
				printf("%d", compteur[j]);
			printf("\n");
		}

		free(tupleBase);
	}
	free(compteur);
	return res;
}

/**
 * @return Un vecteur contenant le nom des tables
 */
static StringVector* splitCartesianProduct(char *str)
{
	char *lastName;
	int debut, fin;
	StringVector *tables = createStringVector();

	for (debut = 0, fin = 0; fin <= strlen(str); fin++)
	{
		if (str[fin] == '*' || str[fin] == '\0')
		{
			char* tName;
			int n = fin - debut;

			tName = (char *) malloc(sizeof(char) * (n + 1));

			if (tName == NULL)
			{
				deleteStringVector(tables);
				return NULL;
			}

			tName = strncpy(tName, str + debut, n);
			tName[n] = '\0';

			printf("%s\n", tName);

			if (! addStringToVector(tables, tName))
			{
				deleteStringVector(tables);
				free(tName);
				return NULL;
			}
			str++;
			debut = fin;

			free(tName);
		}
	}
	return tables;
}

/**
 * @brief Effectue une analyse synthaxique pour vérifier l'existance d'un produit cartésien
 * @return retourne 0 si ce n'est pas un produit cartésien, 1 si s'en est un, -1 s'il s'agit d'un produit cartésien erroné
 */
static int isCP(char *str)
{
	int cartesien = 0;

	if (*str == '*')
		return -1;

	str++;

	for (;*str;str++)
	{
		if (*str == '*')
		{
			cartesien = 1;
			if (*(str - 1) == '*')
				return -1;
		}
	}

	if (*(str - 1) == '*')
		return -1;

	return cartesien;
}

static int isNumeric(char *param)
{
	if (param == NULL)
		return 0;

	for (;*param && *param >= '0' && *param <= '9'; param++);

	return *param == '\0';
}

static int isString(char *str)
{
	if (str == NULL && *str != '"')
		return 0;

	for (str++;*str && *str != '"'; str++);

	return *str == '"' && *(str + 1) == '\0';
}

static void toUpperCase(char* phrase)
{
	for(;*phrase;phrase++)
		*phrase = toupper(*phrase);
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
		return;
	}
	else if (request->length > 5)
	{
		fct(TOO_MUCH_WORDS);
		return;
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
		disp_classic_error(UNKNOWN_TYPE, request->tab[4], fct);
		return;
	}

	c = createColumn(request->tab[3], ! strcmp(request->tab[4], TYPE_INT) ? INT : STR);

	addColumn(t, c);

	fct("OK");
}

void addTupleInTable(Database *db, StringVector *request, DisplayFunc fct)
{
	Table *t;
	Tuple *tuple;
	int i;

	if (db == NULL || request == NULL || fct == NULL)
		return;

	if (request->length < 4)
	{
		fct(NOT_ENOUGH_WORDS);
		return;
	}

	if (! (t = getTableByName(db, request->tab[2])) )
	{
		disp_classic_error(UNKNOWN_TABLE, request->tab[2], fct);
		return;
	}

	if (t->nbColumn == 0)
	{
		disp_classic_error(NO_COL_IN_TABLE, t->name, fct);
		return;
	}

	tuple = createTuple(t->nbColumn);

	if (t->nbColumn > request->length - 3)
	{
		fct(NOT_ENOUGH_PARAM);
		return;
	}
	else if (t->nbColumn < request->length - 3)
	{
		fct(TOO_MUCH_PARAM);
		return;
	}

	for (i = 3; i < request->length; i++)
	{
		Data *data;
		DataValue value;
		DataType dT;

		if (isNumeric(request->tab[i]))
			dT = INT;
		else if (isString(request->tab[i]))
			dT = STR;
		else
		{
			disp_classic_error(UNKNOWN_KEYWORD, request->tab[i], fct);
			return;
		}

		if (dT == INT)
			value.integer = atoi(request->tab[i]);
		else
			value.str = request->tab[i];

		data = createData(dT, value);

		addData(tuple, data);
	}

	i = addTuple(t, tuple);

	if (i < 0)
	{
		fct("ERR: Unexpected error");
	}
	else if (i > 0)
	{
		DataType dT = tuple->datas[i - 1]->type;

		if (dT == INT)
			disp_error_cast(tuple->datas[i - 1], "STR", fct);
		else
			disp_error_cast(tuple->datas[i - 1], "INT", fct);
	}

	fct("OK");
}

void delColFromTable(Database *db, StringVector *request, DisplayFunc fct)
{
	Table *t;

	if (db == NULL || request == NULL || fct == NULL)
		return;

	if (request->length < 4)
	{
		fct(NOT_ENOUGH_WORDS);
		return;
	}
	else if (request->length > 4)
	{
		fct(TOO_MUCH_WORDS);
		return;
	}

	if (! (t = getTableByName(db, request->tab[2])) )
	{
		disp_classic_error(UNKNOWN_TABLE, request->tab[2], fct);
		return;
	}

	if (! removeColumn(t, request->tab[3]) )
		disp_classic_error(UNKNOWN_COL, request->tab[3], fct);

	fct("OK");
}

void dispColsFromTable(Database *db, StringVector *request, DisplayFunc fct)
{
	Table *t;
	int i, length = 0;
	char *tabCol = NULL;

	if (db == NULL || request == NULL || fct == NULL)
		return;

	if (request->length < 3)
	{
		fct(NOT_ENOUGH_WORDS);
		return;
	}
	else if (request->length > 3)
	{
		fct(TOO_MUCH_WORDS);
		return;
	}

	if (! (t = getTableByName(db, request->tab[2])) )
	{
		disp_classic_error(UNKNOWN_TABLE, request->tab[2], fct);
		return;
	}

	for (i = 0; i < t->nbColumn; i++)
	{
		char *tmpPtr;

		tmpPtr = (char*) realloc(tabCol, length + (sizeof(char) * (strlen(t->columns[i]->name) + strlen(t->name) + ((i + 1) == t->nbColumn ? 7 : 8))));

		if (tmpPtr == NULL)
		{
			fct("ERR: Unexpected error");
			free(tabCol);
			return;
		}

		if (tabCol == NULL)
			tmpPtr[0] = '\0';

		tabCol = tmpPtr;

		length += strlen(t->columns[i]->name) + strlen(t->name) + ((i + 1) == t->nbColumn ? 6 : 7);

		strcat(tabCol, t->name);
		strcat(tabCol, ".");
		strcat(tabCol, t->columns[i]->name);
		strcat(tabCol, "(");
		strcat(tabCol, t->columns[i]->type == INT ? "INT" : "STR");
		strcat(tabCol, ")");

		if (i + 1 != t->nbColumn)
			strcat(tabCol, " ");
	}
	if (tabCol != NULL)
	{
		fct(tabCol);
		free(tabCol);
	}

	fct("OK");
}
void dispTuplesFromTable(Database *db, StringVector *request, DisplayFunc fct)
{
	Table *t;
	int i, j, length;
	char* tuple;

	if (db == NULL || request == NULL || fct == NULL)
		return;

	if (request->length < 3)
	{
		fct(NOT_ENOUGH_WORDS);
		return;
	}
	if (! isCP(request->tab[2]))
	{

		if (! (t = getTableByName(db, request->tab[2])) )
		{
			disp_classic_error(UNKNOWN_TABLE, request->tab[2], fct);
			return;
		}

		if (request->length > 3)
		{
			Comparison** c = (Comparison**)malloc(sizeof(Comparison*));
			Tuple** tuples;
			int nbCp = 0;
			*c = NULL;
			int i;

			toUpperCase(request->tab[3]);
			if (strcmp(request->tab[3], "WHERE") || (!strcmp(request->tab[3], "WHERE") && request->length == 4))
			{
				fct("ERR: SYNTHAX_ERROR");
				free(c);
				return;
			}

			for (i = 4; i < request->length; i++)
			{
				if (i % 2 == 0)
				{
					Comparison* cp = createComparison(db, request->tab[i], fct);

					if (cp != NULL)
					{
						Comparison** tmp = (Comparison**) realloc(c, nbCp + 2);

						if (tmp == NULL)
						{
							int j;

							for (j = 0; *(c + j); j++)
								free(*(c + j));
							free(c);
							return;
						}

						c = tmp;

						*(c + nbCp++) = cp;
						*(c + nbCp) = NULL;
					}
				}
				else
				{
					toUpperCase(request->tab[i]);

					if (strcmp(request->tab[i], "AND"))
					{
						int j;

						fct("ERR: SYNTHAX_ERROR");

						for (j = 0; *(c + j); j++)
							free(*(c + j));
						free(c);
						return;
					}
				}
			}

			tuples = getTupleWhere(t, c, fct);

			if (tuples != NULL)
			{
				for (i = 0; *(tuples + i); i++)
				{
					char *tuple = (char*)tupleToString(tuples[i]);
					fct(tuple);
					fct("onche");
					free(tuple);
				}
			}

			free(tuples);

			for (;*c; c++)
			{
				free((*c)->op1);
				free((*c)->op2);
			}
			free(c);
		}
		else
		{
			for(i = 0; i < t->nbTuple; i++)
			{
				char *tuple = (char*)tupleToString(t->tuples[i]);
				fct(tuple);
				free(tuple);
			}
		}
		fct("OK");
	}
	else if (isCP(request->tab[2]) == -1)
		disp_classic_error("ERR: INVALID SYNTHAX ", request->tab[2], fct);
	else
	{
		StringVector* vec = splitCartesianProduct(request->tab[2]);

		if (vec == NULL)
			return;

		char* cart = getCartesianProduct(db, vec, fct);

		if (cart != NULL)
			fct(cart);

		free(cart);
		deleteStringVector(vec);
	}
}

