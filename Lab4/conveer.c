#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
/*  Создание программного канала    */
/*  для двух наших несчастных фильтров    */
{
    int pid, pid2;
    int fd[2];
    int status, dead;
    switch(pid = fork())
    {
        case -1: /* Cбой при вызове fork()  */
            printf("Ошибка при вызове fork() #1 \n");
            exit(1);
            break;
        case 0:  /*  ПОТОМОК #1 */
            pipe(fd);
            
            switch(pid2 = fork())
            {
                case -1: /* Cбой при вызове fork()  */
                    printf("Ошибка при вызове fork() #2 \n");
                    exit(2);
                    break;
                case 0:        /*  ПОТОМОК  #2 */
                    close(0); dup(fd[0]); close(fd[0]); close(fd[1]);
                    execl("./filter2", "filter2", NULL);
                    puts("Ошибка при вызове filter2 \n");
                    exit(-1);
                    break;
                default: /*                     */
                    close(1); dup(fd[1]);
                    close(fd[1]); close(fd[0]);
                    execl("./filter1", "filter1", NULL);
                    break;
            }
            puts("Ошибка при вызове filter1\n");
            exit(-1);
        default: /*  ПРЕДОК ГЛАВНЫЙ  */
            dead = wait(&status);
            exit(0);
            break;
    }
}
