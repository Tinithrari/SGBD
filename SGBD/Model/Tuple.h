typedef struct tuple
{
  
  Data** datas;
  int nb_datas;
  int size;
  
} Tuple;

Tuple *createTuple ( unsigned int size );

int addStrData ( Tuple *t , char* value );
int addIntData ( Tuple *t , int value );

int removeData ( Tuple *t, unsigned int index );

void deleteTuple ( Tuple *tuple );
