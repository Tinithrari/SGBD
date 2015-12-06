#include <stdlib.h>

#include "view.h"

#include "../Utilities/StringVector.h"

#include "../Model/Data.h"
#include "../Model/Tuple.h"
#include "../Model/Column.h"
#include "../Model/Table.h"
#include "../Model/Database.h"



void analyzeRequest(StringVector *request, DisplayFunc fct, Database *db)
{
	if (request == NULL || fct == NULL || db == NULL)
		return;

	if (request->length == 0)
	{

	}

}
