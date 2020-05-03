/* Basic Parser for arithmetic */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "productions.h"

FILE *tokens;
char *line;
char **lineptr = &line;
size_t line_size;

int main(int argc, char **argv) {
	(void) argc;
	tokens = fopen(argv[1], "r");
	if (!tokens) {
		perror("token file failed to open\n");
		exit(1);
	}

	int check = program();

	if (check == 1) {
		printf("No parsing error!\n");
	} else {
		printf("Parsing error.\n");
	}
	
	free(line);
	fclose(tokens);	
	
	return 0;

}
