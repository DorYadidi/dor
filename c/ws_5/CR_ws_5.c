/*******************************************************************************
*WS 5 - logger by chain of responsibilty.									   *							
* when iser typing a strin - the function adding a string to a file. 		   *
*There are few exceptions for spesific strings: 							   *     
*When typing "-exit" - to exit the program.	  	   						 	   *
*When typing "-remove" - the file is been deleted.							   *
*When the start of the string contain "<" - the string will be add to the start*
*of the file.									                               *
*The string is been comperd to a knowen string and base on that know which     *
*Function action to be executed.											   *
*Parameters:																   *
* file_name   : the name of the file we work with.							   *
* file        : pointer to the file_name.									   *
* input       : the input string. 											   *
* error_check : indicator for errors. 	 									   *
* error_check2: indicator for errors. 									       *
* x			  : represent the current char in a file.						   *
* buffer	  : new name file.												   *
* buffer_ptr  : pointer to the buffer file.									   *
* array_buffer: buffer for writing and reading. 							   *
*Return: success for success and in case f error, return the discription of the*
*error.  																	   *
*Created by: Chen Avisar , Creation date: 18.10.18   Update date: 21.10.18    */

#include <stdio.h> /* printf, rename*/
#include <stdlib.h> /*EXIT_SUCCES*/
#include <string.h> /* strcmp */
#define UNUSED(x) (void)(x)	 
#define ARRAY_SIZE 5

int Logger(char *file_name);
int Exit();
int Remove(char *input, char *file_name);
int Count(char *input, char *file_name);
int AppendToStart(char *input, char *file_name);	
int Append(char *input , char *file_name); 
int Compare(char *input, char *str);
int CompareStart(char *input, char *str);
int NoCompare(char *input, char *str);

enum return_value 
{	error, 
	success,
	faild_to_delete_the_file, 
	file_was_not_opend, 
	file_was_not_close, 
	file_failed_to_be_renamed,
	error_for_fputs,
	error_for_reading_the_file,
	error_for_reading_or_writing,
	flush_was_failed
}; 

typedef struct S_logger_input
{
	char *str;
	int (*comp_func)(char *input, char *str);
	int (*oper_func)(char *str, char *file_name);   
} logger_t;

int main(int argc, char **argv)
{
	UNUSED(argc); 
	Logger(argv[1]); 
	return EXIT_SUCCESS;
}			

int Logger(char *file_name)
{
	logger_t array[ARRAY_SIZE];
	char input[50];
	int i = 0;	
	
	array[0].str = "-exit\n";
	array[1].str = "-remove\n";
	array[2].str = "-count\n"; 
	array[3].str = "<"; 
	array[4].str = "-append\n";  
	array[0].comp_func = Compare;    
	array[1].comp_func = Compare; 
	array[2].comp_func = Compare; 
	array[3].comp_func = CompareStart;
	array[4].comp_func = NoCompare;
	array[0].oper_func = Exit;	
	array[1].oper_func = Remove;
	array[2].oper_func = Count;   
	array[3].oper_func = AppendToStart;
	array[4].oper_func = Append;
	
	while (1)
	{
		printf("please enter a string:\n");
		fgets(input, 100, stdin); 	
	
		for ( i=0 ; i<ARRAY_SIZE ; ++i)
		{	
			if ( 0 == (*array[i].comp_func)(input, array[i].str))
			{
				(*array[i].oper_func)(input, file_name);
				break;
			}	
		}
	}
	
	return 0;
}																			   	


int Compare(char *input, char *str)
{
	if ( 0 == strcmp(input, str))
	{
		return (0);
	}
	return (1); 
}


int CompareStart(char *input, char *str)
{
	if ( 0 == strncmp(input, str, 1))
	{
		return (0);
	}
	return (1); 
}


int NoCompare(char *input, char *str)
{
	UNUSED(input);
	UNUSED(str);		
	return (0); 
}

int Exit(char *input, char *str)
{
	UNUSED(input);
	UNUSED(str);	
	exit(0);
} 

