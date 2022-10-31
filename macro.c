#include "my_lib.h"
int is_macro_name_legal(char * macro_name)
{
	char * temp_macro_name = built_temp_str(macro_name);
	char * p= temp_macro_name;
	int macro_name_len = 0;

	/*find the index of the end of the name*/
	while((*p != SPACE)&&(*p != TAB)&&(*p != END_OF_STR))p++;
	macro_name_len = p - temp_macro_name;

		
	/*check if the macro name is <80*/
	if(macro_name_len > MAX_MACRO_NAME_LEN)
		return 0;
	
	/*check if there is extra text after the name*/
	remove_spacesANDtabsANDenter(temp_macro_name);
	p = temp_macro_name + macro_name_len;
	return *p == END_OF_STR;	

}

int if_macro_define(char *line, char * macro_names_list)
{
	char *p = line,* macro_name;
	char *index = strstr(line, MACRO);

	/*check if there is the word macro in line*/
	if(index == NULL)
		return 0;

	macro_name = find_macro_name_in_definition_with_spaces_in_the_end(line);
	/*check if its the first word*/

	while(p < index) { 	if((*p != SPACE)&&(*p != TAB))return 0; p++;}

	/*check if has space before the name of macro*/
	if((*(index+LEN_OF_THE_WORD_MACRO) != SPACE)&&(*(index+LEN_OF_THE_WORD_MACRO) != TAB))
		return 0;

	/*chaek if the macro name is ok, then we can remove the spaces from the end of the macro name*/
	if(!is_macro_name_legal(macro_name))return 0;

	remove_spacesANDtabsANDenter(macro_name);

	/*check if the macro already define*/
	if(strstr(macro_names_list,macro_name) != NULL)return 0;

	return 1;

}

char * find_macro_name_in_definition_with_spaces_in_the_end(char *line)
{
	char * temp_line = built_temp_str(line);
	char * macro_name = strstr(temp_line, "macro") + LEN_OF_THE_WORD_MACRO;

	/*find the index of the begin of the name*/
	while(((*macro_name == SPACE)||(*macro_name == TAB))&&(*macro_name!= END_OF_STR))macro_name++;
	return macro_name;
}

char * find_macro_name_not_in_definition_with_spaces_in_the_end(char *line)
{
	/*we add the word macro to the line, and use the function of decleration macro*/
	char  *temp = string_append(MACRO,line);
	return find_macro_name_in_definition_with_spaces_in_the_end(temp);
}

char * return_macro_name(char * line, int is_def)
{
	char * macro_name = NULL;
	if(is_def)
		macro_name = find_macro_name_in_definition_with_spaces_in_the_end(line);
	else
		macro_name = find_macro_name_not_in_definition_with_spaces_in_the_end(line);

	remove_spacesANDtabsANDenter(macro_name);
	return macro_name;
	
}
void printList(macro* m)
{
    while (m != NULL) {
        printf("the macro tadam: %s%s",m->mname,m->mcontent);
        m = m->next;
    }
}

void insert_macro(char *name,char *content, macro *head) {
	macro * new_macro = NULL;
	macro * temp_pointer = head;
	new_macro = (macro*) malloc(sizeof(macro));
	strcpy(new_macro->mname,name);
	strcpy(new_macro->mcontent,content);
	while (temp_pointer->next != NULL) {
        temp_pointer = temp_pointer->next;
    }
	 temp_pointer->next = new_macro;}

void insert_head(char *name,char *content, macro *head)
{
	strcpy(head->mname,name);
    strcpy(head->mcontent,content);
    head->next = NULL;
}

int if_macro_name_in_list(char *macro_names_list,char *line)
{
	char * macro_name, *index;
	macro_name = find_macro_name_not_in_definition_with_spaces_in_the_end(line);
	if(is_macro_name_legal(macro_name)) remove_spacesANDtabsANDenter(macro_name);
	index = strstr(macro_names_list, macro_name); 

	/*if the name not in name list, strstr return null*/
	if(index == NULL) return 0;
	return 1;
}

char * return_macro_content(char *macro_name,macro *head)
{
	macro * temp_pointer = head;
   	while (temp_pointer != NULL)
	 {
	if(strstr(temp_pointer->mname, macro_name) != NULL)
		return temp_pointer->mcontent;
	temp_pointer = temp_pointer->next;
   	 }
	return NULL;
}
