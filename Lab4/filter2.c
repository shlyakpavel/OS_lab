// Разработать фильтр, ограничивающий длину каждой строки 50 символами.

#include <stdio.h>

#define MAX_LENGHT 50

int main()
{
    char c;
    unsigned short int cnt = 0;
    while ((c = getchar()) != EOF){
        if (c == '\n')
            cnt = 0;
        else
            cnt++;
        if (cnt <= MAX_LENGHT)
            putchar(c);
    }
    //putchar(EOF);
}
