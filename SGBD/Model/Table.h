typedef struct
{
  char *name;
  Column **columns;
  Tuple **tuples;

  int nbColumn;
  int nbTuple;
} Table;

Table *createTable				(char *name);

int addColumn					(Table *table, Column *column);
int addTuple					(Table* table, Tuple *tuple);

Column *getColumn				(Table *table, char *name);
//Tuple* getTupleByColumnName	(Table* table, char *name);

int removeColumn				(Table *table, char *name);
int deleteTable					(Table *table);
