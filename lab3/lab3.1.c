//Matt Stropkey
//lab 3

#include<stdio.h>

struct Node {
	int grade;
	struct Node *next;
};


int main()
{
	int user_in;
	double average = 0;
	int num_nodes = 0;
	struct Node *first_ptr = NULL;
	struct Node *new_node;
	
	do{
		printf("Enter a grade or \'-1\' to get the average: ");
		scanf("%d", &user_in);
		
		if(user_in != -1)
		{
			new_node = malloc(sizeof(struct Node));			//create a new node
			new_node->grade = user_in;				//set the structs grade field to user input
			new_node->next = first_ptr;				//link the new node to beginning of list
			first_ptr = new_node;					//set new node as first in list
		}
		else
		{
			struct Node *current_node;				//current node being used
			struct Node *previous_node;
			current_node = first_ptr;
			while(current_node != NULL)
			{
				average += current_node->grade;
				//printf("AVERAGE: %f\n", average);
				current_node = current_node->next;
				num_nodes++;
			}
			printf("The average is %.3f\n", average/(double)num_nodes);
		
        		do{
				current_node = first_ptr;
                		while(current_node->next != NULL)
                		{
                        		previous_node = current_node;
                        		current_node = current_node->next;
                		}
                		free(current_node);
				current_node = NULL;
				if(num_nodes != 1)
				{
                			previous_node->next = NULL;
				}
				num_nodes--;
        		}while(num_nodes != 0);	
		}//end of else
	}while(user_in != -1);//end of do while
	return 0;
}
