/**
 * \file Data.h
 * \brief Header for data mangement
 * \details This header contains all the function needed to manage the data
 * \author Xavier Heugue
 */

/**
 * \enum DataType
 * Define the type of a data
 * \var INT The type of the data is int
 * \var STR The type of the data is a string
 */
typedef enum {INT, STR} DataType;

/**
 * \union DataValue
 * An enum which contains the value of a data
 * \var integer the field which is filled when the data is an integer
 * \var str the field which is filled when the data is a string
 */
typedef union
{
  int integer;
  char* str;
} DataValue;

/**
 * \struct Data
 * The structure of a data
 * \var type The type of the data
 * \var value The value of the data
 */
typedef struct
{
  DataType type;
  DataValue value;
} Data;

/**
 * \fn Data* createData(DataType type, DataValue value)
 * \brief a function which allocate the data with the specified values
 * \param type The type of the data
 * \param value The value of the data
 * \return A pointer on a data, NULL if the allocation fail
 */
Data *createData	( DataType type, DataValue value );

/**
 * \fn void deleteData(Data *data)
 * \brief a function which free a data
 * \param a pointer to the data which has been created with createData
 * \warning Do nothing if data is NULL
 */
void deleteData		( Data *data );
