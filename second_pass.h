
#ifndef _SECOND_PASS_H
#define _SECOND_PASS_H
#include "constants.h"
#include "table.h"

/**
 * Processes a single source line in the second pass
 * @param line The source line
 * @param ic A pointer to the current instruction counter
 * @param code_img The code image
 * @param symbol_table The symbol table
 * @return Whether succeeded
 */
bool process_line_spass(char *line, long *ic, machine_word **code_img, table *symbol_table);

/**
 * Adds the symbol-dependent data words by the code line.
 * @param line The source code line
 * @param ic A pointer to the current instruction counter
 * @param code_img The code image
 * @param symbol_table The symbol table
 * @return Whether succeeded
 */
bool add_symbols_to_code(char *line, long *ic, machine_word **code_img, table *symbol_table);

#endif