#include "./headers/lib/lib.h"
#include "./headers/functions/functions.h"

#define EMPTY_STR ""
#define FILE_EX_as ".as"
#define FILE_EX_txt ".txt"
#define FILE_EX_ob ".ob"
#define FILE_EX_ent ".ent"
#define FILE_EX_ex ".ext"
#define SPACE ' '
#define TAB '\t'
#define ENTER '\n'
#define POINT '.'
#define SEPARATION "."
#define LEN_OF_THE_WORD_MACRO 5
#define MAX_MACRO_NAME_LEN 81
#define END_OF_STR '\0'
#define MACRO "macro"
#define END_OF_MACRO "endmacro"
#define YES_DEF 1
#define NO_DEF 0

#define Base32 "!@#$%^&*<>abcdefghijklmnopqrstuv"
#define DATA "data"
#define STRUCT "struct"
#define STRING "string"
#define EXTERN "extern"
#define ENTRY "entry"


#define STRING_CASE 1
#define STRUCT_CASE 2
#define DATA_CASE 3
#define ENTERY_CASE 4
#define EXTERN_CASE 5

#define PLUS '+'
#define MINUS '-'

#define SRC 1
#define DST 2

#define MIUN_METHOD_0 0
#define MIUN_METHOD_1 1
#define MIUN_METHOD_2 2
#define MIUN_METHOD_3 3
#define MIUN_METHOD_NULL 4

#define MIUN_STR_0 "00"
#define MIUN_STR_1 "01"
#define MIUN_STR_2 "10"
#define MIUN_STR_3 "11"
#define EXTERNAL_LABEL "0000000001"
#define SPLITE_TABLE_1 "$"


#define MOV_CASE 0
#define CMP_CASE 1
#define ADD_CASE 2
#define SUB_CASE 3
#define NOT_CASE 4
#define CLR_CASE 5
#define LEA_CASE 6
#define INC_CASE 7
#define DEC_CASE 8
#define JMP_CASE 9
#define BNE_CASE 10
#define GET_CASE 11
#define PRN_CASE 12
#define JSR_CASE 13
#define RTS_CASE 14
#define HLT_CASE 15


#define A "00"
#define R "10"
#define E "01"

#define SPLIT_MW "|"
#define OPCODE_LIST   "mov,cmp,add,sub,not,clr,lea,inc,dec,jmp,bne,get,prn,jsr,rts,hlt"
#define DIRECTIVE_LIST "string\nstruct\ndata\nentry\nextern\n"
#define REG_LIST "r0\nr1\nr2\nr3\nr4\nr5\nr6\nr7\nr8"

#define EMPTY_CASE 0
#define COMMENT_CASE 1
#define DIRECTIVE_CASE 2
#define OPERATION_CASE 3
#define STRANGE 4

#define SRC_00  "mov cmp add sub"
#define SRC_01  "mov cmp add sub lea"
#define SRC_10 "mov cmp add sub lea"
#define SRC_11 "mov cmp add sub"
#define SRC_null_op "not clr inc dec jmp bne get prn jsr rts hlt"

#define DST_00 "cmp prn"
#define DST_01 "mov cmp add sub lea not clr inc dec jmp bne get prn jsr"
#define DST_10 "mov cmp add sub lea not clr inc dec jmp bne get prn jsr"
#define DST_11 "mov cmp add sub lea not clr inc dec jmp bne get prn jsr"
#define DST_null_op "rts hlt"

#define two_op_list "mov cmp add sub lea"
#define one_op_list "not clr inc dec jmp bne get prn jsr"
#define zero_op_list "rts hlt"


    enum error 
    {
    OK,
    Label_less_space_after_label_definition,
    Label_already_defined,
    Label_len_not_legal,
    Label_first_char_must_be_alpha,
    Label_chars_only_alpha_or_digit,
    Label_name_like_opcode,
    Directive_name_not_found,
    data_operand_with_space,
    data_operand_not_number,
    string_operand_must_be_alpha,
    string_must_start_with,
    string_must_end_with,
    struct_operand_must_be_str_or_num,
    data_operand_cant_be_empty,
    garbage_data_after_string,
    short_line_error,
    less_space_between_opcode_and_operand,
    Unrecognized_opcode_name,
    count_of_operand_not_legal,
    type_of_src_op_not_legal,
    type_of_dst_op_not_legal,
    Unrecognized_operand_type,
    Unrecognized_directive_name

} ;


 