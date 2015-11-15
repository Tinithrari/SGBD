/**
 * \file Tuple.h
 * \brief Header for tuple maanagement
 * \details A header which provide structure and function fot tuple management
 * \author Xavier Heugue
 * \warning You need to include Data.h before including this file
 */

/**
 * \struct Tuple
 * The structure of a tuple
 */
typedef struct
{
	Data** datas; /*!< A pointer on an array of pointer of Data */
	int nb_datas; /*!< The number of data contained in the tuple */
	int size; /*!< The size of datas (the array of pointer of data) */
} Tuple;

/**
 * \fn Tuple* createTuple(unsigned int size)
 * \brief Create dynamically a tuple
 * \param size The expected number of data (this is for the allocation optimization
 * \return A pointer on a tuple, or NULL if the allocation fail
 */
Tuple *createTuple 		( unsigned int size );

/**
 * \fn int addData(Tuple *tuple, Data* data)
 * \brief a function which add a data into the tuple
 * \param tuple a pointer on the tuple which will contains the data
 * \param data a pointer on the data to add into the tuple
 * \return 0 if data is NULL or if the reallocation fail, 1 if the the operation has been succeed
 */
int addData				( Tuple *tuple, Data *data );

/**
 * \fn Data* getDataByIndex(Tuple* t, unsigned int index)
 * \brief Get a data at a specified index in a tuple
 * \param t the tuple which contains the data
 * \param index the index of the data to get
 * \return A pointer on the wished data, NULL if the data is NULL or if the index is out of the data
 */
Data *getDataByIndex	( Tuple *t, unsigned int index );

/**
 * \fn int removeData (Tuple* t, unsigned int index)
 * \brief A function which delete a data created with createData (Data.h) at the specified index
 * \param t A pointer on the tuple which contains the data to delete
 * \param index The index of the data to delete
 * \return 1 if the data has been deleted, 0 if the data is NULL or if the index is out of the array
 */
int removeData 			( Tuple *t, unsigned int index );

/**
 * \fn void deleteTuple(Tuple *tuple)
 * \brief A function to delete a tuple and its content
 * \param tuple A pointer on the tuple to delete
 * \warning This function free the data contains in the data
 * \warning do nothing if the tuple is NULL
 */
void deleteTuple 		( Tuple *tuple );
