/**
 * @file DatabaseControler.h
 * @details Controls a request from a view and apply it to the database model
 * @author Xavier HEUGUE
 * @warning include Database.h, view.h and StringVector.h before this
 */

/**
 * @fn addTableInDatabase(Database *db, StringVector *request, DisplayFunc fct)
 * @brief Control add table request
 * @param db a pointer on the database
 * @param request a string vector which contains the request
 * @param fct a display function
 */
void addTableInDatabase(Database *db, StringVector *request, DisplayFunc fct);

/**
 * @fn deleteTableFromDatabase(Database *db, StringVector *request, DisplayFunc fct)
 * @brief Control del table request
 * @param db a pointer on the database
 * @param request a string vector which contains the request
 * @param fct a display function
 */
void deleteTableFromDatabase(Database *db, StringVector *request, DisplayFunc fct);

/**
 * @fn displayTablesFromDatabase(Database *db, StringVector *request, DisplayFunc fct)
 * @brief Control disp table request
 * @param db a pointer on the database
 * @param request a string vector which contains the request
 * @param fct a display function
 */
void displayTablesFromDatabase(Database *db, StringVector *request, DisplayFunc fct);
