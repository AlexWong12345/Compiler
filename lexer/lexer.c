/* Main Lexer file. 
 * Takes a file and produces a new file with the format:
 *                  TOKEN_TYPE STRING
 * Each line is a token to be used by the parser
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

int move_state(int state, char curr){ 
	if ((state == OPEN_BRACE) | (state == CLOSED_BRACE)) {
		return -1;
	} 
	if ((state == OPEN_PAREN) | (state == CLOSED_PAREN)) {
		return -1;
	} 
	if (state == SEMICOLON) {
		return -1;
	} 
	if (state == 0) { // Empty State
		switch(curr) {
			case '{' :
				return OPEN_BRACE;
				break;
			case '}' :
				return CLOSED_BRACE;
				break;
			case '(' :
				return OPEN_PAREN;
				break;
			case ')' :
				return CLOSED_PAREN;
				break;
			case ';' :
				return SEMICOLON;
				break;
			case ' ' :
				return WHITE_SPACE;
			case '\n' :
				return WHITE_SPACE;
			case '\t' :
				return WHITE_SPACE;
			}
		if (isdigit(curr)) {
			return INTEGER;
		}
		if (isalpha(curr)) {
			return IDENTIFIER;
		}
	}
	if (state == INTEGER) {
		if (isdigit(curr)) {
			return INTEGER;
		} else { 
			return INVALID;
		}
	}
	if (state == IDENTIFIER) {
		if (isalpha(curr)) {
			return IDENTIFIER2;
		} else {
			return INVALID;
		}
	}
	if (state == IDENTIFIER2) {
		if ((isalnum(curr)) | (curr == '_')) {
			return IDENTIFIER2;
		} else {
			return INVALID;
		}
	}

	return -1;
}

int main(int argc, char **argv) {
	FILE *source;
	FILE *dest;
	source = fopen(argv[1], "r");
	if (!source) {
		perror("Source failed to open");
		exit(1);
	}
	dest = fopen("tokens", "w");
	if (!dest) {
		perror("Destination failed to open");
		exit(1);
	}
        	
	char curr;
	int state = 0;

	while (fread(&curr, sizeof(char), 1, source) == sizeof(char)) {
		state = move_state(state, curr);
		if (state == INVALID) {
			// Do Stuff
			
		}

	}
	/*
	fread(&curr, sizeof(char), 1, source);
	fread(&curr, sizeof(char), 1, source);
	fseek(source, -sizeof(char), SEEK_CUR);
	curr = 'a';
	fread(&curr, sizeof(char), 1, source);
	fwrite(&curr, sizeof(char), 1, dest);
	*/
	return 0;
}
