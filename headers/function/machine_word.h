char * find_label(char* line);
int is_label_defined(char * label, char * label_table);
void add_label_to_table(char ** label_table, char * label, int dc);
int return_label_value(char * label_table,char * label);

int is_entry(char * line);
int is_extern(char * line);
void add_ex_to_table(char ** table, char * line);
void add_ent_to_table(char ** table, char * line);

int emptyORcomment(char * line);
int directiveOroperation(char * line);
int is_EMPTY_COMMENT_DIRECTIVE_OPERATION(char * line);
int is_dataORstructORstr( char * line);

int split_opcode_operand(char * line, char ** opcode, char ** src_op, char ** dst_op);
int kind_of_operand(char * operand);
char * return_miun_method_str(int miun);
char * built_opcode_MW(char * opcode, int src_miun, int dst_miun);
char * built_MW_per_operation_operand(char * operand, int miun_method, int src_or_dst, int * IC);
char * built_MW_operation_line(char * opcode, char * src_op, char * dst_op, int * IC);

void split_direction_operand(char * line, char ** directive, int * directive_case, char ** data);
char * built_MW_to_directive_line( int directive_case,char * data ,int * dc);
int arrange_data_operand(char * operand);

char * stringush(char * operand,int * dc);
char * datush(char * operand,int * dc);
char * struct_data(char * operand, int * dc);
char * structush(char * operands,int * dc);
int built_machine_code(char * line, int operationORdirective,  int * dc_OR_ic, char * label_table, int line_counter , char ** ic_OR_dc_arr_head);