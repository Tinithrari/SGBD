#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../Model/Data.h"
#include "../Model/Tuple.h"
#include "../Model/Column.h"
#include "../Model/Table.h"
#include "../Model/Database.h"
#include "view.h"
#include "ConsoleView.h"
#include "../Controler/Controler.h"
#include "../Controler/CommandControler.h"
#include "../Controler/ModelControler.h"

void display(char* str)
{
	if (strpbrk(str, ERROR_HEADER))
		fprintf(stderr, "%s\n", str);
	else
		fprintf(stdout, "%s\n", str);
}

void run()
{
	Database *db;

	db = (Database*) malloc(sizeof(Database));

	for(;;)
	{
		char command[250] = {0};
		int c, retour;


		retour = scanf("%250[^\n]", command);

		if (!retour)
			do
			{
				c = getchar();
			} while (c != '\n' && c != EOF);
		else
			commandManager(db, command, display);
	}

}
