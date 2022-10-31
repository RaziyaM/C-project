#include "my_lib.h"
/*label, entry and extern function*/
char * find_label(char* line)
{
    char * temp_line,* ptr_to_colon, *ptr_to_QM;
    
    temp_line = built_temp_str(line);
    ptr_to_QM = strchr(temp_line,'\"');
    ptr_to_colon = strchr(temp_line,':');

    if(ptr_to_colon == NULL) return NULL;
    else if(ptr_to_QM == NULL)
         return ptr_to_colon;
    else if (ptr_to_QM > ptr_to_colon) /*check if the colon is in string and not define symbol*/
            return ptr_to_colon;
    return NULL;
}
int is_label_defined(char * label, char * label_table)
{
    return(strstr(label_table,label)!=NULL);
}
void add_label_to_table(char ** label_table, char * label, int dc)
{    
        char dc_str[30];
        sprintf(dc_str, "%d", dc);
        *label_table = string_append(*label_table, label);
        *label_table = string_append(*label_table, SPLITE_TABLE_1);
        *label_table = string_append(*label_table, dc_str);
        *label_table = string_append(*label_table, SPLITE_TABLE_1);
}
int return_label_value(char * label_table,char * label)
{
    int i = 0;
    char * temp = strstr(label_table,label);
    char * label_value = built_temp_str(temp),*value;
    label_value += strlen(label);
    label_value += strlen(SPLITE_TABLE_1);
    temp = label_value;
    while(*label_value!='$' && *label_value!=END_OF_STR)
    {
        i++;
        label_value++;
    }
    value = copy_str_until_index(temp, i);
    return atoi(value);
}

/*entry and extern*/
int is_entry(char * line)
{
    char * temp_line = built_temp_str(line);
    int i,len=strlen(ENTRY),flag=1;
    /*pass_white_spaces_from_the_begin(&temp_line);*/
    if(*temp_line == POINT)
    {
        temp_line++;
        for(i=0; i<len;i++)
        {
            if(!(temp_line[i]==ENTRY[i]))
                flag = 0;
        }
    }

    return flag;     
}
int is_extern(char * line)
{
    {
    char * temp_line = built_temp_str(line);
    int i,len=strlen(EXTERN),flag=1;
    /*pass_white_spaces_from_the_begin(&temp_line);*/
    if(*temp_line == POINT)
    {
        temp_line++;
        for(i=0; i<len;i++)
        {
            if(!(temp_line[i]==EXTERN[i]))
                flag = 0;
        }
    }

    return flag;     
}
}
void add_ex_to_table(char ** table, char * line)
{
    char * label = built_temp_str(line);
    pass_white_spaces_from_the_begin(&label);
    label += strlen(EXTERN)+1;
    remove_white_spaces(label);
    *table = string_append(*table, label);
    *table = string_append(*table, SPLITE_TABLE_1);
}
void add_ent_to_table(char ** table, char * line)
{
    char * label = built_temp_str(line);
    pass_white_spaces_from_the_begin(&label);
    label += strlen(ENTRY)+1;
    remove_white_spaces(label);
    *table = string_append(*table, label);
    *table = string_append(*table, SPLITE_TABLE_1);
}

/* 4 kind of line - empty, comment, directive and operation*/
int emptyORcomment(char * line)
{
    char * temp_line = strdup(line);
    remove_white_spaces(temp_line);
    return ((equal_str(temp_line, EMPTY_STR))||(*temp_line == ';'));
}
int directiveOroperation(char * line)
{
    char *ptr_to_point = line, * temp_opcode;
    pass_white_spaces_from_the_begin(&ptr_to_point);
    if(*ptr_to_point== POINT)
    {
        if(is_extern(ptr_to_point)) return EXTERN_CASE;
        else if(is_entry(ptr_to_point)) return ENTERY_CASE;
        else return DIRECTIVE_CASE;
    }
    temp_opcode = copy_str_until_index(ptr_to_point, 2);
    if(strstr(OPCODE_LIST,temp_opcode))
        return OPERATION_CASE;
    return STRANGE;
}
int is_EMPTY_COMMENT_DIRECTIVE_OPERATION(char * line)
{
    if(emptyORcomment(line)) return COMMENT_CASE;
    return directiveOroperation(line);
}
int is_dataORstructORstr( char * line)
{
    remove_white_spaces(line);
    if(strstr(line, STRING)!=NULL) return STRING_CASE;
    if(strstr(line, STRUCT)!= NULL) return STRUCT_CASE;
    if(strstr(line, DATA)!= NULL) return DATA_CASE;
    return 0;
}


