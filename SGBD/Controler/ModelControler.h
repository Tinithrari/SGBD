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
