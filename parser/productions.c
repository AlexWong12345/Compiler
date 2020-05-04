/* Grammar Productions 
 *
 * Currently assumes Backtracking is needed
 * Need to change the grammar to a backtrack-free one in the future
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "productions.h"
#include "parser.h"


/* A program is a list of functions
 * 
 * TODO: This needs to be changed later to:
 *
 * 	P -> Function
 * 	  |  Function P
 * 	  |  Assignment ### Assignment used to check for global variables
 * 	  |  Assignment P
 *
 * Currently uses a loop to look for more functions
 */
int program() {
	int ret = 1;
	int end = 0;
	int read_size;
	while (ret && !end) {
		ret = function();
		read_size = getline(lineptr, &line_size, tokens);
		if (read_size == -1) { // EOF
			end++;
		} else { // Unread the line
			fseek(tokens, -1*read_size, SEEK_CUR);
		}
	}

	(void) head;
	return ret;
}

/* A function has a header and a body
 *
 */

int function() {
	return 0;

}