/*operation*/
int split_opcode_operand(char * line, char ** opcode, char ** src_op, char ** dst_op)
{
    pass_white_spaces_from_the_begin(&line);

    if(strlen(line) < 3) return short_line_error;
    *opcode = copy_str_until_index(line, 2);
    line +=3;

    if(!isspace(*line)) return less_space_between_opcode_and_operand;

    pass_white_spaces_from_the_begin(&line);
   *src_op = strtok(line,",");
   *dst_op = strtok(NULL, ",");

   if(*dst_op == NULL && *src_op!= NULL)
   {
    *dst_op = *src_op;
    *src_op = NULL;
   }

    return OK;
}
int kind_of_operand(char * operand)
{
    char * temp_label, *temp_operand, *temp_index;
    if(operand == NULL) return MIUN_METHOD_NULL;
    temp_operand = built_temp_str(operand);
    
    if(is_space_in_middle(operand)) return Unrecognized_operand_type;
    remove_white_spaces(operand);
    if(*operand == '#' && is_str_is_num(++operand))return MIUN_METHOD_0;

    if (strstr(REG_LIST, operand) != NULL) return MIUN_METHOD_3;

    if(is_label_name_legal(operand)==OK)return MIUN_METHOD_1;

    if(strstr(temp_operand, ".")!=NULL)
    {
        temp_label = strtok(temp_operand, ".");
        temp_index = strtok(NULL, ".");
        if((is_label_name_legal(temp_label)==OK) && is_str_is_digit(temp_index)) return MIUN_METHOD_2;
    }

    return Unrecognized_operand_type;
}
char * return_miun_method_str(int miun)
{
    switch (miun)
    {
    case MIUN_METHOD_0:
        return MIUN_STR_0;
        break;
    case MIUN_METHOD_1:
        return MIUN_STR_1;
        break;
    case MIUN_METHOD_2:
        return MIUN_STR_2;
        break;
    case MIUN_METHOD_3:
        return MIUN_STR_3;
        break;
    case MIUN_METHOD_NULL:
        return MIUN_STR_0;
        break;
    
    default:
        break;
    }
    return NULL;
}
char * built_opcode_MW(char * opcode, int src_miun, int dst_miun)
{
    char * temp_MW = EMPTY_STR;

    temp_MW = string_append(temp_MW,return_opcode_binary_str(opcode));
    temp_MW = string_append(temp_MW, return_miun_method_str(src_miun));
    temp_MW = string_append(temp_MW,return_miun_method_str(dst_miun));
    temp_MW = string_append(temp_MW,A);
    temp_MW = string_append(temp_MW,SPLIT_MW);
    return temp_MW;
}
char * built_MW_per_operation_operand(char * operand, int miun_method, int src_or_dst, int * IC)
{
    char * temp_MW = EMPTY_STR;
    switch (miun_method)
    {
    case MIUN_METHOD_0:
        temp_MW = string_append(temp_MW, return_imm_num_binary(operand));
        temp_MW = string_append(temp_MW, A);
        (*IC)++;
        break;
    case MIUN_METHOD_1:
        temp_MW = string_append(temp_MW, operand);
        (*IC)++;
        break;
    case MIUN_METHOD_2:
        temp_MW = string_append(temp_MW, return_struct_binary(operand));
        (*IC)+=2;
        break;
    case MIUN_METHOD_3:
        if(src_or_dst == SRC)
            {
                temp_MW = string_append(temp_MW, return_reg_binary(operand));
                temp_MW = string_append(temp_MW, "0000");
                temp_MW = string_append(temp_MW, A);
            }
        else
            {
                temp_MW = string_append(temp_MW, "0000");
                temp_MW = string_append(temp_MW, return_reg_binary(operand));
                temp_MW = string_append(temp_MW, A);
            }
        (*IC)++;
        break;

    default:
        break;
    }
    return temp_MW;
}
char * built_MW_operation_line(char * opcode, char * src_op, char * dst_op, int * IC)
{
    char * temp_MW = EMPTY_STR;
    int src_miun = kind_of_operand(src_op);
    int dst_miun = kind_of_operand(dst_op);

    temp_MW = string_append(temp_MW, built_opcode_MW(opcode, src_miun,dst_miun));
    (*IC)++;

    if((src_miun == MIUN_METHOD_3) && (dst_miun == MIUN_METHOD_3))
        {
            temp_MW = string_append(temp_MW, return_reg_binary(dst_op));
            temp_MW = string_append(temp_MW, return_reg_binary(src_op));
            temp_MW = string_append(temp_MW, A);
            temp_MW = string_append(temp_MW, SPLIT_MW);
            (*IC)++;
        }
    else
    {
        if(src_miun != MIUN_METHOD_NULL)
        {
        temp_MW = string_append(temp_MW, built_MW_per_operation_operand(src_op, src_miun, SRC,IC));
        temp_MW = string_append(temp_MW, SPLIT_MW);
        }
        if(dst_miun != MIUN_METHOD_NULL)
        {
        temp_MW = string_append(temp_MW, built_MW_per_operation_operand(dst_op, dst_miun, DST,IC));
        temp_MW = string_append(temp_MW, SPLIT_MW);
        }
    }

    return temp_MW;
}

