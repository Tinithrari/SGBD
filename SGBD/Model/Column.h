typedef struct
{
	char* name;
	char* type;
} Column;

Column *createColumn	(char *name, char *type);
void removeColumn		(Column *col);
