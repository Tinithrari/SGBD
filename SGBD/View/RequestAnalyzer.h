/**
 * @file TableControler.h
 * @details Function for request analyse
 * @author Xavier HEUGUE
 * @warning include Database.h, view.h and StringVector.h before this
 */

/**
 * @fn void analyzeRequest(StringVector *request, DisplayFunc fct, Database *db)
 * @brief analyze a request and call the good controller to treat the request
 * @param request a pointer on a StringVector which contains the request
 * @param fct a display function
 * @param db a database
 */
void analyzeRequest(StringVector *request, DisplayFunc fct, Database *db);