/*directive*/
void split_direction_operand(char * line, char ** directive, int * directive_case, char ** data)
{
    char * operand;
    if(*line != POINT) 
    {
    operand = strtok(line, ".");
    operand = strtok(NULL, " \t");
    *directive = built_temp_str(operand);
    *directive_case = is_dataORstructORstr(*directive);
    operand = strtok(NULL, "");
    *data = built_temp_str(operand);
    }

    else
    {
    operand = strtok(line, ". \t");
    *directive = built_temp_str(operand);
    operand = strtok(NULL, " \t");
    *directive_case = is_dataORstructORstr(*directive);
    *data = built_temp_str(operand);
    }
}
char * built_MW_to_directive_line( int directive_case,char * data ,int * dc)
{
    char * temp_MW;
    switch (directive_case)
    {
    case STRING_CASE:
        temp_MW = stringush(data,dc);
        break;
    case STRUCT_CASE:
        temp_MW = structush(data,dc);
        break;
    case DATA_CASE:
        temp_MW = datush(data,dc);
        break;
    
    default:
        break;
    }
    return temp_MW;
}
int arrange_data_operand(char * operand)
{
    char sign = PLUS;
    char * temp_operand = built_temp_str(operand);
    remove_spacesANDtabsANDenter(temp_operand);

    if(temp_operand[0] == MINUS || temp_operand[0] == PLUS)
    {
        sign = temp_operand[0];
        temp_operand ++;
    }

    if(sign == PLUS)
        return atoi(temp_operand);

    return atoi(temp_operand) * -1 ;

}

/*global*/
char * stringush(char * operand,int * dc)
{
    char * temp_MW = EMPTY_STR;

    /* get the first token to string values */
    pass_white_spaces_from_the_begin(&operand);
    operand++;

    while(*operand != '\"')
    {
        temp_MW = string_append(temp_MW, int_to_bin(*operand,10));
        temp_MW = string_append(temp_MW, "|");
        (*dc)++;
        operand++;
    }
    temp_MW = string_append(temp_MW, "0000000000");
    temp_MW = string_append(temp_MW, "|");
    (*dc)++;
    /*printf("we in string! tempMW=%s\n", temp_MW);*/
    return temp_MW;
}
char * datush(char * operand,int * dc)
{

    char * temp_MW="";

    operand = strtok(operand,",");
    while( operand != NULL ) 
    {
    (*dc)++;
    temp_MW = string_append(temp_MW, int_to_bin(arrange_data_operand(operand),10));
    temp_MW = string_append(temp_MW, "|");
    operand = strtok(NULL,",");
    }

   /* printf("im in data, tempMW=%s", temp_MW);*/
    return temp_MW;
}
char * struct_data(char * operand, int * dc)
{
    char * temp_MW = EMPTY_STR;
    temp_MW = string_append(temp_MW, int_to_bin(arrange_data_operand(operand),10));
    temp_MW = string_append(temp_MW, "|");
    return temp_MW;
}
char * structush(char * operands,int * dc)
{
    char * temp_MW = "";
    char * operand;
    char * temp_operands = strdup(operands);

    /* get the first token to operands */
   temp_operands = strtok(temp_operands,",");

    while(temp_operands != NULL)
    {
        operand = built_temp_str(temp_operands);
        if(*temp_operands == '\"') temp_MW = string_append(temp_MW,stringush(operand, dc));
        else temp_MW = string_append(temp_MW, struct_data(operand,dc));
        (*dc)++;
        temp_operands = strtok(NULL, ",");
    }

    /*printf("\nwe in struct! temp_MW =%s\n", temp_MW);*/
    return temp_MW;
}

int built_machine_code(char * line, int operationORdirective,  int * dc_OR_ic, char * label_table, int line_counter , char ** ic_OR_dc_arr_head)
{
    int directive_case;
    int error = 1;
    char * directive, *data;
    char * opcode=NULL, *src_op=NULL,*dst_op=NULL;



    if(operationORdirective == DIRECTIVE_CASE)
    {
        split_direction_operand(line, &directive, &directive_case,&data);
        error = check_directive_line(line, directive,directive_case,data);
        if(error != OK) print_ERORR(error,line_counter);
        else *ic_OR_dc_arr_head = string_append(*ic_OR_dc_arr_head,built_MW_to_directive_line(directive_case,data,dc_OR_ic));
        
    }
    else
    {
        if((error = split_opcode_operand(line,&opcode,&src_op,&dst_op))==OK)
        {
            if((error = is_opcode_legal(opcode))== OK)
                    error = check_if_operands_legal(opcode, src_op,dst_op);
        }
        if(error != OK) print_ERORR(error,line_counter);
        else *ic_OR_dc_arr_head = string_append(*ic_OR_dc_arr_head, built_MW_operation_line(opcode, src_op, dst_op,dc_OR_ic));

    }

    return error;
}


