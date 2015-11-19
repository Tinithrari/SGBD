/**
 * @file Database.h
 * @details Header which provide structure and function for database management
 * @author Xavier Heugue
 * @warning please include Table.h before including this file
 */

/**
 * @struct Database
 * The structure for a database
 */
typedef struct
{
  Table **tables; /*!< An array of table */
  int nb_table; /*!< The number of table which are contains in the database */
}Database;

/**
 * @fn Database *createDatabase()
 * @brief Create dynamically a database
 * @return a pointer on the new database
 */
Database *createDatabase	();

/**
 * @fn int addTable(Database* db, Table* table)
 * @brief add a table into the database
 * @param db the database which will contains the new table
 * @param table the table to add in the database
 * @return 1 if the operation succeed, 0 Otherwise
 */
int addTable				(Database *db, Table* table);

/**
 * @fn Table* getTableByName(Database* db, char* name);
 * @brief search and the table which has the name : name
 * @param db The database where you want to search a table
 * @param name The name of the table researched
 * @return a pointer on the table, if the table name doesn't exist it return NULL
 */
Table* getTableByName		(Database *db, char *name);

/**
 * @fn void deleteTable(Database* db, char* name)
 * @brief delete a table from the database using the name of the table
 * @param db The database which contains the table to delete
 * @param name the name of table to delete
 * @return 1 if the operation succeed, 0 otherwise
 */
int removeTable				(Database *db, char *name);

/**
 * @fn void deleteDatabase(Database *db)
 * @brief Delete the table and all of its contents
 * @param db the database to delete
 * @warning It delete all the data contain in a database and free db
 * It do nothing if db is NULL
 */
void deleteDatabase			(Database *db);
