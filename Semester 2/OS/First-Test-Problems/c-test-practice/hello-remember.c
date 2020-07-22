#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
    char* name;
    struct node* next;
};

struct node* add(struct node* head, char* name) {
    struct node* n;
    struct node* p;

    n = (struct node*)malloc(sizeof(struct node));
    n->name = (char*)malloc(strlen(name)+1);
    strcpy(n->name, name);
    n->next = NULL;

    if(head == NULL) {
        return n;
    } 

    p = head;
    while(p->next != NULL) {
        p = p->next;
    }
    p->next = n;
    return head;
}

int known(struct node* head, char* name) {
    struct node* p;
	
    if(head == NULL)
	return 0;

    p = head;
    while( p->next != NULL && strcmp(p->name, name) != 0) {
        p = p->next;
    }

    if(p->next==NULL && strcmp(p->name,name) == 0)
	return 1;

    if(p->next!=NULL)
	return 1;
    return 0;
   // return p != NULL;
}

void clear(struct node* head) {
    if(head == NULL) {
        return;
    }
    	struct node  *p, *n;
	p=head;
	while(p!=NULL)
	{
	free(p->name);
	n=p->next;
	free(p);
	p=n;
	}
	/*
    clearhead->next);
    free(head->name);
    free(head);
*/
}

int main(int argc, char** argv) {
    char name[64];
    struct node* head=NULL;

    while(scanf("%s", name) == 1) {
        if(known(head, name)) {
            printf("Still around %s, eh?\n", name);
        }
        else {
            head = add(head, name);
            printf("Hello %s\n", name);
        }
    }
    clear(head);
    return 0;
}
