#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../Model/Data.h"
#include "../Model/Tuple.h"

#define INT_DATA 1
#define STR_DATA "Un produit en provenace d'un supermarché"
#define MORE_DATA "Another data"

int main()
{
	Tuple *monTuple;

	monTuple = createTuple(2);

	if (monTuple != NULL)
	{
		assert(addIntData(monTuple, INT_DATA));
		assert(addStrData(monTuple, STR_DATA));

		assert(monTuple->nb_datas == 2);
		assert(monTuple->size == 2);

		assert(addStrData(monTuple, MORE_DATA));

		assert((*(monTuple->datas))->value.integer == INT_DATA);
		assert(! strcmp( (*(monTuple->datas + 1))->value.str, STR_DATA));
		assert(! strcmp( (*(monTuple->datas + 2))->value.str, MORE_DATA));

		assert(removeIntData(monTuple, INT_DATA));
		assert(monTuple->size == 2);
		assert(monTuple->nb_datas == 2);

		deleteTuple(monTuple);
	}

}
