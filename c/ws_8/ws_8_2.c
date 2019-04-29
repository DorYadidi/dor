#include <stdio.h> 
#include "ws_8.c"


#define sizeof_var( var ) ((size_t)(&(var)+1)-(size_t)(&(var))) /*sizeof var*/
#define sizeof_type( type ) ((size_t)((type*)1 + 1)-(size_t)((type*)1)) /*sizeof type*/

typedef struct s_DateOfBirth 
{
	size_t day;
	size_t month;
	size_t year;

}DateOfBirth_type;


typedef struct s_Contact
{
	char f_name[50];
	char l_name[50];
	DateOfBirth_type dob;
	size_t ID;

}Contact_type;

Contact_type *WriteAndRead(Contact_type *p_contact, int size_arry)
{

	Contact_type *new_contact = (Contact_type *)malloc(size_arry*sizeof(Contact_type));

	FILE *file= fopen("/home/rd58/soko.txt", "wb");
	if (NULL == file) 
	{
		return NULL;
	}
	
    	fwrite(p_contact, sizeof(Contact_type), size_arry, file);
	fclose(file);
	
	file= fopen("/home/rd58/soko.txt", "rb");
	if (NULL == file) 
	{
		return NULL;
	}
	
	fread(new_contact, sizeof(Contact_type), size_arry, file);
	
	fclose(file);
	return new_contact;							
}


int main()
{
/*	test *p = (test)malloc(3*sizeof(test));
	p[1].void* = 
	*/
	int i = 0;
	Contact_type *p_contact = (Contact_type *)malloc(2*sizeof(Contact_type));
	Contact_type *new_contact = NULL;
	if (0 == p_contact)
	{
		return 0;
	}
	
	strcpy(p_contact[0].f_name, "itamar");
	strcpy(p_contact[0].l_name, "yazizir");
	p_contact[0].dob.day = 1;
	p_contact[0].dob.month = 4;
	p_contact[0].dob.day = 45;
	p_contact[0].ID = 1;
	
	
	strcpy(p_contact[1].f_name, "itzozoar");
	strcpy(p_contact[1].l_name, "yazizizpzpr");
	p_contact[1].dob.day = 34;
	p_contact[1].dob.month = 4;
	p_contact[1].dob.day = 4;
	p_contact[1].ID = 2;

	new_contact = WriteAndRead(p_contact, 2);
	printf("%s\n %s\n", new_contact[0].f_name, new_contact[0].l_name);
	printf("%s\n %s\n", new_contact[1].f_name, new_contact[1].l_name);

	free(p_contact);
	free(new_contact);
	

	printf ("size of var i: %ld\n", sizeof_var( i ));
	printf ("size of char Contact_type: %ld\n", sizeof_type( Contact_type ));
	printf ("size of char: %ld\n", sizeof_type( char ));
	
	
	return 0;
}
