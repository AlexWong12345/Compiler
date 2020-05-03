/* Production signatures */

extern FILE *tokens;
extern char *line;
extern char **lineptr;
extern size_t line_size;


int program();
int function();
int statement();
int expression();
