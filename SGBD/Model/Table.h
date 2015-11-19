/**
 * \file Table.h
 * \brief A header for table management
 * \details A header which provide structure and function for table management
 * \author Xavier Heugue
 * \warning You need to include Column.h, Data.h and Tuple.h before including this file
 */

/**
 * \struct Table
 * The structure of a table
 */
typedef struct
{
	char *name; /*!< The name of the table */
	Column **columns; /*!< A pointer on an array of pointer on Column */
	Tuple **tuples; /*!< A pointer on an array of pointer on Tuple */
	unsigned int nbColumn; /*!< The number of column into the table */
	unsigned int nbTuple; /*!< The number of tuples into the table */
} Table;

/**
 * \fn Table* createTable (char* name)
 * \brief A function which create dynamically a table
 * \param name The name of the table
 * \return A pointer on the new table
 */
Table *createTable				(char *name);

/**
 * \fn int addColumn(Table* table, Column* column)
 * \brief A function which add a column into a table
 * \param table A pointer on the table which will contains the column
 * \param column A pointer on the column to add into the table
 * \return 1 if the operation succeed, 0 if the table or the tuple is NULL or if the operation fails
 */
int addColumn					(Table *table, Column *column);

/**
 * \fn int addTuple(Table* table, Tuple* tuple)
 * \brief A function which add a tuple into a table
 * \param table A pointer on the table which will contains the tuple
 * \param tuple A pointer on the tuple to add into the table
 * \return 0 if the operation succeed, another number for the column number if there are a problem
 */
int addTuple					(Table *table, Tuple *tuple);

/**
 * \fn Column* getColumn(Table* table, char* name)
 * \brief A function which give a column named name
 * \param table A pointer on the table where searched the column
 * \param name A pointer on the name of the column to search
 * \return A pointer on the column called named name, otherwise retuns NULL
 */
Column *getColumn				(Table *table, char *name);

/**
 * \fn int removeColumn(Table* table, char* name)
 * \brief A function which remove a column and datas which are associated to the column
 * \param table A pointer on the table which contains the column to delete
 * \param name The name of the column to delete
 * \return return 1 if the operation succeed, 0 if the table or the name is NULL, or if the column doesn't exist
 */
int removeColumn				(Table *table, char *name);

/**
 * \fn deleteTable(Table* table)
 * \brief A function which delete a table
 * \param table A pointer on the table to delete
 * \warning All contents in the table will be free
 */
void deleteTable					(Table *table);
