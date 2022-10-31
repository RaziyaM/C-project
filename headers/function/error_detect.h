int is_kind_src_op_legal(char *src_op, char * opcode);
int is_kind_dst_op_legal(char *dst_op, char * opcode);
int is_count_operand_legal(char * opcode, char * src_op, char * dst_op);
int is_opcode_legal(char * opcode);
int check_if_operands_legal(char * opcode, char * src_op, char * dst_op);


int check_directive_line(char * line, char * directive, int directive_case,char * data);
int is_directive_legal(char * directive);
int check_if_data_legal(int directive_case, char * data);


int check_label_legal(char * line, char * label_table);
int is_label_name_legal(char * label);

void print_ERORR(int error_index, int line_num);