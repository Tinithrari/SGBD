#define STRING "STR"
#define INTEGER "INT"

/**
 * \file ModelControler.h
 * \brief Header for Model management
 * \details This header contains all the function needed to manage Model
 * \author Louis Bayart
 * \warning You need to include view.h, Controler.h, Column.h, Data.h, Database.h, Table.h and Tuple.h before including this file
 */


/**
 * \fn tableManager(Table* table, char* command)
 * \brief A function which manage a table
 * \param table The name of the table
 * \param command The name of the command
 */
void tableManager(Table* table, char* command);

/**
 * \fn databaseManager(Database* db, char* command)
 * \brief A function which manage a database
 * \param db The name of the database
 * \param command The name of the command
 */
void databaseManager(Database* db, char* command);

/**
 * \fn addTableToDatabase(Database* db, TabMot mot, DisplayFunc fct)
 * \brief A function which add a table to the database
 * \param db The name of the database
 * \param mot this is a word's tab
 * \param fct The name of DisplayFunc
 */
void addTableToDatabase(Database* db, TabMot* mot, DisplayFunc fct);

/**
 * \fn addColumnToTable(Database* db, TabMot mot, DisplayFunc fct)
 * \brief A function which add a column to the table
 * \param db The name of the database
 * \param mot this is a word's tab
 * \param fct The name of DisplayFunc
 */
void addColumnToTable(Database* db, TabMot* mot, DisplayFunc fct);

/**
 * \fn addTupleToTable(Database* db, TabMot mot, DisplayFunc fct)
 * \brief A function which add a tuple to the table
 * \param db The name of the database
 * \param mot this is a word's tab
 * \param fct The name of DisplayFunc
 */
void addTupleToTable(Database* db, TabMot* mot, DisplayFunc fct);

/**
 * \fn dispTable(Database* db, TabMot mot, DisplayFunc fct)
 * \brief A function which display the tables in the database
 * \param db The name of the database
 * \param mot this is a word's tab
 * \param fct The name of DisplayFunc
 */
void dispTable(Database* db, TabMot* mot, DisplayFunc fct);

/**
 * \fn dispColumn(Database* db, TabMot mot, DisplayFunc fct)
 * \brief A function which display the columns in the table
 * \param db The name of the database
 * \param mot this is a word's tab
 * \param fct The name of DisplayFunc
 */
void dispColumn(Database* db, TabMot* mot, DisplayFunc fct);

/**
 * \fn dispTuple(Database* db, TabMot mot, DisplayFunc fct)
 * \brief A function which display the tuples in the table
 * \param db The name of the database
 * \param mot this is a word's tab
 * \param fct The name of DisplayFunc
 */
void dispTuple(Database* db, TabMot* mot, DisplayFunc fct);

/**
 * \fn removeTableFromDatabase(Database* db, TabMot* mot, DisplayFunc fct)
 * \brief A function which remove a table from the database
 * \param db The name of the database
 * \param mot this is a word's tab
 * \param fct The name of DisplayFunc
 */
void removeTableFromDatabase(Database* db, TabMot* mot, DisplayFunc fct);

/**
 * \fn removeColumnFromTable(Database* db, TabMot mot, DisplayFunc fct)
 * \brief A function which remove a column from the table
 * \param db The name of the database
 * \param mot this is a word's tab
 *  * \param fct The name of DisplayFunc
 */
void removeColumnFromTable(Database* db, TabMot* mot, DisplayFunc fct);

