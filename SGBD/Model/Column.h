/**
 * \file Column.h
 * \brief Header for Column management
 * \details This header contains all the function needed to manage column
 * \author Xavier Heugue
 * \warning You need to include Data.h before including this file
 */

/**
 * \struct Column
 * The column structure
 */
typedef struct
{
	char* name; /*!< The name of the column */
	DataType type; /*!< The type of the column */
} Column;

/**
 * \fn Column* createColumn(char *name, DataType type)
 * \brief A function which create a column
 * \param name The name of the column
 * \param type The type of the column
 * \return Return a pointer on a column created dynamically, return NULL if the name is NULL or if the allocation fail
 */
Column *createColumn	(char *name, DataType type);

/**
 * \fn void removeColumn(Column *col)
 * \brief A function which remove a column created with createColumn
 * \param col A pointer on a column
 * \warning Do nothing if col is NULL
 */
void removeColumn		(Column *col);
