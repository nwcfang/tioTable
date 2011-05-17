#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cell {
    char *s;
    struct cell *n;
} cl;

int main() 
{
    cl head, *ptr;
    int i=0;
    char s[80];

    ptr = &head;
    (*ptr).n = NULL;
    
    while (1) 
    {
        printf (" %d) ",i+1);
        fgets (s,80,stdin);

        if (!strcmp(s,"0\n")) 
        {
            break;
        }

        ptr->s=(char *)malloc(strlen(s));
        strcpy (ptr->s,s);
        ptr->n=( cl *)malloc(sizeof( cl));
        ptr=ptr->n;
        ptr->n=NULL;

        i++;

    } 
    
    ptr=&head;
    i=1;

    while (ptr->n!=NULL) 
    {
        printf ("%d) %s",i++,ptr->s);
        ptr=ptr->n;
    }
 
    return 0;
}

