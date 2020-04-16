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
	if (state == EQUAL_SIGN) {
		return -1;
	}
	if (state == OPERATOR) {
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
			case '=' :
				return EQUAL_SIGN;
				break;
			case '+' :
			case '-' :
			case '*' :
			case '/' :
				return OPERATOR;
				break;
			case ' ' :
				return WHITE_SPACE;
				break;
			case '\n' :
				return WHITE_SPACE;
				break;
			case '\t' :
				return WHITE_SPACE;
				break;
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
	if (state == WHITE_SPACE) {
		if ((curr == ' ') | (curr == '\n') | (curr == '\t')) {
			return WHITE_SPACE;
		} else {
			return INVALID;
		}
	}

	return -1;
}

/* Writes the state of the DFA to dest
 * Assumes valid end state
 */
void write_token(FILE *dest, int state) {
	int len;
	char token[50];
	memset(token, '\0', sizeof(token));
	switch (state) {
		case OPEN_BRACE :
			strncpy(token, "OPEN_BRACE ", 11);
			len = 11;
			break;
		case CLOSED_BRACE :
			strncpy(token, "CLOSED_BRACE ", 13);
			len = 13;
			break;
		case OPEN_PAREN :
			strncpy(token, "OPEN_PAREN ", 11);
			len = 11;
			break;
		case CLOSED_PAREN :
			strncpy(token, "CLOSED_PAREN ", 13);
			len = 13;
			break;
		case SEMICOLON :
			strncpy(token, "SEMICOLON ", 10);
			len = 10;
			break;
		case INTEGER :
			strncpy(token, "INTEGER ", 8);
			len = 8;
			break;
		case IDENTIFIER:
			strncpy(token, "IDENTIFIER ", 11);
			len = 11;
			break;
		case IDENTIFIER2 :
			strncpy(token, "IDENTIFIER2 ", 12);
			len = 12;
			break;
		case WHITE_SPACE :
			strncpy(token, "WHITE_SPACE ", 12);
			len = 12;
			break;
		case OPERATOR :
			strncpy(token, "OPERATOR ", 9);
			len = 9;
			break;
		case EQUAL_SIGN:
			strncpy(token, "EQUAL_SIGN ", 11);
			len = 11;
			break;
		case KEYWORD:
			strncpy(token, "KEYWORD ", 8);
			len = 8;
			break;
	}
	fwrite(&token, sizeof(char), len, dest);
	return ;
}

int is_keyword(char *token) {
	if (strcmp(token, "int") == 0) {
		return 0;
	}
	if (strcmp(token, "return") == 0) {
		return 0;
	}

	return 1;
}

int main(int argc, char **argv) {
	FILE *source;
	FILE *dest;
	source = fopen(argv[1], "r");
	if (!source) {
		perror("Source failed to open\n");
		exit(1);
	}
	dest = fopen("tokens", "w");
	if (!dest) {
		perror("Destination failed to open\n");
		exit(1);
	}
        	
	char curr;
	int state = 0;
	struct stack_node head;
	stack_node_init(&head);
	struct stack_node *tail = &head;
	int stack_size = 0;

	while (fread(&curr, sizeof(char), 1, source) == sizeof(char)) {
		state = move_state(state, curr);
		if (state == INVALID) {
			fseek(source, -1*sizeof(char), SEEK_CUR);
			while (tail->state == INVALID) { // Go back to last valid state
				if (tail->state == END) {
					perror("Rollback error\n");
					exit(1);
				}
				tail = tail->prev;
				fseek(source, -1*sizeof(char), SEEK_CUR);
				stack_size--;
			}
			// Write token to file
			char token[2*stack_size+1];
			struct stack_node *curr_node = head.next;
			struct stack_node *prev_node;
			int counter = 0;
			for (int i = 0; i < stack_size; i++) {
				if (curr_node->character == ' ') {
					token[counter] = '\\';
					counter++;
					token[counter] = 's';
					counter++;
				} else if (curr_node->character == '\n') {
					token[counter] = '\\';
					counter++;
					token[counter] = 'n';
					counter++;
				} else if (curr_node->character == '\t') {
					token[counter] = '\\';
					counter++;
					token[counter] = 't';
					counter++;
				} else {
					token[counter] = curr_node->character;
					counter++;
				}
				curr_node = curr_node->next;
			}
			token[counter] = '\0';
			if (is_keyword(token) == 0) {
				tail->state = KEYWORD;
			}
			write_token(dest, tail->state);
			token[counter] = '\n';
			fwrite(&token, sizeof(char), counter+1, dest);
			curr_node = head.next;
			for (int i = 0; i < stack_size; i++) {
				prev_node = curr_node;
				curr_node = curr_node->next;
				free(prev_node);
			}
			// Clear Stack
			head.next = NULL;
			tail = &head;
			stack_size = 0;
			state = 0;
		} else {
			struct stack_node *new_node = malloc(sizeof(struct stack_node));
			stack_node_init(new_node);
			new_node->state = state;
			new_node->character = curr;
			new_node->prev = tail;
			tail->next = new_node;
			tail = new_node;
			stack_size++;
		}

	}
	struct stack_node *curr_node = head.next;
	struct stack_node *prev_node;
	for (int i = 0; i < stack_size; i ++) {
		prev_node = curr_node;
		curr_node = curr_node->next;
		free(prev_node);
	}

	fclose(dest);
	fclose(source);

	return 0;
}
