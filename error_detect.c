#include "my_lib.h"
/*operation line check*/
int is_kind_src_op_legal(char *src_op, char * opcode)
{
    /*return error code if not legal, else return the miun method*/
    int kind;
    
    if(src_op == NULL && strstr(SRC_null_op, opcode) != NULL) return MIUN_METHOD_NULL;
    kind = kind_of_operand(src_op);
   /* printf("op=%s kind src=%d\n",src_op,kind);*/
    if (strstr(SRC_00, opcode) != NULL && kind == 0) return MIUN_METHOD_0;
    if (strstr(SRC_01, opcode) != NULL && kind == 1) return MIUN_METHOD_1;
    if (strstr(SRC_10, opcode) != NULL && kind == 2) return MIUN_METHOD_2;
    if (strstr(SRC_11, opcode) != NULL && kind == 3) return MIUN_METHOD_3;
    return type_of_src_op_not_legal;
}
int is_kind_dst_op_legal(char *dst_op, char * opcode)
{
    /*return error code if not legal, else return the miun method*/
    int kind;
    if(dst_op == NULL && strstr(DST_null_op, opcode) != NULL)return MIUN_METHOD_NULL;
    kind = kind_of_operand(dst_op);
    /*printf("op=%s kind dst=%d\n",dst_op,kind);*/
    if (strstr(DST_00, opcode) != NULL && kind == 0) return MIUN_METHOD_0;
    if (strstr(DST_01, opcode) != NULL && kind == 1) return MIUN_METHOD_1;
    if (strstr(DST_10, opcode) != NULL && kind == 2) return MIUN_METHOD_2;
    if (strstr(DST_11, opcode) != NULL && kind == 3) return MIUN_METHOD_3;

    return type_of_dst_op_not_legal;
}
int is_count_operand_legal(char * opcode, char * src_op, char * dst_op)
{
    int op_count;
    if (strstr(two_op_list, opcode) != NULL) op_count = 2;
    else if(strstr(one_op_list, opcode)) op_count = 1;
    else if(strstr(zero_op_list, opcode)) op_count = 0; 

    if(op_count==0 && src_op==NULL && dst_op==NULL)
        return OK;
    if(op_count==1 && src_op==NULL && dst_op!=NULL)
        return OK;
    if(op_count==2 && src_op!=NULL && dst_op!=NULL)
        return OK;
    return count_of_operand_not_legal;
}
int is_opcode_legal(char * opcode)
{
    if(strstr(OPCODE_LIST, opcode) != NULL) return OK;
    return Unrecognized_opcode_name;
}
int check_if_operands_legal(char * opcode, char * src_op, char * dst_op)
{
    int error_index = OK;
    if((error_index = is_count_operand_legal(opcode, src_op,dst_op)) == OK)
        {
            if(is_kind_src_op_legal(src_op, opcode) == type_of_src_op_not_legal) return type_of_src_op_not_legal;
            if(is_kind_dst_op_legal(dst_op, opcode) == type_of_dst_op_not_legal) return type_of_dst_op_not_legal;
        }
    return error_index;
}

/*directive line check*/
int check_directive_line(char * line, char * directive, int directive_case,char * data)
{
        int error_index;
        /*printf("line=%s, directive=%s, case=%d, data=%s\n", line, directive, directive_case, data);*/
        if((error_index = is_directive_legal(directive)) == OK)
            error_index = check_if_data_legal(directive_case, data);
        return error_index;
}
int is_directive_legal(char * directive)
{
    char * temp_directive = built_temp_str(directive);
    remove_white_spaces(temp_directive);
    if(strstr(DIRECTIVE_LIST, temp_directive) != NULL)
        return OK;
    return Directive_name_not_found;
}
int check_if_data_legal(int directive_case, char * data)
{
    char * operand,*temp_data;
    switch (directive_case)
    {
    case DATA_CASE:
        temp_data = strdup(data);
        operand = strtok(temp_data, ",");
        while( operand != NULL ) 
        {
            if(!is_space_in_middle(operand)) remove_spacesANDtabsANDenter(operand);
            else return data_operand_with_space;

            if(!is_str_is_num(operand) && !is_str_is_digit(operand)) return data_operand_not_number;
            
            if(is_str_empty(operand)) return data_operand_cant_be_empty;

            operand = strtok(NULL, ",");
        }
        break;

    case STRING_CASE:
        pass_white_spaces_from_the_begin(&data);
        if(*data == '\"')
        {
            data++;
            while(*data != '\"')
            {
                if(!isalpha(*data)) return string_operand_must_be_alpha;
                if(*data == END_OF_STR) return string_must_end_with;
                data++;
            }
            if(!is_str_empty(++data)) return garbage_data_after_string;
        }
        else return string_must_start_with;
        break;

    case STRUCT_CASE:
        temp_data = strdup(data);
        operand = strtok(temp_data, ",");
        while( operand != NULL ) 
        {
            if(!(check_if_data_legal(STRING_CASE, operand)== OK || check_if_data_legal(DATA_CASE, operand)==OK))
                return struct_operand_must_be_str_or_num;
            operand = strtok(NULL, ",");
        }
        break;
    
    default:
        break;
    }
        return OK;   
}

/*label check*/
int check_label_legal(char * line, char * label_table)
{
    char * temp_line = strdup(line);
    char * label_name = strtok(temp_line, ":");
    int error_flag;

    if((error_flag = is_label_name_legal(label_name)) == OK)
        {
            if(!is_label_defined(label_name, label_table))
                {
                    label_name = strtok(NULL, ":");
                    if(*label_name == TAB || *label_name == SPACE) /* check that there is space or tab before the operation or direction*/
                        return OK;
                    return Label_less_space_after_label_definition;
                }
            return Label_already_defined;
        }
     else return error_flag;
}
int is_label_name_legal(char * label)
{
    int i,label_len;
    pass_white_spaces_from_the_begin(&label);   /*clr the white spaces before the name*/

    if(is_space_in_middle(label))return Label_chars_only_alpha_or_digit;
    remove_white_spaces(label);
    label_len = strlen(label);
    
    if(label_len >= 30) return Label_len_not_legal;
       
    if(!isalpha(*label)) return Label_first_char_must_be_alpha;

    if(strstr(OPCODE_LIST, label)!= NULL)return Label_name_like_opcode;

    for(i=0; i<label_len; i++)
    {
        if(!isalpha(*(label+i)))
            {
                if(!isdigit(*(label + i))) return Label_chars_only_alpha_or_digit;
            }
    }

    return OK;
}


/*global*/
void print_ERORR(int error_index, int line_num)
{

    char *ERROR_LIST[] = {"OK","No space after label definition","Label already defined", "Label name not legal!! len should be max 30" ,
    "label name not legal!! first char must be aplha", "label name not ledgal!! you can enter only digits and alpha", "Label name cant be like opcode name",
    "Directive name not found. did you mean struct/string/data?",".data operand cant contain spaces", ".data operand must be number", 
    "string characters must be alpha", "string must start with quotation marks","string must ends with quotation marks",
    "struct operands must be legal string/number", "data operand cant be empty", "there is garbage data in the end of string definition"
    , "unidentified error, line too short","less space between opcode and operand", "Unrecognized opcode name", "Amount of operands does not match code name",
    "type of src operand not legal", "type of dst operand not legal","Unrecognized operand","Unrecognized directive name"};

    char * error = ERROR_LIST[error_index];
    printf("### ERROR! in line %d, %s ##\n", line_num, error);
}