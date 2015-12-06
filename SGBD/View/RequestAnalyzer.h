const char **synthaxError

#define UNKNOWN_KEYWORD			"UNKNOWN_KEYWORD "

#define TOO_MUCH_WORDS			"TOO_MUCH_WORDS"
#define NOT_ENOUGH_WORDS		"NOT_ENOUGH_WORDS"

void analyzeRequest(StringVector *request, DisplayFunc fct, Database *db);
