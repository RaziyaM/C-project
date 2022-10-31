#include "my_lib.h"

char * return_filePath_no_ex(char *str, char *file_extention)
{
    int i;
    int str_len = strlen(str),ex_len = strlen(file_extention);
	int size = str_len - ex_len + 1;
	char *temp_str = calloc(size,sizeof(char));
    for(i=0; i< strlen(str)-3; i++)
        temp_str[i] = str[i];
    return temp_str;
}

char * add_filePath_ex(char * file_path, char * extention)
{
    char * temp = string_append(file_path,extention);
    return temp;
}

FILE * open_file(char * file_path, char * open_method)
{
    FILE * fptr;
    fptr = fopen(file_path,open_method);
    
	if(fptr == NULL && equal_str(open_method, "r")) 
	{
		printf("Error! cant open %s file. is it exist?", file_path);
	}	
    return fptr;
}