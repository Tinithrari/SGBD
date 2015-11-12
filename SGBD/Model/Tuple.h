typedef struct
{
  
  Data** datas;
  int nb_datas;
  int size;
  
} Tuple;

Tuple *createTuple 	( unsigned int size );

int addData			( Data *data );
Data *getDataByIndex( Tuple *t, int index );
int removeData 		( Tuple *t, unsigned int index );

void deleteTuple 	( Tuple *tuple );
