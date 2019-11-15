// Разработать фильтр, ограничивающий длину каждого слова в строке 5 символами.

#include <stdio.h>

#define MAX_LENGHT 5

int main()
{
    char c, r;
    r = EOF;
    while ((c = getchar()) != EOF){
        if (c != r)
            putchar(c);
        r = c;
    }
    //putchar(EOF);
}
