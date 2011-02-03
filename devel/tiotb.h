struct inform
{
    char** cap;         /*Шапка*/
    int countLetter;    /*Колличество символов в строке*/
    int countColum;     /*Колличество столбцов*/
    int* bufType;       /*Буфер с типам данных для каждого столбца*/
};

extern int tioTableBegin( struct inform *datTab, const char* format, ... );

extern int tioTableEnd( char **cap, int *bufType );


