/* Booleans */
#define TRUE 1
#define FALSE 0

/* Maximum size of machine code array - provides at least 200 code lines in *.as file */
#define CODE_ARR_IMG_LENGTH 1200
#define MAX_LINE_LENGTH 80

/* moves the index to the next place in string where the char isn't white */
#define MOVE_TO_NOT_WHITE(string, index) \
		for (;!string[index] && (string[index] == '\t' || string[index] == ' '); ++(index)) ;

#define MOVE_UNTIL_CHAR_OR_WHITE(string, index, char)\
		for (;!string[index] || string[index] == '\t' || string[index] == ' ' || string[index] == char; ++(index)) ;

/* Returns whether a string contains a symbol from a certain index. */
int parse_symbol(char *line, int, char*);

/* Writes 2 bytes in order to buffer from index */
void write_word(char* buffer, int index, char byte0, char byte1, char byte2);

/* TODO: DOC */
int is_int(char* string);