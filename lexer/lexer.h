/* Lexer definitions and possible helpers */

/** State numbers
 */
#define END -2
#define INVALID -1
#define OPEN_BRACE 1
#define CLOSED_BRACE 2
#define OPEN_PAREN 3
#define CLOSED_PAREN 4
#define SEMICOLON 5
#define INTEGER 6
#define IDENTIFIER 7
#define IDENTIFIER2 8
#define WHITE_SPACE 9
#define OPERATOR 10
#define EQUAL_SIGN 11
#define KEYWORD 12

typedef struct stack_node {
	int state;
	char character;
	struct stack_node *next;
	struct stack_node *prev;
} stack_node;

void stack_node_init(struct stack_node *node) {
	node->state = END;
	node->character = INVALID;
	node->next = NULL;
	node->prev = NULL;
}


