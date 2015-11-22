#include <stdlib.h>
#include <string.h>

#include "../View/view.h"
#include "Data.h"
#include "Column.h"
#include "Tuple.h"
#include "Table.h"
#include "Database.h"
#include "Controler.h"
#include "ModelControler.h"

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

static int isNumeric(char* str)
{
	int first;
	if (str == NULL)
		return 0;
	for(first = 1;*str;str++, first = 0)
	{
		if ((! first) && (*str == '-'))
			return 0;
		else if (*str < '0' && *str > '9')
			return 0;
	}
	return 1;
}

static int isString(char* str)
{
	int longueur, i;
	if (str == NULL)
		return 0;

	if(*str != '"')
		return 0;
	longueur = strlen(str);
	for(i=1;*str;str++,i++)
	{
		if ((*str == '"' && i != longueur) || (*str != '"' && i == longueur))
			return 0;
	}
	return 1;
}

void addTableToDatabase(Database* db, TabMot mot, DisplayFunc fct)
{
	Table* table;

	if (db == NULL)
		return;
	if (getTableByName(db, mot->tab[2]) != NULL)
	{
		char* error = "%s%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(EXISTING_TABLE) + strlen(mot->tab[2]) + 1) );

		sprintf(buffer, error, ERROR_HEADER, EXISTING_TABLE, mot->tab[2]);
		fct(buffer);

		free(buffer);
		return;
	}

	table = createTable(mot->tab[2]);
	addTable(db, table);
}

void addColumnToTable(Database* db, TabMot mot, DisplayFunc fct)
{
	DataType type;
	Column* column;
	Table* table;

	if (db == NULL)
		return;
	if ((table = getTableByName(db, mot->tab[2])) == NULL)
	{
		char* error = "%s%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_TABLE) + strlen(mot->tab[2]) + 1) );

		sprintf(buffer, error, ERROR_HEADER, UNKNOWN_TABLE, mot->tab[2]);
		fct(buffer);

		free(buffer);
		return;
	}
	if ((column = getColumn(table, mot->tab[3])) != NULL)
	{
		char* error = "%s%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(EXISTING_COL) + strlen(mot->tab[3]) + 1) );

		sprintf(buffer, error, ERROR_HEADER, EXISTING_COL, mot->tab[3]);
		fct(buffer);

		free(buffer);
		return;
	}
	toUpperCase(mot->tab[4]);
	if (( (strcmp(mot->tab[4],INTEGER) ) || (strcmp (mot->tab[4], STRING) )))
	{
		char* error = "%s%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_TYPE) + strlen(mot->tab[4]) + 1) );

		sprintf(buffer, error, ERROR_HEADER, UNKNOWN_TYPE, mot->tab[4]);
		fct(buffer);

		free(buffer);
		return;
	}
	if (!strcmp(mot->tab[4],INTEGER))
		type = INT;
	else
		type = STR;

	column = createColumn(mot->tab[3], type);
	addColumn(table,column);
}

void addTupleToTable(Database* db, TabMot mot, DisplayFunc fct)
{
	Data* data;
	DataType type;
	DataValue value;
	Tuple* tuple;
	Table* table;
	int i, errorCode;

	if (db == NULL)
		return;
	if ((table = getTableByName(db, mot->tab[2])) == NULL)
	{
		char* error = "%s%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_TABLE) + strlen(mot->tab[2]) + 1) );

		sprintf(buffer, error, ERROR_HEADER, UNKNOWN_TABLE, mot->tab[2]);
		fct(buffer);

		free(buffer);
		return;
	}

	if(table->nbColumn == 0)
	{
		char* error = "%s%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NO_COL_IN_TABLE) + 1) );

		sprintf(buffer, error, ERROR_HEADER, NO_COL_IN_TABLE);
		fct(buffer);

		free(buffer);
		return;
	}

	if (table->nbColumn > mot->nbMot-3)
	{
		char* error = "%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(NOT_ENOUGH_PARAM) + 1) );

		sprintf(buffer, error, ERROR_HEADER, NOT_ENOUGH_PARAM);
		fct(buffer);

		free(buffer);
		return;
	}
	else if (table->nbColumn < mot->nbMot-3)
	{
		char* error = "%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(TOO_MUCH_PARAM) + 1) );

		sprintf(buffer, error, ERROR_HEADER, TOO_MUCH_PARAM);
		fct(buffer);

		free(buffer);
		return;
	}

	tuple = createTuple(table->nbColumn);

	for (i=3; i < mot->nbMot ; i++)
	{
		if (isNumeric(mot->tab[i]))
		{
			value.integer = atoi(mot->tab[i]);
			type = INT;
		}
		else if (isString(mot->tab[i]))
		{
			value.str = mot->tab[i];
			type = STR;
		}
		else
		{
			char* error = "%s%s", buffer;

			buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_KEYWORD) + 1) );

			sprintf(buffer, error, ERROR_HEADER, UNKNOWN_KEYWORD);
			fct(buffer);

			free(buffer);
			deleteTuple(tuple);
			return;
		}
		data = createData(type, value);
		addData(tuple, data);
	}

	errorCode = addTuple(table, tuple);

	if (errorCode)
	{
		Column* col = *((table->columns)+(errorCode-1));

		char* error = "%s%s%s%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(CANNOT_CAST) + strlen(mot->tab[3 + (errorCode-1)]) + strlen(" to ") + strlen(col->type == INT ? INTEGER:STRING) + 1) );

		sprintf(buffer, error, ERROR_HEADER, CANNOT_CAST, mot->tab[3 + (errorCode-1)], " to ", col->type == INT ? INTEGER:STRING);
		fct(buffer);

		free(buffer);
		deleteTuple(tuple);
		return;
	}
}

