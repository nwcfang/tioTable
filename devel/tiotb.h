struct inform
{
    char **cap;         /*Шапка*/
    int countLetter;    /*Колличество символов в строке*/
    int countColum;     /*Колличество столбцов*/
    char *bufType;      /*Буфер с типам данных для каждого столбца*/
    void ***data;        /*Данные*/
};

extern void* tioTableBegin( const char *format, ... );
extern void* tioTableRecord( void *td );
extern int tioTableEnd( void *td );
