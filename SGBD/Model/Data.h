#define STR "str"
#define INT "int"

typedef union dataType
{
  int integer;
  char* str;
} DataType;

typedef struct data
{
  char* type;
  DataType value;
} Data;

Data *createStrData(char *str);
Data *createIntData(int integer);
void deleteData(Data* data);
