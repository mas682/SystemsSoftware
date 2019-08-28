/*****************************************************
*id3tagED					     *
*@author: Matt Stropkey			             *
*This program allows you to print, modify, or add to *
*a ID3 tag					     *
*To run the program, type id3tagEd FILENAME or type  *
*id3tagEd FILENAME -FIELD VALUE		             *
*****************************************************/


#include <string.h>
#include <stdio.h>
char *file_name;
FILE * in_file;

//structure used when reading in data from file
	struct id3tag {
               char header[3];
               char song[30];
               char artist[30];
               char album[30];
               char year[4];
               char comment[28];
               char zero[1];
               char track;
               char genre;
        }tag;
//structure used when printing out data from file to add null terminator to strings
	 struct id3tag_terminated {
               char tag[4];
               char song[31];
               char artist[31];
               char album[31];
               char year[5];
               char comment[29];
               char zero[2];
               char track;
               char genre;
        }string;
//function terminate used to add a null terminator to a string if no present
	void terminate(char *temp, int len)
	{	
		if(temp[len] != '\0')
		{
			temp[len] = '\0';		//set the last character of a string to the null terminator 
		}
	}
//funtion to just read file
//returns 1 if the tag does not exist, 0 if it does
	int read()
	{
		int pos;		//used to get position to start reading at
		int read_size;		//used to see if correct number of bytes read
		int i = 0;		//used for the for loop to see if TAG at header
		int no_tag = 0; 	//used as a boolean
		char tag_check[4] = "TAG";
	        if(in_file == NULL)	//if file does not exist, crash program
       	        {
               		 printf("Error: Unable to open file \' %s\'\n", file_name);
               		 //exit(EXIT_FAILURE);              //CRASH THE PROGRAM OR MAKE A NEW FILE 
       	        }
		else
		{
       	        pos = fseek(in_file, -128, SEEK_END);           //go to last 128 bytes $

       	        read_size = fread((char *)&tag, 1, sizeof(tag), in_file);  	//copy 128 bytes to tag struct

	        if(read_size != sizeof(tag))                    //if the number of bytes does not equal
       	        {                                               //the size of the tag, crash the program
               		 printf("TAG NOT CORRECTLY READ\n");
               	//	 printf("read_size = %d\n", read_size);
               		 //exit(EXIT_FAILURE);                              //CRASH THE PROGRAM?
       		}
		for(i = 0; i < sizeof(tag.header); i++)		//used to see if there is a tag in the file
		{
			if(tag.header[i] != tag_check[i])
			{
				//printf("Not a tag\n");
				no_tag = 1;			//if one of the TAG characters do not match,
								//set no tag to true
				break;				//break out of the for loop
			}		
		}
		if(!no_tag)				//if there is a tag do this
		{
       	        	*strncpy(string.tag, tag.header, 3);            //copy the string from 
       	        	terminate(string.tag, 4);
       	        	*strncpy(string.song, tag.song, 30);            //copy the string from 
       	        	terminate(string.song, 31);
       	        	*strncpy(string.artist, tag.artist, 30);        //copy the string from 
                	terminate(string.artist, 31);
       	        	*strncpy(string.album, tag.album, 30);          //copy the string from 
       	        	terminate(string.album, 31);
       	        	*strncpy(string.year, tag.year, 4);             //copy the string from 
        		terminate(string.year, 5);
                	*strncpy(string.comment, tag.comment, 28);      //copy the string from 
                	terminate(string.comment, 28);
                	*strncpy(string.zero, tag.zero, 1);             //copy the string from 
        		terminate(string.zero, 2);
        		string.track = tag.track;
			string.genre = tag.genre;
		}
		}//end else
		return no_tag;	//return true or false if tag is there or not
	}//end of f read function

//this function is used to create a new tag if one does not exist
//by setting the struct string and struct tag fields
//the fields are either set to a empty string or a 0
	void create_tag()
	{
		*strncpy(string.tag, "TAG", 4);            //copy the string
                *strncpy(tag.header, "TAG", 3);
	

                *strncpy(string.song, "", 31);            //copy the string
                *strncpy(tag.song, "", 30);


                *strncpy(string.artist, "", 31);        //copy the string
                *strncpy(tag.artist, "", 30);

                *strncpy(string.album, "", 31);          //copy the string
                *strncpy(tag.album, "", 30);

                *strncpy(string.year, "", 5);             //copy the string
                *strncpy(tag.year, "", 4);

                *strncpy(string.comment, "", 29);      //copy the string
                *strncpy(tag.comment, "", 28);

                *strncpy(string.zero, "", 2);             //copy the string
                *strncpy(tag.zero, "", 1);

		string.track = 0;
		tag.track = 0;

		string.genre = 0;
		tag.genre = 0;		

	}//end of create_tag function

