typedef struct
{
	char* name;
	DataType type;
} Column;

Column *createColumn	(char *name, DataType *type);
void removeColumn		(Column *col);
