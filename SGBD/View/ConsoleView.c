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

#include "RequestAnalyzer.h"

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
	int stdin_copy = NULL;
	int close_file = 0;
	int isFile = 0;

	FILE *f;

	if (nbFile > 0)
	{
		#ifdef UNIX
			stdin_copy = dup(STDIN_FILENO);
		#elif defined(WINDOWS)
			_stdin = _dup(STDIN_FILENO);
		#endif
		f = fopen(*files, "r");
		#ifdef UNIX
		dup2(fileno(f), STDIN_FILENO);
		#endif
		isFile = 1;
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

		if (! isFile)
			printf("=> ");
		fflush(stdout);

		c = scanf("%999[^\n]%*c", command);

		if (feof(stdin) && files != NULL && (compteur + 1) < nbFile)
		{
			fclose(f);
			f = fopen(*(files + compteur), "r");
			dup2( fileno(f), 0);
			compteur++;
			close_file = 1;
		}
		else if (feof(stdin) && files != NULL && (compteur + 1) == nbFile)
		{
			fclose(f);
			#ifdef UNIX
			close(0);
			dup2(stdin_copy, STDIN_FILENO);
			close(stdin_copy);
			#elif defined(WINDOWS)
			_close(STDIN_FILENO);
			_dup2(stdin_copy, STDIN_FILENO);
			_close(stdin_copy);
			#endif
			free(files);
			files = NULL;
			close_file = 1;
			isFile = 0;
		}

		if (!c)
		{
			while ( (c = getchar()) != '\n' && c != EOF);
		}

		if (! close_file)
			vec = diviserCommande(command);
		else
			close_file = 0;

		if (vec != NULL)
			analyzeRequest(vec, display, db);

		deleteStringVector(vec);
		vec = NULL;
	}
	deleteDatabase(db);
}
