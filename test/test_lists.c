#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char *s;
    list *next;
};

void main () 
{
    list head, *ptr;
    int i=0;
    char s[80];
    ptr=&head;
    ptr->next=NULL;
    
    do 
    {
        printf (" %d) ",i+1);
        fgets (s,80,stdin);

        if (!strcmp(s,"0\n")) 
        {
            break;
        }
        else 
        {
            ptr->s=(char *)malloc(strlen(s));
            strcpy (ptr->s,s);
            ptr->next=(list *)malloc(sizeof(list));
            ptr=ptr->next;
            ptr->next=NULL;
        }

        i++;

    } while (1);
    
    ptr=&head;
    i=1;

    while (ptr->next!=NULL) 
    {
        printf ("%d) %s",i++,ptr->s);
        ptr=ptr->next;
    }
}
