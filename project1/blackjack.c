/********************************************************
*blackjack						*
*This program simulates playing the card game blackjack	*
*@author: Matt Stropkey					*
*The game runs one time, with the goal of getting as 	*
*close to 21 as possible.				*
*If the user or dealer has an ace, the program will 	*
*determine if it is worth a 1 or 11 based off of if	*
*they are over or under 21				*
********************************************************/

#include <stdio.h>


int main() {
	
	char dealer_card1;	//used to hold first dealer card
	char dealer_card2;	//used to hold second dealer card
	char dealer_hit;	//used to hold card for dealer hit
	char dealer_total;	//used to hold dealer card total
	char user_card1;	//used to hold first user card
	char user_card2;	//used to hold second user card
	char user_hit;		//used to hold card for user hit
	char user_total;	//used to hold user total
	char input[6];		//used to hold user input for hit or stand
	const char goal = 21;	//used to see if user/dealer went over
	char cards[52];		//array of card values
	char counter;		//counter to initialize deck
	char multiple_4;	//used to initialize deck
	char card_value;	//used to initialize card deck
	int random_val;		//used to pick a random card from the deck
	int string_cmp;		//used to see if the user wants to hit/stand
	char user_update;	//used if the user chooses to hit
	char dealer_update;	//used if the dealer has to hit
	char winner = 0;	//used as a boolean to see if winner found	
	char dealer_first = 1;	//used as a boolean if dealers first hit
	char user_ace = 0;
	char dealer_ace = 0;

	multiple_4 = 0;		//set to 0 for the number of each type of card in deck
	card_value = 2;		//beginning value to add cards to deck as
	for(counter = 0; counter < 52; counter++)	//for loop to initialize card deck
	{
		cards[counter] = card_value;		//set card values
		if(multiple_4 >= 3 && counter < 32)
		{
			multiple_4 = 0;			//reset count
			card_value = card_value+1;	//increment card value 
		}
		else if(counter == 47)			
		{
			card_value = card_value+1;	//change card value to 11
		}
		else if(multiple_4 < 3 && counter < 32)
		{
			multiple_4++;			//increment multiple of 4 to get 4 cards of each value
		}
	}//end of for loop to initialize cards
	srand((unsigned int)time(NULL));		//used to generate random numbers
	
	random_val = rand() %(52);			//generate a random number from 0-51
	dealer_card1 = cards[random_val];		//get the dealers first card
	cards[random_val] = 0;				//set the card to 0 in deck so it cannot be reused
	do{						//get the next dealer card
		random_val = rand() %(52);			//generate a random number between 0-51
		dealer_card2 = cards[random_val];		//get the dealers second card
	}while(dealer_card2 == 0);			//if the card is 0, pull another one
	cards[random_val] = 0;				//set the card to 0 in deck so it cannot be reused
	dealer_total = dealer_card1 + dealer_card2;	//update the total of the dealers cards
	if(dealer_card1 == 11)
	{
		dealer_ace++;
	}
	if(dealer_card2 == 11)
	{
		dealer_ace++;
	}
	if(dealer_ace == 2)
	{
		dealer_card1 = 1;
		dealer_ace--;
		dealer_total = dealer_total - 10;
	}
	//get the card values for the user
	do{	
		random_val = rand() %(52);			//generate a random number between 0-51
		user_card1 = cards[random_val];			//get the first user card
	}while(user_card1 == 0);			//if the card is 0, pull another one
	cards[random_val] = 0;				//set the card to 0 in the deck so it cannot be reused
	do{	
		random_val = rand() %(52);					//get the next card for the user
		user_card2 = cards[random_val];			//get the second user card
	}while(user_card2 == 0);			//if the card is 0, pull anotherone
	if(user_card1 == 11)
	{
		user_ace++;
	}
	if(user_card2 == 11)
	{
		user_ace++;
	}
	if(user_ace == 2)
	{
		user_card1 = 1;
		user_ace--;
		user_total = user_total - 10;
	}
	cards[random_val] = 0;				//set the card to 0 in the deck so it cannot be reused
	user_total = user_card1 + user_card2;		//update value of users cards
	
	printf("The dealer:\n");			//print out dealer cards
	printf("? + %d\n\n", dealer_card1);	
	printf("You:\n");				//print out user cards
	printf("%d + %d = %d \n\n", user_card1, user_card2, user_total);
	
	while(!winner){					//while no one has won	
     	do{
	printf("Would you like to \"hit\" or \"stand\"?\n");
	fgets(input, sizeof(input), stdin);
	string_cmp = strncmp(input, "hit", 3);		//need to only read 3 characters as if you read more it uses enter too
	printf("\n");
	if(string_cmp == 0)
	{
		
     		 do{                                             //get the next card for the user
     	                random_val = rand() %(52);                      //generate a random number
       		       	user_hit = cards[random_val];                 //get the next card for the user
        	}while(user_hit  == 0);                        //if the card is 0, pull another one
        	cards[random_val] = 0;
		user_update = user_total + user_hit;
		if(user_hit == 11)
		{
			user_ace++;
		}
		while(user_update > 21 && user_ace)
		{
			user_update = user_update - 10;
			user_ace--;
			if(user_hit == 11)
			{
				user_hit = 1;
			}
			else
			{
				user_total = user_total - 10;
				if(user_card1 == 11)
					user_card1 = 1;
				if(user_card2 = 11)
					user_card2 = 1;
			}
		}
		
	        printf("The dealer:\n");                        //print out dealer cards
	        printf("? + %d\n\n", dealer_card1);
		printf("You:\n");
		if(user_update <= goal)
		{
		printf("%d + %d = %d\n\n", user_total, user_hit, user_update);
		}				
		if(user_update > goal)
		{
			printf("%d + %d = %d BUSTED!\n\n", user_total, user_hit, user_update);
			printf("You busted. Dealer wins.\n");
			winner = 1;			//winner found
			break;
		}
		user_total = user_update;
	}//end of if
	}while(string_cmp == 0 && !winner);
	if(dealer_total < 17 && !winner)
	{
		// printf("%d + %d = %d\n", user_total, user_hit, user_total);	//will need to fix if user hits more than once
		do{	
       		         do{                                             //get the next card for the dealer
              	               random_val = rand() %(52);                      //generate a random number
                               dealer_hit = cards[random_val];                 //get the next card for the dealer
                         }while(dealer_hit  == 0);                        //if the card is 0, pull another one
                         cards[random_val] = 0;                         //set card to 0 in deck so it is not used again
                         dealer_update = dealer_total + dealer_hit;     //update dealer total
			 if(dealer_hit == 11)
			 {
				dealer_ace++;
			 }
			 while(dealer_update > 21 && dealer_ace)
			 {
				dealer_update = dealer_update - 10;
				dealer_ace--;
				if(dealer_hit == 11)
				{
					dealer_hit = 1;
				}
				else
				{
					dealer_total = dealer_total - 10;
					if(dealer_card1 == 11)
						dealer_card1 = 1;
					if(dealer_card2 == 11)
						dealer_card2 = 1;
				}
			 }
                         if(dealer_first)
			 {
				if(dealer_update <= goal)
				{
					printf("The dealer:\n");
					printf("%d + %d + %d = %d\n\n", dealer_card1, dealer_card2, dealer_hit, dealer_update);
					dealer_first = 0;
			 	}
				else
				{
					printf("The dealer:\n");
					printf("%d + %d + %d = %d BUSTED!\n\n", dealer_card1, dealer_card2, dealer_hit, dealer_update);
					printf("Dealer busted. You win.\n");
					winner = 1;
					break;
				}
			 }
			 else
			 {
				if(dealer_update <= goal)
				{
					printf("The dealer:\n");
					printf("%d + %d = %d\n\n", dealer_total, dealer_hit, dealer_update);
			        }
				else
                         	{
					printf("The dealer:\n");
					printf("%d + %d = %d BUSTED!\n\n", dealer_total, dealer_hit, dealer_update);
                               	        printf("Dealer busted. You win.\n");
                               	        winner = 1;
 			              	break;
				}
                         }
			dealer_total = dealer_update;
		}while(dealer_total < 17 && !winner);
	}
	if(!winner)
	{
		if(user_total < dealer_total)
		{
			printf("The dealer has won with the card total of %d to your %d\n", dealer_total, user_total);
			winner = 1;
		}
		else if(user_total > dealer_total)
		{
			printf("You have won with a card total of %d to the dealers %d\n", user_total, dealer_total);
			winner = 1;
		}
		else
		{
			printf("It is a draw.\n");
			winner = 1;
		}	
	}//end of else
	}//end of while loop
	

	return 0;
}	
