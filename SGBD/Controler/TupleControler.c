#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../Utilities/StringVector.h"

#include "../Model/Data.h"
#include "../Model/Tuple.h"
#include "../Model/Column.h"
#include "../Model/Table.h"
#include "../Model/Database.h"
#include "../View/view.h"
#include "controler.h"
#include "TupleControler.h"

const char LCmp[] = {'<', '>', '='};

#define NB_CMP_CHAR 3

static char* intToASCII(int nb)
{
	char *str;
	int length = log10( (double) abs(nb)) + 1 + (nb < 0 ? 2 : 1), i;

	str = (char*)malloc(sizeof(char) * length);

	if (nb < 0)
		*str = '-';

	*(str + length - 1) = '\0';

	for (i = length - 2; nb > 0; i--, nb /= 10)
		*(str + i) = (nb % 10) + '0';

	return str;
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

static int isTable(char* str)
{
	int i;

	if (*str == '.' || str[strlen(str) - 1] == '.')
		return 0;

	for (i = 0; i < strlen(str); i++)
		if (*(str + i) == '.')
			return 1;
	return 0;
}

static int isComparisonChar(char c)
{
	int i;
	for (i = 0; i < NB_CMP_CHAR; i++)
		if (c == LCmp[i])
			return 1;

	return 0;
}

static int correctSynthaxComparison(char* str)
{
	int nbSign = 0, quote = 0, i, j;

	for (i = 0; i < strlen(str); i++)
		if (str[i] == '"')
			quote = !quote;
		if (!quote && isComparisonChar(str[i]))
		{
			nbSign++;
			if (i == 0 || i == strlen(str) - 1)
				return 0;
		}

	return nbSign == 1;
}

Comparison* createComparison(Database* db, char* str, DisplayFunc fct)
{
	Comparison *c;
	int begin = 0, end;

	if (str == NULL || ! correctSynthaxComparison(str))
		return NULL;

	c = (Comparison*) malloc(sizeof(Comparison));

	for (end = 0; end < strlen(str); end++)
	{
		int op1Len = end - begin, op2Len = strlen(str) - (end + 1);
		if (isComparisonChar(str[end]))
		{
			c->op1 = (char*) malloc(sizeof(char) * (op1Len + 1) );

			if (c->op1 == NULL)
			{
				free(c);
				return NULL;
			}

			c->op2 = (char*) malloc(sizeof(char) * (op2Len + 1) );

			if (c->op1 == NULL)
			{
				free(c->op1);
				free(c);
				return NULL;
			}

			strncpy(c->op1, str, op1Len), *(c->op1 + op1Len) = '\0';
			strncpy(c->op2, str + end + 1, op2Len), *(c->op2 + op2Len) = '\0';

			return c;
		}
	}

	return NULL;
}

static StringVector* splitTableComponent(char* str)
{
	int begin = 0, end;
	StringVector* vec = createStringVector();

	for (end = 0; str[end] && vec->length == 0; end++)
	{
		if (str[end] == '.')
		{
			int tNameLen = end - begin, cNameLen = strlen(str) - (end + 1);
			char* tName = (char*) malloc((tNameLen + 1) * sizeof(char)),
			*cName = (char*) malloc((cNameLen + 1) * sizeof(char));

			strncpy(tName, str, tNameLen);
			strncpy(cName, str + end + 1, cNameLen);

			addStringToVector(vec, tName);
			addStringToVector(vec, cName);

			free(tName);
			free(cName);
		}
	}
	return vec;
}

static int respectCondition(Table *table, Tuple *t, Comparison *c, DisplayFunc fct)
{
	if (! isTable(c->op1))
		return -1;

	if (isTable(c->op1) && isTable(c->op2))
	{
		int index1, index2;
		StringVector* coord1 = splitTableComponent(c->op1);
		StringVector* coord2 = splitTableComponent(c->op2);

		if (strcmp(table->name, coord1->tab[0]) || strcmp(table->name, coord2->tab[0]))
		{
			deleteStringVector(coord1);
			deleteStringVector(coord2);
			return -2;
		}

		index1 = getColumnIndex(table, coord1->tab[1]);
		index2 = getColumnIndex(table, coord2->tab[1]);

		if (index1 == -1 || index2 == -1)
		{
			disp_classic_error(UNKNOWN_COL, index1 == -1 ? coord1->tab[1] : coord2->tab[2], fct);
			deleteStringVector(coord1);
			deleteStringVector(coord2);
			return -3;
		}

		if (getColumn(table, coord1->tab[1])->type != getColumn(table, coord2->tab[1])->type)
		{
			fct("ERR: INCOMPATIBLE_TYPES");
			deleteStringVector(coord1);
			deleteStringVector(coord2);
			return -4;
		}

		int res;
		switch (c->operation)
		{
		case '=':
			if (getColumn(table, coord1->tab[1])->type == INT)
				res = t->datas[index1]->value.integer == t->datas[index2]->value.integer;
			res = (! strcmp(t->datas[index1]->value.str, t->datas[index2]->value.str));
			break;

		case '>':
			if (getColumn(table, coord1->tab[1])->type == INT)
				res = t->datas[index1]->value.integer > t->datas[index2]->value.integer;
			res = strcmp(t->datas[index1]->value.str, t->datas[index2]->value.str) > 0;
			break;

		case '<':
			if (getColumn(table, coord1->tab[1])->type == INT)
				res = t->datas[index1]->value.integer < t->datas[index2]->value.integer;
			res = strcmp(t->datas[index1]->value.str, t->datas[index2]->value.str) < 0;
			break;
		}

		deleteStringVector(coord1);
		deleteStringVector(coord2);
		return res;
	}
	else if (isTable(c->op1))
	{
		int i, res, index;
		StringVector* coord = splitTableComponent(c->op1);

		if (strcmp(table->name, coord->tab[0]))
		{
			deleteStringVector(coord);
			return -2;
		}

		i = getColumnIndex(table, coord->tab[1]);

		if (i == -1)
		{
			disp_classic_error(UNKNOWN_COL, coord->tab[1], fct);
			deleteStringVector(coord);
			return -3;
		}

		if ( (getColumn(table, coord->tab[1])->type == INT && !isNumeric(c->op2)) ||
				(getColumn(table, coord->tab[1])->type == STR && !isString(c->op2) ) )
		{
			fct("ERR: INCOMPATIBLE_TYPES");
			deleteStringVector(coord);
			return -4;
		}

		switch (c->operation)
		{
		case '=':
			if (getColumn(table, coord->tab[1])->type == INT)
				res = t->datas[index]->value.integer == atoi(c->op2);
			res = (! strcmp(t->datas[index]->value.str, c->op2));
			break;

		case '>':
			if (getColumn(table, coord->tab[1])->type == INT)
				res = t->datas[index]->value.integer > atoi(c->op2);
			res = strcmp(t->datas[index]->value.str, c->op2) > 0;
			break;

		case '<':
			if (getColumn(table, coord->tab[1])->type == INT)
				res = t->datas[index]->value.integer < atoi(c->op2);
			res = strcmp(t->datas[index]->value.str, c->op2) < 0;
			break;
		}
	}

	fct("ERR: SYNTHAX_ERROR");
	return -6;
}

Tuple** getTupleWhere(Table* t, Comparison** c, DisplayFunc fct)
{
	Tuple** tuples = (Tuple**) malloc(sizeof(Tuple*));
	*tuples = NULL;
	int nbTuples = 0, i, j;

	if (t == NULL)
	{
		free(tuples);
		return NULL;
	}

	for (i = 0; i < t->nbTuple; i++)
	{
		Tuple** tmp;
		if (c != NULL)
			for (j = 0; *(c + j); j++)
				if (! respectCondition(t, *(t->tuples + i), *(c + j), fct) )
					goto finVerif;

		tmp = (Tuple**) realloc(tuples, sizeof(Tuple*) * (nbTuples + 2));

		if (tmp == NULL)
		{
			free(tuples);
			return NULL;
		}

		*(tmp + nbTuples++) = *(t->tuples + i);
		*(tmp + nbTuples) = NULL;

		finVerif:
		continue;
	}

	return tuples;
}