//this funtion is used to simply print out the tag
	void print_output()
	{
		printf("Header: %s\n",string.tag);
                printf("Song title: %s\n",string.song);
                printf("Artist: %s\n",string.artist);
                printf("Album: %s\n",string.album);
                printf("Year: %s\n",string.year);
                printf("Comment: %s\n",string.comment);
                printf("Zero seperator: %s\n",string.zero);
                printf("Track: %d\n",string.track);
                printf("Genre: %c\n",string.genre);
	}
	

//this function is used to change the tag values given input from the command line
//this fuction returns the offset to where the command line array should currently be
//array_len is the number of characters the current field can hold
//a is the array to place the arguments into
//args is the command line arguments
//arg_size is the number of arguments left in the command line array
	int get_value(int array_len, char a[], char* args[], int* arg_size)
	{
        	int string_length = 0;		//used to hold the lenght of the string given the current argument
        	int previouslen;		//holds the previous length value before new value updated
        	int copylen;			//used if the current argument takes you over the max string lenght
       		int offset = 0;			//used as the return value
		int track_boolean = 0;

		if(strcmp(args[1],"-track") == 0)
		{
			track_boolean = 1;
		}
		         
		args++;				//increment current argumen
		offset++;			//increment offset
         	while(args[1][0] != '-' && *arg_size >= 2)
         	{
         		//printf("argc: %d\n",* arg_size);	//for testing
                	previouslen = string_length;		//update previous length
                	string_length += strlen(args[1]);	//update current length with next arg
                	if(string_length > array_len && previouslen <= array_len)		//if over max length
               		{
                		copylen = array_len - previouslen;	//only copy this many characters
                        	char cpytest[copylen];			//create an array of copylen size
                        	strncpy(cpytest, args[1], copylen);	//copy current arg to the array
                        	strncat(a, cpytest, array_len);		//copy array to the field array
                	}
                	else if(!track_boolean && previouslen <= array_len)					//not over limit so just copy the arg
                	{
                  		//printf("string_length: %d\n", string_length);
                        	strncat(a, args[1], array_len);		//copy the current arg to the field array
                	}
			if(track_boolean)				//only do this if you are changing the track number
			{
				*a = (char)atoi(args[1]);		//convert a string to a char
				//printf("Value: %d\n",*a); 		//for testing
			}
                	if(*arg_size == 2)		//if size ==2, no more arguments to read
                	{
  				(*arg_size)--;
                        	break;			//break out of while loop
                	}
                	args++;		//increment command line array
			offset++;	//increment return value
               		(*arg_size)--;	//decrement number of args left
                	if(args[1][0] != '-' && string_length < array_len && *arg_size >= 2)	//used to add a space to the field array if more arguments left for this field
                	{
                        	strncat((char *)a, " ", 30);	//add a space to the array
                        	string_length += 1;		//increase the length
                	}
              
	
          	}//end of while loop
	 	//printf("offset returned: %d\n", offset);	//for testing
         	//printf("%string placed in new value:s\n", a);	//for testing
		return offset;
	}//end of get_value function
