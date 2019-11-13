// Разработать фильтр, ограничивающий длину каждого слова в строке 5 символами.

#include <stdio.h>

#define MAX_LENGHT 5

int main()
{
    char c;
    unsigned short int cnt = 0;
    while ((c = getchar()) != EOF){
        if (c == ' ' || c == '\n')
            cnt = 0;
        else
            cnt++;
        if (cnt <= MAX_LENGHT)
            putchar(c);
    }
    //putchar(EOF);
}
