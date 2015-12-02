/**
 * @file StringVector.h
 * @details Provide method and structure to use string vector
 * @author Xavier Heugue
 */

/**
 * @struct StringVector
 * @brief structure of string vector
 */
typedef struct
{
	char **tab; /*!< The table which contains string */
	int length; /*!< The length of the vector and the number of string stored*/
} StringVector;

/**
 * @fn StringVector *createStringVector()
 * @brief create a StringVector
 * @return a pointer on the StringVector, NULL if the allocation fail
 */
StringVector *createStringVector();

/**
 * @fn int addStringToVector(StringVector *vec, char *str)
 * @brief add a string into a string vector
 * @param vec a string vector which will contains the new string
 * @param str a string
 * @return 1 if the operation succeed, 0 if allocation fails or if there are not enough space to store the string, or if param are NULL
 */
int addStringToVector(StringVector *vec, char *str);

/**
 * @fn int removeStringToVector(StringVector *vec, char *str)
 * @brief remove a string from a string vector
 * @param vec a string vector which contains the string
 * @param str a string
 * @return 1 if the operation succeed, 0 if the string isn't there or if param are NULL
 */
int removeStringToVector(StringVector *vec, char *str);

/**
 * @fn void deleteStringVector(StringVector *vec)
 * @brief delete a string vector and its content
 * @param vec the string vector to delete
 */
void deleteStringVector(StringVector *vec);
