typedef enum {INT, STR} DataType;

typedef union
{
  int integer;
  char* str;
} DataValue;

typedef struct
{
  DataType type;
  DataValue value;
} Data;

Data *createData	( DataType type, DataValue value );
void deleteData		( Data *data );
