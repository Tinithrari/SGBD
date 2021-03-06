#include <stdlib.h>
#include <string.h>

#include "StringVector.h"

StringVector *createStringVector()
{
	StringVector *vec;

	vec = (StringVector*) malloc(sizeof(StringVector));

	if (vec == NULL)
		return NULL;

	vec->tab = NULL;
	vec->length = 0;

	return vec;
}

int addStringToVector(StringVector *vec, char *word)
{
	char** tmpTab, *tmpStr;
	int length;


	if (vec == NULL || word == NULL)
		return 0;

	tmpTab = (char**) realloc(vec->tab, sizeof(char*) * (vec->length + 1));

	if (tmpTab == NULL)
		return 0;

	vec->tab = tmpTab;

	length = strlen(word);

	tmpStr = (char*) malloc(sizeof(char) * (length + 1));

	if (tmpStr == NULL)
		return 0;

	*(vec->tab + vec->length) = tmpStr;

	strcpy( *(vec->tab + vec->length), word );

	vec->length++;

	return 1;
}

int removeStringToVector(StringVector *vec, char *mot)
{
	int i, j;
	char** tmp;
	if (vec == NULL || vec->tab == NULL || mot == NULL)
		return 0;

	for (i = 0; i < vec->length; i++)
	{
		if (! strcmp( *(vec->tab + i), mot ) )
		{
			free(*( vec->tab + i ) );

			for (j = i; j < vec->length - 1; j++)
				*(vec->tab + j) = *(vec->tab + j + 1);
			tmp = realloc(vec->tab, sizeof(char*) * (vec->length - 1) );
			vec->tab = tmp;
			vec->length--;

			return 1;
		}
	}
	return 0;
}

void deleteStringVector(StringVector *vec)
{
	int i;
	if (vec == NULL)
		return;

	for (i = 0; i < vec->length; i++)
		free(*((vec->tab) + i));

	free(vec->tab);
	free(vec);
}
