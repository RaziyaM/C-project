#include "my_lib.h"
void remove_chars_fromSTR(char * string, char ch)
{
    int i;
    int non_space_count = 0;

    if(string != NULL)
    {
        for (i = 0; string[i] != '\0'; i++)
        {
            if (string[i] != ch)
            {
                string[non_space_count] = string[i];
                non_space_count++;
            }    
        }

        string[non_space_count] = '\0';
    }
}

void remove_white_spaces(char * s)
{
    char* d = s;
    do while(isspace(*s)) s++; while((*d++ = *s++));
}

int is_str_empty(char * str)
{
    remove_white_spaces(str);
    return equal_str(str, EMPTY_STR);
}

void remove_spacesANDtabsANDenter(char * str)
{
    remove_chars_fromSTR(str, SPACE);
    remove_chars_fromSTR(str, TAB);
    remove_chars_fromSTR(str, ENTER);

}

char * string_append(char *s1, char *s2)
{
	int s1_len = strlen(s1),s2_len = strlen(s2);
	int size = s1_len + s2_len + 1;
	char *s = calloc(size,sizeof(char));
	int i;
	for (i=0; i<s1_len; i++)
		s[i] = s1[i];
	for (i=0; i<s2_len; i++)
		s[s1_len +i] = s2[i];
	
	return s;
}

char * built_temp_str(char * str)
{
    char * temp_str = NULL;
    if(str == NULL)
        return NULL;

    temp_str = string_append(str, EMPTY_STR);
    return temp_str;
}

int equal_str(char * str1, char * str2)


{
    if (strcmp(str1, str2) != 0) /*strcmp return 0 when 2 string equal*/
        return 0;
    return 1;
}

int is_str_is_digit(char * str)
{
    int len,i,flag=1;

    if(is_space_in_middle(str)) return 0;
    remove_white_spaces(str);
    len = strlen(str);

    for(i = 0; i<len; i++)
    {
        if(!isdigit(*(str+i)))
            flag = 0;
    }

    return flag;
}
int is_str_is_num(char * str)
{
    /*same as is_str_is_digit, but this also check if the first character is - or + */
    return((*str == PLUS || *str == MINUS)&&(is_str_is_digit(++str)));
}
void pass_white_spaces_from_the_begin(char ** str)
{
    while(isspace(**str) && **str != END_OF_STR) (*str)++;
}

char * copy_str_until_index(char * str, int index)

{
    int str_len = index+1;
    int i;
    char *s = calloc(str_len,sizeof(char));
    for(i=0; i<=index; i++)
    {
        s[i] = str[i];
    }
    s[i+1] = END_OF_STR;
    return s;

}

int is_only_space_until_the_end(char * line)
{
       while(*line!= END_OF_STR)
    {
        if(!isspace(*line))
            return 1;
        line++;
    }
    return 0;
}
int is_space_in_middle(char * line)
{
    if(line == NULL)
    return 0;

    /*we pass all the spaces from the begin*/
    while(isspace(*line) && *line != END_OF_STR) line++;

    /*we pass the non spaces*/
    while(!isspace(*line) && *line != END_OF_STR) line++;


    /*we check if there is something which isnt space until the end of str*/
    return is_only_space_until_the_end(line);
}

void str_reverse(char * str)
{
    int i, len, temp;  
    len = strlen(str);  
      
  
    for (i = 0; i < len/2; i++)  
    {  

        temp = str[i];  
        str[i] = str[len - i - 1];  
        str[len - i - 1] = temp;  
    }  
}