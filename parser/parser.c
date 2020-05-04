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
struct ast_node *head;

int main(int argc, char **argv) {
	(void) argc;
	tokens = fopen(argv[1], "r");
	if (!tokens) {
		perror("token file failed to open\n");
		exit(1);
	}

	head = malloc(sizeof(struct ast_node) + sizeof(struct ast_node*));
	head->num_children = 0;
	head->item = 0;
	head->children[0] = head;
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