void dispTable(Database* db, TabMot mot, DisplayFunc fct)
{
	int i;
	if (db == NULL)
		return;
	for(i=0; i < db->nb_table; i++)
		printf("%s\n", (*((db->tables)+i))->name);
}

void dispColumn(Database* db, TabMot mot, DisplayFunc fct)
{
	int i;
	Table* table;
	if (db == NULL)
		return;
	if ((table = getTableByName(db, mot->tab[2])) == NULL)
	{
		char* error = "%s%s%s", buffer;

		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_TABLE) + strlen(mot->tab[2]) + 1) );

		sprintf(buffer, error, ERROR_HEADER, UNKNOWN_TABLE, mot->tab[2]);
		fct(buffer);

		free(buffer);
		return;
	}

	for (i = 0; i < table->nbColumn; i++)
		printf("%s(%s) ", (*((table->columns)+i))->name, (*((table->columns)+i))->type == INT ? INTEGER:STRING);

}

void dispTuple(Database* db, TabMot mot, DisplayFunc fct)
{
	int i, j;
	Table* table;
	if (db == NULL)
		return;
	if ((table = getTableByName(db, mot->tab[2])) == NULL)
	{
		char* error = "%s%s%s", buffer;
		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_TABLE) + strlen(mot->tab[2]) + 1) );
		sprintf(buffer, error, ERROR_HEADER, UNKNOWN_TABLE, mot->tab[2]);
		fct(buffer);
		free(buffer);
		return;
	}

	for (i = 0; i < table->nbTuple; i++)
		for (j = 0; j < table->nbColumn; j++)
			printf("%s ", (*(( (*(table->tuples)) + i)->datas + j))->value);
}

void removeTableFromDatabase(Database* db, TabMot mot, DisplayFunc fct)
{
	if (! removeTable(db, mot->tab[2]))
	{
		char* error = "%s%s%s", buffer;
		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_TABLE) + strlen(mot->tab[2]) + 1) );
		sprintf(buffer, error, ERROR_HEADER, UNKNOWN_TABLE, mot->tab[2]);
		fct(buffer);
		free(buffer);
		return;
	}
}

void removeColumnFromTable(Database* db, TabMot mot, DisplayFunc fct)
{
	Table* table;
	if (db == NULL)
		return;
	if ((table = getTableByName(db, mot->tab[2])) == NULL)
	{
		char* error = "%s%s%s", buffer;
		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_TABLE) + strlen(mot->tab[2]) + 1) );
		sprintf(buffer, error, ERROR_HEADER, UNKNOWN_TABLE, mot->tab[2]);
		fct(buffer);
		free(buffer);
		return;
	}

	if (! removeColumn(table, mot->tab[3]))
	{
		char* error = "%s%s%s", buffer;
		buffer = (char*)malloc(sizeof(char) * (strlen(ERROR_HEADER) + strlen(UNKNOWN_COL) + strlen(mot->tab[3]) + 1) );
		sprintf(buffer, error, ERROR_HEADER, UNKNOWN_COL, mot->tab[3]);
		fct(buffer);
		free(buffer);
		return;
	}
}
