/**
 * @file TableControler.h
 * @details Controls a request from a view and apply it to the table model
 * @author Xavier HEUGUE
 * @warning include Database.h, view.h and StringVector.h before this
 */

/**
 * @fn addColInTable(Database *db, StringVector *request, DisplayFunc fct)
 * @brief Control add col in table request
 * @param db a pointer on the database
 * @param request a string vector which contains the request
 * @param fct a display function
 */
void addColInTable(Database *db, StringVector *request, DisplayFunc fct);

/**
 * @fn addTupleInTable(Database *db, StringVector *request, DisplayFunc fct)
 * @brief Control add tuple into table request
 * @param db a pointer on the database
 * @param request a string vector which contains the request
 * @param fct a display function
 */
void addTupleInTable(Database *db, StringVector *request, DisplayFunc fct);

/**
 * @fn delColFromTable(Database *db, StringVector *request, DisplayFunc fct)
 * @brief Control del col from table request
 * @param db a pointer on the database
 * @param request a string vector which contains the request
 * @param fct a display function
 */
void delColFromTable(Database *db, StringVector *request, DisplayFunc fct);

/**
 * @fn dispColsFromTable(Database *db, StringVector *request, DisplayFunc fct)
 * @brief Control disp cols from table request
 * @param db a pointer on the database
 * @param request a string vector which contains the request
 * @param fct a display function
 */
void dispColsFromTable(Database *db, StringVector *request, DisplayFunc fct);

/**
 * @fn dispTuplesFromTable(Database *db, StringVector *request, DisplayFunc fct)
 * @brief Control disp tuples from table request
 * @param db a pointer on the database
 * @param request a string vector which contains the request
 * @param fct a display function
 */
void dispTuplesFromTable(Database *db, StringVector *request, DisplayFunc fct);
