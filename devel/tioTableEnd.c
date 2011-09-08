#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <tiotb.h>

#define WIDTH 80


/*Table row*/ 
int tabRow( void **strings, int *bufType, int countColum, int lenColCon )
{
    char ***data;                   /*Pointer of the table's data*/
    int *colStr;                    /*Array of extra lines*/ 
    int i;
    int j;
    int max = 0;
    int extraCounter;               /*Extra lines counter*/ 
    int offset;                     /*Offset counter*/ 
    int strCounter;

    /*Allocating memory for colStr*/ 
    if( (colStr = (int *) malloc(countColum * sizeof(int))) == NULL )
    {
        printf("ERROR!");
        exit(EXIT_FAILURE);
    }

    /*Calculation number of extra lines of the array*/ 
    for( i = 0; i < countColum; ++ i )
    {
        colStr[i] = strlen( (char *)strings[i] ) / lenColCon; 
        if(max < colStr[i])
            max = colStr[i];
    }

    /*Allocating memory for data*/ 
    if((data = (char ***) malloc (countColum * sizeof(char **))) == NULL)
    {
        printf("ERROR!\n");
        exit(EXIT_FAILURE);
    }
    for( i = 0; i < countColum; ++ i )
    {
        if((data[i] = (char **) malloc ((max + 1) * sizeof(char *))) == NULL)
        {
            printf("ERROR!\n");
            exit(EXIT_FAILURE);
        }       
        else
        {
            for (j = 0; j < (max + 1); ++ j)
            {
                if((data[i][j] = (char *) malloc (lenColCon * sizeof(char))) == NULL)
                {
                    printf("ERROR!\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    /*Partition line*/ 
    for(i = 0; i < countColum; ++ i)
    {
        switch( bufType[i] )
        {
        case 1:
            sprintf( data[i][0], "%c",*(char *) strings[i]);
            offset = strlen(data[i][0]);
            /*Insert spaces*/
            for( offset; offset < (lenColCon - 1); ++ offset)
                data[i][0][offset] = ' ';
            /*Insert spaces*/
            for(extraCounter = 1; extraCounter < (max + 1); ++ extraCounter)
                for( offset = 0; offset < (lenColCon - 1); ++ offset )
                    data[i][extraCounter][offset] = ' ';           
            break;
        case 2:
            sprintf( data[i][0], "%.2f",*(double *) strings[i]);
            offset = strlen(data[i][0]);
            /*Insert spaces*/
            for( offset; offset < (lenColCon - 1); ++ offset)
                data[i][0][offset] = ' ';
            /*Insert spaces*/
            for(extraCounter = 1; extraCounter < (max + 1); ++ extraCounter)
                for( offset = 0; offset < (lenColCon - 1); ++ offset )
                    data[i][extraCounter][offset] = ' '; 
            /*printf("90 string in End = %s\n", (char*)strings[3]);*/
            break;
        case 3:
            sprintf( data[i][0], "%ld",*(long *) strings[i]);
            offset = strlen(data[i][0]);
            /*Insert spaces*/
            for( offset; offset < (lenColCon - 1); ++ offset)
                data[i][0][offset] = ' ';
            /*Insert spaces*/
            for(extraCounter = 1; extraCounter < (max + 1); ++ extraCounter)
                for( offset = 0; offset < (lenColCon - 1); ++ offset )
                    data[i][extraCounter][offset] = ' ';
            break;
        case 4:
            for( extraCounter = 0; extraCounter <= colStr[i]; ++ extraCounter )
            {
                j = extraCounter * (lenColCon - 1);
                for( offset = 0;
                        ((offset != (lenColCon - 1)) && (((char *)strings[i])[j] != '\0' )); ++ offset, ++ j)
                {
                    data[i][extraCounter][offset] = ((char *)strings[i])[j]; 
                }
                /*Insert spaces*/
                for( offset; offset < (lenColCon - 1); ++ offset)
                    data[i][extraCounter][offset] = ' ';
            }
            /*Insert spaces*/
            for(extraCounter = colStr[i] + 1; extraCounter < (max + 1); ++ extraCounter )
                for( offset = 0; offset < (lenColCon - 1); ++ offset )
                    data[i][extraCounter][offset] = ' ';
            break;
        default:
            printf("ERROR!");
            exit(EXIT_FAILURE);
        }
        
    
    }

    /*Print row*/
        for( strCounter = 0; strCounter < (max + 1); ++ strCounter  )
        {
            for( i = 0; i < countColum; ++ i )
                printf("|%s", data[i][strCounter]);    
            printf("|\n");
        } 

    /*FREE */
    for( i = 0; i < countColum; ++ i )
    {
        for( j = 0; j < colStr[i]; ++ j )
        {
            free(data[i][j]);
        }
        free(data[i]);
    }
    free(data);

    free(colStr);
    
    return 0;

}

/*Display cap*/ 
int capMap( int countColum, char **cap, int lenColCon )
{
    int i;
    int j;
    int tmp;
    for(i = 0; i < countColum; ++ i )
    {
        printf( "|%s", cap[i] );
        tmp = lenColCon - strlen(cap[i]);
        for( j = 0; j < tmp - 1; ++ j )
            printf( " " );
    }
    printf( "|\n");
    
    return 0;
}

/*Draw line function*/
int drawLine( int lenColCon )
{
    int i;
    for( i = 0; i < WIDTH; ++ i )   /*Need correct WIDTH*/ 
    {
        if((i % lenColCon) == 0)
            printf("+");
        else
            printf("-");
    }
    printf( "+\n" );

    return 0;
}

/*Table's output*/ 
int tioTableEnd( void *td )
{
    struct inform *datTab;
     
    int i;                          /*Counter*/ 
    int lenColCon;                  /*Cell width*/ 
    void *next;     
    int *masType;                   /*For type of cap*/ 
    datTab = (struct inform *) td;
    
    datTab->ptr = datTab->head;
    /*printf("string in End = %s\n", (char*)datTab->ptr->s[3]);*/

    /*Calculate the column width depending on the number of*/  
    lenColCon = WIDTH / datTab->countColum;   
    printf("Размер колонки = %d\n", lenColCon);
    
    if( (masType = (int *) malloc(datTab->countColum * sizeof(int))) == NULL)
    {
        printf("ERROR!");
        exit(EXIT_FAILURE);
    }

    /*Draw line*/ 
    drawLine(lenColCon); 
    
    for( i = 0; i < datTab->countColum; ++ i )
    {
        masType[i] = 4;
    }
    /*Display cap*/
    tabRow( (void *)datTab->cap, masType, datTab->countColum, lenColCon); 
    
    /*Draw line*/
    drawLine(lenColCon);
    
    while( datTab->ptr->n != NULL )
    {

        /*Print table row*/ 
        tabRow( datTab->ptr->s, datTab->bufType, datTab->countColum, lenColCon );

        /*Jump to the new cell*/ 
        datTab->ptr = datTab->ptr->n;
        /*Draw line*/
        drawLine(lenColCon);
    }
    
    /*Free masType*/
    free(masType);
    /*Free data*/
    for( i = 0; i < datTab->countColum; ++ i )
        free(datTab->cap[i]);
    free( datTab->cap );

    /*Free bufTab*/
    free(datTab->bufType);

    /*Free ptr->s*/ 
    datTab->ptr = datTab->head;
    do 
    {     
        next = (void *) datTab->ptr->n;
        for( i = 0; i < datTab->countColum; ++ i )
        {
            if(datTab->ptr->n != NULL)
                free(datTab->ptr->s[i]);
        }
        free(datTab->ptr->s);
        free(datTab->ptr);
        datTab->ptr = (cl *) next;
    } while (datTab->ptr != NULL);

    /*Free datTab*/
    free(datTab);

    return 0;
}
