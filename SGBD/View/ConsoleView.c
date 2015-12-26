#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef UNIX
#include <unistd.h>
#elif defined(WINDOWS)
#include <io.h>
#endif

#include "view.h"
#include "ConsoleView.h"
#include "../Utilities/StringVector.h"

#include "../Model/Data.h"
#include "../Model/Tuple.h"
#include "../Model/Column.h"
#include "../Model/Table.h"
#include "../Model/Database.h"


#define TAILLE_BUFFER 1000

void display(char* str)
{
	if (strpbrk(str, ERROR_HEADER) == str)
		fprintf(stderr, "%s\n", str);
	else
		fprintf(stdout, "%s\n", str);
}

static int addWordToStruct(char *begin, char *end, StringVector* vec)
{
	char *mot;
	int length = end - begin;
	mot = (char*) malloc(sizeof(char) * (length + 1));

	if (mot == NULL)
		return 0;

	memcpy(mot, begin, length);
	mot[length] = '\0';

	if (! addStringToVector(vec, mot) )
	{
		free(mot);
		return 0;
	}

	free(mot);
	return 1;
}

static StringVector *diviserCommande(char *command)
{
	StringVector *vec;
	char *pointer, *first;
	int entreQuote, firstSpace, length;

	// On vérifie si la commande est nulle
	if (command == NULL)
		return NULL;

	// On créer un vecteur de string pour stocker les divers éléments de la requête
	vec = createStringVector();
	entreQuote = 0, firstSpace = 0;

	for (first = (pointer = command); *pointer; pointer++)
	{
		if (!firstSpace && *pointer != ' ')
		{
			first = pointer;
			firstSpace = 1;
		}
		if (*pointer == '"')
		{
			entreQuote = ! entreQuote;
		}
		else if (*pointer == ' ' && ! entreQuote && firstSpace)
		{

			if (! addWordToStruct(first, pointer, vec))
			{
				deleteStringVector(vec);
				return NULL;
			}

			first = pointer + 1;

			firstSpace = 0;
		}
	}

	if (command[0] != '\0' && *(pointer - 1) != ' ')
	{
		if (! addWordToStruct(first, pointer, vec))
		{
			deleteStringVector(vec);
			return NULL;
		}
	}

	return vec;
}

void run(char** files, const int nbFile)
{
	int compteur = 0;
	FILE* stdin_copy = NULL;

	if (nbFile > 0)
	{
		#ifdef UNIX
			dup2(stdin, stdin_copy);
		#elif defined(WINDOWS)
			_dup2(stdin, stdin_copy);
		#endif

		freopen(*files, "r", stdin);
	}

	char command[TAILLE_BUFFER];
	command[0]='\0';

	StringVector* vec;
	Database *db;

	db = createDatabase();

	for(;strcmp(command, "QUIT");)
	{
		int c;
		command[0] = '\0';

		printf("=> ");
		fflush(stdout);

		c = scanf("%999[^\n]%*c", command);

		if (!c)
			while ( (c = getchar()) != '\n' && c != EOF);

		if (c == EOF && files != NULL && (compteur + 1) < nbFile)
		{
			freopen( *(files + compteur), "r", stdin);
			compteur++;
		}
		else if (c == EOF && files != NULL && (compteur + 1) == nbFile)
		{
			fclose(stdin);
			#ifdef UNIX
				dup2(stdin_copy, stdin);
			#elif defined(WINDOWS)
				_dup2(stdin_copy, stdin);
			#endif
			free(files);
			files = NULL;
		}

		vec = diviserCommande(command);

		if (vec != NULL)
			analyzeRequest(vec, display, db);

		deleteStringVector(vec);
	}
	deleteDatabase(db);
}
