#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

int main (int argc, char **argv)     /*”named pipe” client.c*/
{
  struct message msg;
  int n, fdpub, fdpriv;
  char line [LINESIZE];

/* синтезировать имя личного программного канала и создать этот канал с правами чтения и записи для всех процессов*/
sprintf(msg.privfifo, "Fifo%d", getpid());
if (mkfifo(msg.privfifo, S_IFIFO|0666) == -1)
{ perror (msg.privfifo);
exit(1);
}
/* общедоступный именованный канал (создается перед запуском сервера %mkfifo public) открывается на запись, и в него записываются имена личного канала и требуемого файла */

if ((fdpub=open(PUBLIC, O_WRONLY)) == -1)
{ perror (PUBLIC);
exit (2);
}
strcpy (msg.filename, argv[1]);
write (fdpub, (char*)&msg, sizeof(msg));

/* личный именованный канал открывается для чтения */
if ((fdpriv=open (msg.privfifo, O_RDONLY)) == -1)
{ perror (msg.privfifo);
exit (3);
}

 /*распечатать данные, полученные из личного канала */

//filter 2
    #define MAX_LENGHT 50
    int c;
    unsigned short int cnt = 0;
    while ((n = read(fdpriv,&c,1)) > 0){
        if (c == '\n')
            cnt = 0;
        else
            cnt++;
        if (cnt <= MAX_LENGHT)
            write(1, &c, 1);
    }
//end of filter 2

 /*личный именованный канал закрывается и удаляется из текущего каталога */
close (fdpriv);
unlink (msg.privfifo);
exit(0);
}