int main(int argc, char *argv[])
{	
	int close;
	//printf("%d\n", argc); 		//for testing
	int no_tag;
	file_name = argv[1];			//file_name = first argument
	argv++;					//increment where you are in command line array
	in_file = fopen(file_name, "r+b");	//try to open the file as read and write binary
	if(argc == 2)				//if only 2 arguments, just read the file
	{
		no_tag = read();		//try to get the field values
		if(!no_tag)
		{
			print_output();		//if there is a tag, print it ou
		}
		else
		{
			printf("No tag exists for this file\n");
		}
		
	}
	else if(argc > 2){			//if there are more than 2 arguments, update file
		
		int pos;			//used to go to right spot in file when updating
		argc--;				//decrement number of arguments
		no_tag = read();
		if(no_tag)			//if no tag exists, create one for the file
		{
			create_tag();
		}
		while((argc > 1) && (argv[1][0] == '-'))	//at least 2 arguments and the current one begins with a '-'
		{	
			int offset;				//offset of current position in command line array
			if(strcmp(argv[1],"-title") == 0)
			{	
				argc--;							//decrease number of arguments
				char temp[30] = "";					//allocate a 30 char sized array
				offset = get_value(30, temp, argv, &argc);		//call get value function
				//printf("%d\n", offset);				//for testing
				argv += offset;						//add the offset to the array upon return
				//printf("%s\n", temp);					//for testing: make sure right char[] returned
				strncpy(tag.song, temp, sizeof(tag.song));		//copy the arguments to the tag field
				//printf("after if the next arg is: %s\n", argv[1]);	//for testing
			}
		
			else if(strcmp(argv[1],"-artist") == 0)
			{
				argc--;							//decrease number of arguments
				char temp[30] = "";					//allocate a 30 char sized array
                                offset = get_value(30, temp, argv, &argc);		//call get value function
				argv += offset;						//add the offset to the array upon return
                                //printf("%s\n", temp);					//for testing: make sure right char[] returned
                                strncpy(tag.artist, temp, sizeof(tag.artist));		//copy the arguments to the tag field
			}
			else if(strcmp(argv[1],"-album") == 0)
			{
				argc--;							//decrease the number of arguments
                                char temp[30] = "";					//allocate a 30 char sized array
                                offset = get_value(30, temp, argv, &argc);		//call the get value function
                                argv += offset;						//add the offset to the array upon return
                                //printf("%s\n", temp);					//for testing: make sure right char[] returned		
                                strncpy(tag.album, temp, sizeof(tag.album));		//copy the arguments to the tag field
      				//printf("next arg: %s", argv[1]);   			//for testing
			}
			else if(strcmp(argv[1],"-year") == 0)
                	{
                        	argc--;							//decrease the number of arguments
                                char temp[4] = "";					//allocate a 4 char sized array
                                offset = get_value(4, temp, argv, &argc);		//call the get value function
                                argv += offset;						//add the offset to the array upon return
                                //printf("%s\n", temp);					//for testing: make sure right char[] returned
                                strncpy(tag.year, temp, sizeof(tag.year));		//copy the arguments to the tag field
				//printf("next arg: %s", argv[1]);			//for testing
                	}
			else if(strcmp(argv[1],"-comment") == 0)
                	{
                        	argc--;							//decrease the number of arguments
                                char temp[28] = "";					//allocate a 28 char sized array
                                offset = get_value(28, temp, argv, &argc);		//call the get value function
                                argv += offset;						//add the offset to the array upon return
                                //printf("%s\n", temp);					//for testing: make sure right char[] returned
                                strncpy(tag.comment, temp, sizeof(tag.comment));	//copy the arguments to the tag field
				//printf("next arg: %s", argv[1]);			//for testing
                	}
			else if(strcmp(argv[1],"-track") == 0)
                	{
                        	argc--;							//decrease the number of arguments
                                char temp[1];						//allocate a 1 char sized array
                                offset = get_value(1, temp, argv, &argc);		//call the get value function
                                argv += offset;						//add the offset to the array upon return
                                //printf("Temp: %d\n", temp[0]);				//for testing: make sure right value returned
				tag.track = temp[0];					//copy the arguments to the tag field
				//printf("next arg: %s", argv[1]);			//for testing
                	}
			else if(argc > 0)			//if a argument is found that is not valid, skip over it
			{
				++argv;				//increment position in array
				--argc;				//decrease number of arguments
			}
		}//end of while loop

		if(no_tag)		//if no tag exists, add new tag to the end of the file
		{
			pos = fseek(in_file, 0, SEEK_END);	
		}
		else			//if the tag exists, write over old tag
		{
			pos = fseek(in_file, -128, SEEK_END);
		}
		fwrite((char *)&tag, 1, sizeof(tag), in_file);	//write the new tag

	}//end of else

	close = fclose(in_file);	//put statement if closing file does not work
	if(close)
	{
		printf("File not closed correctly\n");
	}
	
	return(0);
}

  
