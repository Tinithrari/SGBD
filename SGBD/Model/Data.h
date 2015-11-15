/**
 * \file Data.h
 * \brief Header for data mangement
 * \details This header contains all the function needed to manage the data
 * \author Xavier Heugue
 */

/**
 * \enum DataType
 * Define the type of a data
 */
typedef enum
{
	INT, /*!< The type of the data is int*/
	STR /*!< The type of the data is a string */
} DataType;

/**
 * \union DataValue
 * An enum which contains the value of a data
 */
typedef union
{
  int integer; /*!< The field which is filled when the data is an integer */
  char* str; /*!< the field which is filled when the data is a string */
} DataValue;

/**
 * \struct Data
 * The structure of a data
 */
typedef struct
{
  DataType type; /*!< The type of the data */
  DataValue value; /*!< The value of the data */
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
 * \brief A function which free a data
 * \param data A pointer to the data which has been created with createData
 * \warning Do nothing if data is NULL
 */
void deleteData		( Data *data );