int Remove(char *input, char *file_name)
{
	int error_check = 0;
	UNUSED(input); 
	
	error_check = remove(file_name);
	
	if (error_check == 0)
	{
		printf("file deleted succesfully\n");	
	} 
	else
	{
		return (faild_to_delete_the_file);
	}
	return success; 
}

int Count(char *input, char *file_name)
{
	int x = 0, count = 0;
	int error_check = 0;
	FILE *file = fopen(file_name, "r");
	UNUSED(input);
	
	if ( NULL == file)
	{
		return (file_was_not_opend);
	}
		
	while ( x != EOF) 
	{
		x = fgetc(file);
		
		if ( x == '\n') 
		{
			++count;
		}
	}
	
	error_check = fclose(file);
	 
	if (error_check != 0)
	{
		return (file_was_not_close);
	} 
		
	printf("The number of lines in the file is:%d\n",count);
	return success; 
}
																	   	
int Append(char *input, char *file_name )
{
	FILE *file = fopen(file_name,"a+");
	int error_check = 0;
	
	if ( NULL == file)
	{
		return (file_was_not_opend);  
	}
		fputs(input,file);
		error_check = fclose(file);
		
	if (error_check != 0)
	{
		return (file_was_not_close);
	} 
		
		return success; 
}	

int AppendToStart(char *input, char *file_name)
{
	char *buffer = "/tmp/buffer"; 
	FILE *buffer_ptr = fopen(buffer,"w+");  
	FILE *file = fopen(file_name, "r+");
	int error_check = 0;
	int error_check2 = 0;
	size_t read_count = 0;
	char array_buffer[4096];
	
	if ( (NULL == file) || (NULL == buffer_ptr))
	{
		return (file_was_not_opend);  
	}
		
	++input;
	error_check = fputs(input, buffer_ptr);
	
	if ( EOF == error_check)
	{
		return (error_for_fputs);	
	}
	
	read_count = fread(array_buffer, 1, 4096, file);
	
	if ( 0 == read_count)   /*fread failed*/
	{
		if (ferror(file))
		{
			return error_for_reading_the_file;
		}
	}
	
	while (read_count > 0)
	{
		error_check = fwrite(array_buffer, 1, read_count, buffer_ptr);
		read_count = fread(array_buffer, 1, 4096, file);

		if (( 0 == read_count) || (0 == error_check))   /*fread failed*/
		{	
			if (ferror(file) || (ferror(buffer_ptr)))
			{
				return error_for_reading_or_writing;
			}
		}
	}	
	
	
	error_check = fflush(file);

	if ( 0 != error_check)
	{
		return (flush_was_failed);
	}
	
	error_check = fclose(buffer_ptr);
	error_check2 = fclose(file);
	
	if ((error_check != 0 ) || (error_check2 != 0))
	{
		return (file_was_not_close);
	} 
	
	file = fopen(file_name, "w+");
	buffer_ptr = fopen(buffer, "r+");
	
	if ( (NULL == file) || (NULL == buffer_ptr))
	{
		return (file_was_not_opend);  
	}

	read_count = fread(array_buffer, 1, 4096, buffer_ptr);
	
	if ( 0 == read_count)   /*fread failed*/
	{
		if (ferror(buffer_ptr))  
		{
			return error_for_reading_the_file;
		}
	}
		
	while (read_count > 0)
	{
		error_check = fwrite(array_buffer, 1, read_count, file);
		read_count = fread(array_buffer, 1, 4096, buffer_ptr);
		
		if (( 0 == read_count) || (0 == error_check))   /*fread failed*/
		{	
			if (ferror(buffer_ptr) || (ferror(file)))
			{
				return error_for_reading_or_writing;
			}
		}
	}
		
	error_check = fflush(buffer_ptr); /*comment for me - need to investigate */
	
	if ( 0 != error_check)
	{
		return (flush_was_failed);
	}
		
	return success;
}

	
	
	
	
	
	
	
	
	
	
															   	
																			   	
