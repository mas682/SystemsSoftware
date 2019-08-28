#include <stdio.h>
int weight;

int main() {
	printf("Please enter the weight you'd like to convert: ");
	scanf("%d", &weight);
	printf("\nHere is the weight on other planets:\n");
	printf("Mercury		%0.2f lbs\n", weight*0.38);
	printf("Venus		%0.2f lbs\n", weight*0.91);
	printf("Mars		%0.2f lbs\n", weight*0.38);
	printf("Jupiter		%0.2f lbs\n", weight*2.54);
	printf("Saturn		%0.2f lbs\n", weight*1.08);
	printf("Uranus		%0.2f lbs\n", weight*0.91);
	printf("Neptune		%0.2f lbs\n", weight*1.19);
	return(0);
}

