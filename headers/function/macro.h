int if_macro_define(char *line, char * macro_names_list);
char * find_macro_name_in_definition_with_spaces_in_the_end(char *line);
char * find_macro_name_not_in_definition_with_spaces_in_the_end(char *line);
int is_macro_name_legal(char * macro_name);
char * return_macro_name(char * line, int is_def);



struct macro {
    char mname[80];
    char mcontent[2000];
    struct macro* next;
};
typedef struct macro macro;

void printList(macro* m);
void insert_macro(char *name,char *content, macro *head);
void insert_head(char *name,char *content, macro *head);
int if_macro_name_in_list(char *macro_names_list,char *line);
char * return_macro_content(char *macro_name,macro *head);