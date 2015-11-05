typedef struct column
{
	char* name;
	char* type;
} Column;

Column *createColumn(char *name, char *type);
void deleteColumn(Column *col);