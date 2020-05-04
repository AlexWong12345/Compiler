/* Definitions and helpers used by parser.c */

/* A node for AST */
struct ast_node {
	int item; /* The production the node contains */
	int num_children; 
	struct ast_node *children[]; /* The Children branching off of this node */
};

/* Adds a node to the ast_node node 
 */
void add_node(struct ast_node *node) {
	node->num_children++;
	
}
