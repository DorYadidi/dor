/*Dor yadidi ws_5*/

#include <stdio.h> /*fclose, fopen, fgets, fseek*/
#include <string.h> /*strcmp*/

struct s_LoggerInput
{
	char *str;
	int (*cmp_pointer)();
	int (*opr_pointer)(char *);
};
typedef struct s_LoggerInput s_Check;


	
int Remove (char *file_name);
/*****************************************************************
 *if the user enter the string "-remove" then the file deleted.  *
 *Paramters: file_name - the file name                           *
 *Return: if the file deleted successfully return 0 (exitreturn) *
 *        and exit the program. if there is fail return 1.       *
 ****************************************************************/
 
int Exit (char *file_name);
/*****************************************************************
 *if the user enter the string "-exit" the program should close  *
 *Paramters: file_name - the file name                           *
 *Return: return 0 (exitreturn)                                  *
 ****************************************************************/

int Count (char *file_name);
/*****************************************************************
 *if the user enter the string "-count" print the number of lines*
 *in the file.                                                   *
 *Paramters: file_name - the file name                           *
 *Return: return 1                                               *
 ****************************************************************/

int Insert(char *file_name, char *str);
/*****************************************************************
 *if user string start with '<' then the string sould added to   *
 *the begins of the file witout the '<'                          *
 *Paramters: file_name - the file name,  str - the user string   *
 *Return: return 1 if successfully and 0 if fail                 *
 ****************************************************************/

int Append(char *file_name, char *str);
/*****************************************************************
 *user string should add in the end of the file                  *
 *Paramters: file_name - the file name,  str - the user string   *
 *Return: return 1 if successfully and 0 if fail                 *
 ****************************************************************/

int CmpInput(char *str_user, s_Check *inputs, int size_arr, char *file_name);
/***************************************************************************
 *function that comper between user string and the operaion                *
 *Paramters: str_user - the user string, inputs- the operaion,             *
 *size_arr - the size arry, file_name - the file name                      *
 *Return: the value from the functions                                     *
***************************************************************************/

enum Status

{
	exitreturn,
	keepget,
	error_fopen		
};

int main(int argc, char **argv)
{
	char str_user[80];
	int check = 1;
	FILE *fp = NULL;
	
	s_Check inputs[3];
	inputs[0].str = "-remove\n";
	inputs[0].opr_pointer = &Remove;
	inputs[1].str = "-count\n";
	inputs[1].opr_pointer = &Count;
	inputs[2].str = "-exit\n";
	inputs[2].opr_pointer = &Exit;
	
	if (1 == argc)
	{
		printf("Enter a file name\n");
		return exitreturn;
	
	}
		
	fp = fopen(argv[1] , "a+");
	if (0 == fp)
	{
		printf("Error: could not open file!\n");
		return exitreturn;
	}
	
	fclose(fp);
	
	while (check != exitreturn)
	{
		printf("Enter your text:\n");
		fgets(str_user, 80, stdin);
		check = CmpInput(str_user, inputs, 3, argv[1]);
		if (exitreturn == check)
		{
			break;
		}
		
		else if (error_fopen == check)
		{
			printf("Error: could not open file!\n");
		}
	}

	return exitreturn;
}

int CmpInput(char *str_user, s_Check *inputs, int size_arr, char *file_name)
{
	int i=0;
	int ret=0;
	while (i < size_arr)
	{

		if (0 == strcmp(str_user, inputs[i].str))
		{
			ret = inputs[i].opr_pointer(file_name);		
			return ret;							
		}
		
		++i;
	}
	
	if ('<' == *str_user)
	{
		ret = Insert(file_name, str_user);
		return ret;
	
	}
	else
	{
		ret = Append(file_name, str_user);
		return ret;
	}

} 


int Remove(char *file_name)
{
	if(0 == remove(file_name))
	{
		printf("File deleted successfully\n");
		return exitreturn;
	}    
	else
	{
		printf("Error: unable to delete the file\n");
		return keepget;
	}
   
}

int Exit(char *file_name)
{
	printf("File %s exit \n", file_name);
	return exitreturn;

}


int Count(char *file_name)
{
	int ch=0, lines=0;
	FILE *fp = fopen(file_name , "r");
	if (0 == fp)
	{
		return error_fopen;
	}
	
	while(0 == feof(fp))
	{
 		 ch = fgetc(fp);
 		 if('\n' == ch)
 		{
    		++lines;
  		}
	}
	
	fclose(fp);
	printf("The number of lines in the file is: %d\n", lines);	
	return keepget;

}


int Append(char *file_name, char *str)
{

	FILE *fp = fopen(file_name , "a+");	
	if (0 == fp)
	{
		return error_fopen;
	}
		
	if(fprintf(fp,"%s", str) < 0)
	{
		printf("Error: unable to print in the file\n");
		fclose(fp);
		return keepget;	
	}			
	else
	{
		printf("Write to the end of the file successfully\n");
		fclose(fp);
		return keepget;
	}					
}
		
int Insert(char *file_name, char *str)
{

	char buffer[4096];
	FILE *new_fp = NULL;
	size_t last_chunk_size = 0;
	char *filenametmp = "/tmp/help";
	FILE *fp = fopen(file_name , "r+");
	FILE *fp_help = fopen(filenametmp ,"w+");
	if (0 == fp_help)
	{
		return error_fopen;
	}
	

	if (0 == fp)
	{
		return error_fopen;
	}
		
	++str; /*witout the '<'*/
	
	if(fprintf(fp_help ,"%s", str) < 0)
	{
		printf("Error: unable to print in the file\n");
		fclose(fp);
		fclose(fp_help);
		return keepget;
	}			
	

	while(0 == feof(fp))
	{
		last_chunk_size = fread(buffer ,1 ,4096, fp);
		fwrite(buffer, 1, last_chunk_size, fp_help);
	}
	
	fclose(fp);
	fseek(fp_help, 0L , SEEK_SET);
	
	new_fp = fopen(file_name, "w+");
	if (0 == new_fp)
	{
		fclose(fp_help);
		return error_fopen;
	}
	
	while (0 == feof(fp_help))
	{
		last_chunk_size = fread(buffer, 1, 4096, fp_help);
		fwrite(buffer, 1, last_chunk_size, new_fp);
	}	
	
	fclose(new_fp);	
	fclose(fp_help);	
	
	printf("Write to the begins of the file successfully\n");
	return keepget;

}

