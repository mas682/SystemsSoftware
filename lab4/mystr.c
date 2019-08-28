/************************************************************************
*mystrings								*
*@author: Matt Stropkey                                                 *
*@username: mas682							*
*This program takes a filename fromt he command line and reads the bytes*
*of the file, looking for strings of printable characters(ASCII 32-126)	*
*To run the program, type mystrings FILENAME				*
*Whenever a string of 4 consecutive printable characters is found it 	*
*will be printed out							*
*									*
*									*
*									*
************************************************************************/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *file_name;
FILE * in_file;

//string copy function
void my_strcpy(char *dest, char *src)
{
	while(*dest++ = *src++);
}

//string concatenation
void my_strcat(char *dest, char *src)
{
	int len = 0;
	int srclen = 0;
	char *temp;
	while(*dest++ != '\0');
	len = strlen(dest);
	srclen = strlen(src);
	printf("%d\n", len);
	temp = malloc(len+srclen);
	while(*dest != '\0')
	{
		*temp++ = *dest++;
	}
	while(1)
	{
		if(*src == '\0')
		{
                        *dest = *src;
			break;
		}
		*temp++ = *src++;

	}
	printf("Printing temp: %s\n", temp);
	dest = temp;		

		
}

//function used to read file
void read()
{
	int read_size = 0;						//used to keep track of num of characters read
	char current_character[1];					//used to hold current character
	int string_len = 0;						//the lenght of current string
	char *current_string;						//pointer for a string array
		
	while(!feof(in_file))						//do this while not at end of file
	{		
		string_len = 0;						//reset string length
		do
		{
			fread(current_character, 1, sizeof(current_character), in_file);	//read in one byte at a time
			read_size++;								//increment number of bytes read
			if((int)current_character[0] >= 32 && (int)current_character[0] <= 126)		//if a valid character, increment string len
			{
				string_len++;			//if character valid, increment string length
			}
			//printf("Current character: %c\n", current_character[0]);		//for testing
			//printf("Character value: %d\n",(int) current_character[0]);		//for testing
		}while((int)current_character[0] >= 32 && (int)current_character[0] <= 126 && !feof(in_file));
		if(string_len >= 4)
		{	
			string_len++;					//increase by 1 to add nul terminator
			//printf("String len: %d", string_len);		//for testing
			current_string = malloc(string_len);		//create a char array the size of the string
			strcpy(current_string, "");			//set the string to nothing
			fseek(in_file, -string_len, SEEK_CUR);		//go to starting position of string in file
			fread(current_string, 1, string_len-1, in_file);	//read the string from the file into the char array
			current_string[string_len-1] = '\0';		//null terminate the string
			printf("%s\n", current_string);	//output the string
			free(current_string);				//free the memory

		}
	}//end of while loop
}//end of read method

int main(int argc, char *argv[])
{	
	int close;
	file_name = argv[1];			//file_name = first argument
	in_file = fopen(file_name, "rb");	//try to open the file as read only binary
	if(in_file == NULL)			//if the file does not exist, crash program
	{
		printf("Error: Unable to open file \'%s\'\n", file_name);
	}
	else
	{
		read();
		close = fclose(in_file);
		if(close)
		{
			printf("Unable to close the file\n");
		}
	}
	return 0;
}
