// Find file by attributes. If no attributes are provided, outputs all files in the current directory.

#include <sys/stat.h>

#include <stdio.h>

#include <string.h>

#include <dirent.h>


int main(int argc, char ** argv) {
    struct dirent * d;
    struct stat buff;
    DIR * dp;
    
    if ((dp = opendir("./")) == NULL)
        return (-1);
    
    while ((d = readdir(dp))) {
        if (d->d_ino != 0) {
            ino_t inot = d -> d_ino;
            stat (d->d_name, &buff);
            char* permstr;
            asprintf(&permstr, "%o", buff.st_mode);
            if (!argv[1] || !strcmp(argv[1], permstr))
                printf("%s %s\n", permstr, d -> d_name);
            
        }
    }
    return 0;
}
