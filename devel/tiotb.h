typedef struct cell     /*Однонаправелнный список*/ 
{
    void **s;           /*Массив указателей на неизвестный тип данных*/ 
    struct cell *n;     /*Указатель на следующий элемент списка*/ 
} cl;

struct inform
{
    char **cap;         /*Шапка*/
    int countLetter;    /*Колличество символов в строке*/
    int countColum;     /*Колличество столбцов*/
    int *bufType;      /*Буфер с типам данных для каждого столбца*/
    cl *head, *ptr;      /*Список данных*/ 
};

extern void* tioTableBegin( const char *format, ... );
extern void* tioTableRecord( void *td, int num, ... );
extern int   tioTableEnd( void *td );
