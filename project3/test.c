#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
int main(){
	




	void *a;
        a = my_bestfit_malloc(0);
        if(a == NULL)
        {
                printf("failed 1\n");
        }
        else
        {
                printf("%d added 0\n", a);
        }

        a = my_bestfit_malloc(0);
        if(a == NULL)
        {
                printf("failed 1\n");
        }
        else
        {
                printf("%d added 0\n", a);
        }



        a = my_bestfit_malloc(17);
        if(a == NULL)
        {
                printf("failed 1\n");
        }
        else
        {
                printf("%d added 17\n", a);
        }
        int *p;
        p = my_bestfit_malloc(0);
	
	if(p == NULL)
        {
                printf("failed 1 on 0\n");
        }
        else
        {
                printf("%d on 0\n", p);
        }

        p = my_bestfit_malloc(18);
        if(p == NULL)
        {
                printf("failed 1 on 100\n");
        }
        else
        {
                printf("%d on 18\n", p);
        }

        void *q;
        q = my_bestfit_malloc(50);


        if(q == NULL)
        {
                printf("failed 2 on 50\n");
                return 0;
        }
        else
        {
        printf("%d on 50\n", q); 
        }
        my_free(p);
        p = my_bestfit_malloc(1);
        if(p == NULL)
        {
                printf("failed 2 on 4\n");
                return 0;
        }
        else
        {
        printf("%d on 1\n", p);
        
        }
        my_free(a);
        my_free(q);
        my_free(p);


	return 0;





}//end main
