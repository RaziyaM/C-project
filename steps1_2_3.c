#include "my_lib.h"
int step1_speard_macro(char * file_path)
{
    FILE *fptrR,*fptrW;
	int is_macro_defined = 0;
	char *macro_name,*macro_names_list,*macro_content;
    macro * head;
    char * read_file_path,*write_file_path;

	char *line;
    size_t len = 0;


    macro_names_list = EMPTY_STR;

    head = (macro*) malloc(sizeof(macro));
    if (head == NULL) /*RAZIIIIIIIIII*/{printf("malloc ERROR");return 0;}

    write_file_path = add_filePath_ex(file_path,FILE_EX_txt);
    read_file_path = add_filePath_ex(file_path, FILE_EX_as);

    if((fptrR = open_file(read_file_path,"r")) == NULL) return 0;
     /*RAZI!!! you need to print ERRORRRR!!!*/
    fptrW = open_file(write_file_path,"w");

	while (getline(&line, &len, fptrR) != -1)
	{
        /*if there is definition of macro in the line we need to add the macro to the list*/
		if(if_macro_define(line,macro_names_list))
		{	
			macro_name = return_macro_name(line,YES_DEF);
            macro_names_list = string_append(string_append(macro_names_list, macro_name), SEPARATION); /*the names separated by '.' in the list*/

			getline(&line, &len, fptrR);
			macro_content = EMPTY_STR;

            /*we add the macro content until there is endofmacro line*/
			while(!strstr(line, END_OF_MACRO))
            {
				macro_content = string_append(macro_content,line);
				getline(&line, &len, fptrR);
            }

            
			if(!is_macro_defined) /*if no macro defined yet, we initial the head*/
			{
                insert_head(macro_name,macro_content, head);
                is_macro_defined++;
			}

			else insert_macro(macro_name,macro_content, head);
		
		}

		/*if there is name of macro, we need to insert the macro content*/
		else if(is_macro_defined && if_macro_name_in_list(macro_names_list,line)) 
        
			{
			macro_content = return_macro_content(return_macro_name(line,NO_DEF),head);
			fprintf(fptrW,"%s",macro_content);
			}
        /*if its not definition of macro or macro name, we just copy the line*/
		else
			fprintf(fptrW,"%s",line);
	}

	fclose(fptrR);
	fclose(fptrW);
    /*printf("name=%s", macro_names_list);
    printList(head);*/
    return 1;
}

