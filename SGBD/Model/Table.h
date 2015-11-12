typedef struct
{
  char *nom;
  Column **columns;
  Tuple **tuples;

  int nb_column;
  int nb_tuple;
} Table;

int addColumn		(Column *column);
int addTuple		(Tuple *tuple);

void deleteTable	(Table *table);
void deleteColumn	(char *name);
