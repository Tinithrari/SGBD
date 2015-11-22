/**
 * \file CommandControler.h
 * \brief Header for Command management
 * \details This header contains all the function needed to manage Command
 * \author Louis Bayart
 * \warning You need to include view.h, Controler.h, Column.h, Data.h, Database.h, Table.h and Tuple.h before including this file
 */

/**
 * \fn commandManager(Database* db, char* command)
 * \brief A function which manage a command
 * \param db The name of the database
 * \param command The name of the command
 * \param fct A pointer on the display function
 */
void commandManager(Database* db, char* command, DisplayFunc fct);
