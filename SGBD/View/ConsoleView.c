#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "view.h"
#include "ConsoleView.h"
#include "CommandControler.h"

void display(char* str)
{
	if (strpbrk(str, ERROR_HEADER))
		fprintf(stderr, str);
	else
		fprintf(stdout, str);
}

void run()
{
	char* command;
	Database *db;

	db = (Database*) malloc(sizeof(Database));

	for(;scanf("%s", command);)
		commandManager(db, command, display);

}
