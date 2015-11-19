/**
 * \file CommandControler.h
 * \brief Header for Command management
 * \details This header contains all the function needed to manage Command
 * \author Louis Bayart
 * \warning You need to include Data.h before including this file
 */

typedef *DysplayFunction(char*);

/**
 * \fn commandManager(Database db, char* command)
 * \brief A function which manage a command
 * \param db The name of the database
 * \param command The name of the command
 */
void commandManager(Database db, char* command);
