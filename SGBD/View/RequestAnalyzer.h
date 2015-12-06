#define UNKNOWN_KEYWORD			"ERR: UNKNOWN_KEYWORD "

#define TOO_MUCH_WORDS			"ERR: TOO_MUCH_WORDS"
#define NOT_ENOUGH_WORDS		"ERR: NOT_ENOUGH_WORDS"

void analyzeRequest(StringVector *request, DisplayFunc fct, Database *db);
