/********************************************************
*craps							*
*This program simulates playing the dice game craps	*
*@author: Matt Stropkey					*
*The game can run severl times, with the goal of 	*
getting a 7 or 11 on the first roll, or get the point 	*
*If the user rolls a 2, 3, or 12 they immediately lose 	*
********************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int repeatgame(char *temp)
{
        int equal = 1;
        if(temp[3] != '\n')
        {
                return 0;
        }
        else
        {
                if(temp[0] != 'y' && temp[0] != 'Y')
                {
                        return 0;
                }
                if(temp[1] != 'e' && temp[1] != 'E')
                {
                        return 0;
                }

                if(temp[2] != 's' && temp[2] != 'S')
                {
                        return 0;
                }
        }//end else
        return equal;
}

//method used to see if user entered play regardless of the case
static int ignorecase(char *temp)
{
	int equal = 1;
	if(temp[4] != '\n')
	{
		return 0;
	}
	else
	{
		if(temp[0] != 'P' && temp[0] != 'p')
		{
			return 0;
		}
		if(temp[1] != 'L' && temp[1] != 'l')
		{
			return 0;
		}
		
		if(temp[2] != 'A' && temp[2] != 'a')
		{
			return 0;
		}
		if(temp[3] != 'Y' && temp[3] != 'y')
		{
			return 0;
		}
	}//end else
	return equal;
}



int main() {
	
	char die1;	//used to hold users first die value
	char die2;	//used to hold users second die value
	char user_total;	//used to hold user total
	char temp[20];		//used to hold user name
	int len;		//used for name 
	char *name;		//used to hold user name
	char input[6];		//used to hold if they want to play or quit
	char point;		//used to hold point value
	char iteration = 0;	//used to hold how many times user played
	char winner = 0;	//used to control while loop if not a winner
	char again[5];		//used to hold user input to play again

	srand((unsigned int)time(NULL));			//used to generate random numbers
	printf("Welcome to Matt's Casino!\n");			//intoduction line
	printf("Please enter your name: ");			//prompt the user for their name
	fgets(temp, sizeof(temp), stdin);			//get the user name
	if(!strchr(temp, '\n'))					//if the buffer is not empty, empty it
	{
		while(fgetc(stdin)!='\n');			//empties the buffer
	}
	len = strlen(temp);					//used to get the length of the user input
	name = malloc((len-1));					//used to hold the users name
	strncpy(name, temp, (len-1));				//places the user name in name
	printf("\n%s, would you like to Play or Quit? ", name);		//prompt the user to see if they want to play
	fgets(input, sizeof(input), stdin);			//set input to user input
	if(!strchr(input, '\n'))                                 //if the buffer is not empty, em$
        {
                while(fgetc(stdin)!='\n');                      //empties the buffer
        }
	if(ignorecase(input) == 1)	//the user wants to play
	{
		int fd = open("/dev/dice", O_RDWR);
		if(fd < 0)
		{
			printf("DEVICE FAILED TO OPEN\n");
		}
		 
		do{
		winner = 0;					//used to control for while loop
		iteration = 0;					//used to see if on first dice roll
		point = 0;					//used to keep track of current point value
		while(!winner)
		{
			char *dice = (char*)malloc(2);			//allocate 2 bytes to hold 2 dice
			int num = read(fd, dice, 2);			//get the 2 dice values
			if(2 != num)
			{
				printf("WRONG NUMBER OF BYTES READ!\n");
			}
			die1 = dice[0];		//used to get first die value; will need to change to driver
			die2 = dice[1];		//used to get second die value
			user_total = die1+die2;
			printf("\nYou have rolled %d + %d = %d\n", die1, die2, user_total);
			if(iteration == 0)
			{
				if(7 == user_total || 11 == user_total)//user wins
				{
					printf("You Win!\n");
					winner = 1;
				}
				else if(2 == user_total || 3 == user_total || 12 == user_total)//user loses
				{
					printf("You Lose!\n");
					winner = 1;
				}
				else
				{
					printf("The point is now %d\n", user_total);
					iteration = 1;
					point = user_total;
				}
			}//end of if
			else
			{
				if(7 == user_total)
				{
					printf("You Lose!\n");
                                        winner = 1;
				}
				else if(point == user_total)
				{
					printf("You Win!\n");
                                        winner = 1;
				}
				else
				{
					printf("You did not win or lose\n");
					printf("The point is still %d\n", point);

				}
			}//end else
			free(dice);				//free the space allocated for the dice
		}//end of while
		printf("\nWould you like to play again? ");
		fgets(again, sizeof(again), stdin);
		if(!strchr(again, '\n'))                                 //if the buffer is not empty, em$
	        {
                	while(fgetc(stdin)!='\n');                      //empties the buffer
        	}
		}while(repeatgame(again) == 1);//end of do while
	}//end of if
	
	//exit the program here
	printf("\nGoodbye, %s!\n", name);
	free(name);			//free the space used for the users name
	return 0;
}	
