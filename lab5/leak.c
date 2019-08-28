#include <stdio.h>
#include <stdlib.h>

typedef
   struct _Node {
      struct _Node *l;
      struct _Node *r;
   } Node;

Node* mk(void)
{
   Node *x = malloc(sizeof(Node));
   x->l = NULL;
   x->r = NULL;
   return x;
}

Node* t;

void fr(Node* s)
{
	Node *temp;
	temp = s;
	if(temp->l != NULL)
	{
		temp = s->l;
		fr(temp);
	}
	if(temp->r != NULL)
	{
		temp = s->r;
		fr(temp);
	}
	temp = NULL;
		
}		
void f(void)
{
   t       = mk();   // A
   t->l    = mk();   // B
   t->r    = mk();   // C
   t->l->l = mk();   // D
   t->l->r = mk();   // E
   t->r->l = mk();   // F
   t->r->r = mk();   // G

   fr(t->l->l);
   fr(t->r);
}

int main(void)
{
   f();
   return 0;
}

