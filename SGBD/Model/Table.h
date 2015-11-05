typedef struct table
{
  char *nom;
  Column **columns;
  Tuple **tuples;

  int nb_column;
  int nb_tuple;
} Table;

bool addColumn(char *name, char* type);
bool addTuple();

void deleteTable(Table *table);
void deleteColumn(char *name);
