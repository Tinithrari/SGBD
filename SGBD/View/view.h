#define ADD_KEYWORD 			"ADD"
#define DELETE_KEYWORD 			"DEL"
#define DISPLAY_KEYWORD 		"DISP"

#define TUPLE_KEYWORD 			"TUPLE"
#define TABLE_KEYWORD 			"TABLE"
#define COL_KEYWORD 			"COL"

#define SET_TUPLES_KEYWORD		"TUPLES"
#define SET_TABLES_KEYWORD		"TABLES"
#define SET_COLS_KEWORD			"COLS"

#define QUIT_KEYWORD			"QUIT"

#define ERROR_HEADER			"ERR: "

#define UNKNOWN_KEYWORD			"ERR: UNKNOWN_KEYWORD "

#define TOO_MUCH_WORDS			"ERR: TOO_MUCH_WORDS"
#define NOT_ENOUGH_WORDS		"ERR: NOT_ENOUGH_WORDS"

typedef void (*DisplayFunc)(char *str);
