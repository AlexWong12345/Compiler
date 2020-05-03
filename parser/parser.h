/* Definitions and helpers used by parser.c */

/* A node for AST */
struct ast_node {
	int item; /* The production the node contains */
	int num_children; 
	struct ast_node *children[]; /* The Children branching off of this node */
};


