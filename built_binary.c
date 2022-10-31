#include "my_lib.h"
#include <math.h>


char * int_to_bin(int num, int bits_len)
{
    int i;
    int stam = 1;
    char * binary_code = calloc(10,sizeof(char));
    for(i=0; i<bits_len;i++)
    {

        if(num & stam)
            binary_code[i] = '1';
        else
            binary_code[i] = '0';
        stam *=2;
    }


    str_reverse(binary_code);
    return binary_code;
}

char * return_reg_binary(char * reg)
{

    return int_to_bin(atoi(++reg),4);
}

char * return_opcode_binary_str(char * _opcode)
{
    int _op = return_opcode_index(_opcode);
    return int_to_bin(_op, 4);
}

int return_opcode_index(char * opcode)
{
    char * temp_list = built_temp_str(OPCODE_LIST);
    char * temp_pointer = strstr(temp_list, opcode);
    int index = ( temp_pointer - temp_list)/4;
    return index;

}

char * convert_my_base32(char * binary_str)
{
    int decimal = from_bin_to_dec(binary_str);
    char *temp = calloc(2,sizeof(char));
    temp[0] = Base32[decimal];
    temp[1] = END_OF_STR;
    return temp;
}


int from_bin_to_dec(char * bin_num)

{
    /* bin num in 5 bits size*/ 
    int i;
    int num = 0;

    for(i = 4; i>=0; i--)
    {
        if(bin_num[i]== '1') /*if there is 1 we need to add the number*/
            num += pow(2,4-i);
    }
    return num;
}

char * return_imm_num_binary(char * operand)
{
    char * temp = int_to_bin(arrange_data_operand(++operand),8);
    return temp;
}


char * return_struct_index_binary(char * index)
{
    char * temp = built_temp_str(int_to_bin(atoi(index), 8));
    temp = string_append(temp, A);
    return temp;
}
char * return_struct_binary(char * operand)
{
    char * temp_operand = strdup(operand);
    char * label = strtok(temp_operand, ".");
    char * index = strtok(NULL, ".");

    char * temp_MW = built_temp_str(label);
    temp_MW = string_append(temp_MW, SPLIT_MW);
    temp_MW = string_append(temp_MW, return_struct_index_binary(index));
    return temp_MW;
}   