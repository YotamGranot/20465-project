#include "globals.h"

/**
 * Returns the first instruction detected from the index in the string.
 * @param string The source string.
 * @param index The index to start looking from.
 * @return instruction_type indicates the detected instruction.
 */
instruction_type find_instruction_from_index(char *string, int *index);

/**
 * Processes a .string instruction from index of source line.
 * @param line The source line
 * @param index The index
 * @param data_img The current data image
 * @param dc The current data counter
 * @return Whether succeeded
 */
bool process_string_instruction(char *line, int index, machine_data **data_img, long *dc);

/**
 * Processes a .data instruction from index of source line.
 * @param line The source line
 * @param index The index
 * @param data_img The data image
 * @param dc The current data counter
 * @return Whether succeeded
 */
bool process_data_instruction(char *line, int index, machine_data **data_img, long *dc);