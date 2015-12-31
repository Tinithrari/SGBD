/**
 * @file TupleControler.h
 * @details Provide method and data structure to do data selection
 * @author Xavier HEUGUE
 * @warning You need to include Database.h, view.h, StringVector.h before including this file
 */

#define TAB_COL_SEP '.'

/**
 * @struct Comparison
 * A data structure which represent a comparison
 */
typedef struct
{
	char *op1; /*!< The first operand of the comparison */
	char operation; /*!< A character which represents the type of comparison ( Available characters : <,>,= ) */
	char *op2; /*!< The second operand of the comparison */
} Comparison;

/**
 * @fn Comparison* createComparison(char* str)
 * @brief Transform a string with a comparison into a comparison structure
 * @param db The database which will contains the table for the operation
 * @param str The string which contains the comparison
 * @param fct A function which permits to display something on the screen
 * @return A comparison structure, if there are a synthax error or type error, return NULL
 */
Comparison* createComparison(Database *db, char* str, DisplayFunc fct);

/**
 * @fn Tuple** getTupleWhere(Table *t, Comparison** c)
 * @brief Extract Tuple from a single table where the comparisons are verified
 * @param t the table where you will make some operation
 * @param c conditions to respect to obtain a tuple, this array must be NULL terminated, if no condition, just put NULL
 * @return The tuple which respect the conditions (NULL terminated)
 */
Tuple** getTupleWhere(Table *t, Comparison** c, DisplayFunc fct);

/**
 * @fn void deleteComparison(Comparison *c)
 * @brief Delete a comparison structure
 * @param c The comparison to delete
 */
void deleteComparison(Comparison* c);