void step2_built_symbol_table(char * file_name)
{
    FILE *fptrR;
    char * file_path = add_filePath_ex(file_name, FILE_EX_txt);
    int error_index,label_legal = 1,line_counter =1,expression=0;

    char *line;
    size_t len = 0;

    char * DC_head = "",*IC_head = "",* label_table = "", *entry_table = "", *extern_table = ""; 
    int dc = 100, ic = 0;

    fptrR = open_file(file_path,"r");/*we dont need to check if there is file like that, we did it in step 1*/

    while (getline(&line, &len, fptrR) != -1)
    {
        if(!emptyORcomment(line)) 
        {  
                if(find_label(line))
                {
                    if((error_index = check_label_legal(line, label_table)) != OK)
                    {
                        label_legal = 0;
                        print_ERORR(error_index, line_counter);
                    } 
                    else
                    {
                        line = strtok(line, ":");
                        add_label_to_table(&label_table, line,dc+ic);
                        line = strtok(NULL, ":");
                    }

                }

                if(label_legal)
                {
                    expression = is_EMPTY_COMMENT_DIRECTIVE_OPERATION(line);
                    switch (expression)
                    {
                        case EMPTY_CASE:
                        break;

                        case COMMENT_CASE:
                        break;

                        case DIRECTIVE_CASE:
                        error_index = built_machine_code(line, DIRECTIVE_CASE, &dc,label_table, line_counter, &DC_head);
                        break;

                        case OPERATION_CASE:
                        error_index = built_machine_code(line, OPERATION_CASE, &ic,label_table, line_counter,&IC_head);
                        break;
                        
                        case ENTERY_CASE:
                        add_ent_to_table(&entry_table, line);
                        break;
                        case EXTERN_CASE:

                        add_ex_to_table(&extern_table, line);
                        break;

                        default:
                        error_index =Unrecognized_opcode_name;
                        print_ERORR(error_index, line_counter);
                        break;

                    }
                
                }
            

    }

    line_counter++;
    label_legal = 1;
    }

    if(error_index!= OK) step3_built_machine_code(DC_head, IC_head,label_table, extern_table, entry_table,file_name);

}
void print_data_to_file(char* file_path, char * data_array, char * label_table, char * extern_table, int * counter, char ** extern_file)
{
    char * token = strtok(data_array, "|");
    char * index_1, *index_2;
    char * counter_binary, *counter_1, *counter_2;      
    char * temp_label_binary=EMPTY_STR;
    char *temp_token;
    int temp_label_value=0, ex_flag =0;

    FILE * fptr;
    fptr = open_file(file_path, "a");
    while(token != NULL)
        {
            temp_token = built_temp_str(token);
            if(*temp_token == '0' || *temp_token == '1') temp_label_binary = built_temp_str(token);
            
            else 
            {
                temp_token = built_temp_str(token);
                if(strstr(extern_table, temp_token)!=NULL)
                    {
                        temp_label_binary = EXTERNAL_LABEL;
                        ex_flag = 1;
                    }
                else  
                    {
                        temp_label_value = return_label_value(label_table, temp_token);
                        temp_label_binary = int_to_bin(temp_label_value,8);
                        temp_label_binary = string_append(temp_label_binary, R);
                    }
                
            }
            index_1 = copy_str_until_index(temp_label_binary, 4);
            index_2 = temp_label_binary + 5;

            counter_binary = int_to_bin(*counter,10);
            counter_1 = copy_str_until_index(counter_binary, 4);
            counter_2 = counter_binary + 5;
            fprintf(fptr, "%s  %s, %s  %s\n",convert_my_base32(counter_1),convert_my_base32(counter_2), convert_my_base32(index_1),convert_my_base32(index_2));

            if(ex_flag)
            {
                *extern_file = string_append(*extern_file, temp_token);
                *extern_file = string_append(*extern_file, " ");
                *extern_file = string_append(*extern_file,convert_my_base32(counter_1));
                *extern_file = string_append(*extern_file,convert_my_base32(counter_2));
                *extern_file = string_append(*extern_file, "\n");
            }
            token = strtok(NULL, "|");
            (*counter)++;
            ex_flag = 0;
        }
        fclose(fptr);
}
void step3_built_machine_code(char * dc_head, char * ic_head, char * label_table, char * extern_table, char * entry_table,char * file_name)
{
    int counter = 100;
    char * ex_file_content = EMPTY_STR;
    char * token,*temp_entry_table, *bin_word, *index1, *index2;
    char * file_path = add_filePath_ex(file_name, FILE_EX_ob);
    FILE * fptr;
    print_data_to_file(file_path,ic_head, label_table,extern_table, &counter, &ex_file_content); 
    print_data_to_file(file_path,dc_head, label_table,extern_table, &counter,&ex_file_content); 
    if(!equal_str(extern_table,EMPTY_STR)) 
    {
            file_path = add_filePath_ex(file_name, FILE_EX_ex);
            fptr = open_file(file_path, "w");
            fprintf(fptr,"%s",ex_file_content);
            fclose(fptr);
    }
    if(!equal_str(extern_table,EMPTY_STR)) 
    {  
        file_path = add_filePath_ex(file_name, FILE_EX_ent);
        fptr = open_file(file_path, "w");
           
        temp_entry_table = strdup(entry_table);
        token = strtok(temp_entry_table, SPLITE_TABLE_1);
        while (token!=NULL)
        {
            bin_word = int_to_bin(return_label_value( label_table,token),10);
            index1 = copy_str_until_index(bin_word, 4);
            index2 = bin_word + 5;
            fprintf(fptr,"%s %s %s\n",token,convert_my_base32(index1),convert_my_base32(index2));
            token = strtok(NULL, SPLITE_TABLE_1);
        }
         fclose(fptr);
    }


}

