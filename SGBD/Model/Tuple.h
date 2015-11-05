typedef struct tuple
{
  
  Data** datas;
  int nb_datas;
  int size;
  
} Tuple;

Tuple *createTuple ( unsigned int size );

int addStrData ( Tuple *t , char* value );
int addIntData ( Tuple *t , int value );

int removeStrData ( Tuple *t , char* value );
int removeIntData ( Tuple *t , int value );

void deleteTuple ( Tuple *tuple );
