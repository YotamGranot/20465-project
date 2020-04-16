#include "instructions_handler.h"
#include <string.h>
#include "globals.h"
#include "utils.h"

/* Returns the first instruction from the specified index. if no such one, returns NONE */
instruction_type find_instruction_from_index(char *string, int index){
	char temp[MAX_LINE_LENGTH];
	int j;
	MOVE_TO_NOT_WHITE(string, index); /* get index to first not white place */
	if (string[index] != '.') return NONE;

	for (j = 0;string[index] && string[index] != '\t' && string[index] != ' ';index++,j++) {
		temp[j] = string[index];
	}

	if (strcmp(temp, ".extern") == 0) {
		return EXTERN;
	}
	else if (strcmp(temp, ".data") == 0) {
		return DATA;
	}
	else if (strcmp(temp, ".entry") == 0) {
		return ENTRY;
	}

}

/* Instruction line processing helper functions */
/*
 * Processes a line data instruction. puts 2 empty bytes in the data_img array and then 2bytes of the char, for each char.
 * Returns the count of processed chars.
 * */
int process_string_instruction(char *line, int index, char* data_img, int data_img_indx) {
	int cntr; /* counts processed chars amount */
	data_img_indx *= 3; /* We need to find location in char array. each word is 3-byte, char in ansi-c is 1-byte */
	MOVE_TO_NOT_WHITE(line, index)
	if (line[index] == '"') {
		index++;
		/* Foreach char between the two " */
		for (cntr = 0;line[index] != '"';index++) {
			/* ASCII char is 1byte but one word is 3byte. we need to insert 2 zero-bytes, and then the actual data */
			data_img[data_img_indx++] = '\0';
			data_img[data_img_indx++] = '\0';
			data_img[data_img_indx++] = line[index];
		}
	}
	/* Return processed chars count */
	return cntr;
}

/*
 * Parses a .data instruction. copies each number value to data_img by dc position, and returns the amount of processed data.
 */
int process_data_instruction(char *line, int index, char *data_img, int dc) {
	char temp[80], byte0, byte1, byte2;
	int i, curr_val, data_counter;
	data_counter = 0;
	do {
		MOVE_TO_NOT_WHITE(line, index)
		for (i = 0; line[index] && line[index] != EOF && line[index] != '\t' && line[index] != ' ' && line[index] != ',' ; index++,i++) {
			temp[i] = line[index];
		}
		temp[i] = '\0'; /* End of string */
		if (!is_int(temp)) {
			/* TODO: Write error and return flag that indicates error (somehow) */
			fprintf(stderr, "Error: line : expected number after .data instruction (got %s)", temp)
			return FALSE;
		}
		int curr_val = atoi(temp);
		/* Now let's write to data buffer */
		byte0 = (curr_val >> 16) & 0xFF;
		byte1 = (curr_val >> 8) & 0xFF;
		byte2 = curr_val & 0xFF;
		write_word(data_img, dc, byte0, byte1, byte2);
		data_counter++; /* a word was written right now */
		MOVE_TO_NOT_WHITE(line, index)
		if (line[index] != '\n' && line[index] != EOF && line[index] != ',') {
			/* We're after parsed number, after all white chars but no comma or end of line. */
			/* TODO: Error, Unexpected char or something */
			fprintf(stderr, "Error: line : expected comma separation between integers (char '%c')", line[index]);
		}
	} while (line[index] != '\n' && line[index] != EOF);
	return data_counter;
}