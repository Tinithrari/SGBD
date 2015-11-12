typedef struct
{
  Table **table;
  int nb_table;
}Database;

Database *createDatabase();

int addTable			(Table* table);
void deleteTable		(Table* table);

void deleteDatabase		(Database *db);
