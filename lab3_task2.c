// ls -l -i

#include <sys/stat.h>
#include <sys/types.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <dirent.h>

#include <time.h>

#include <pwd.h>
#include <grp.h>

char* getUser(uid_t uid)
{
    struct passwd *pws;
// SVID 3, POSIX, BSD 4.3
    pws = getpwuid(uid);
    return strdup(pws->pw_name);
}
                   
char* getGroup(gid_t gid)
{
    struct group *grp;
// SVID 3, POSIX, BSD 4.3
    grp = getgrgid(gid);
    return strdup(grp->gr_name);
}

char* permissions(mode_t perm)
{
    char *modeval = malloc(sizeof(char) * 9 + 1);
    modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
    modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
    modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
    modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
    modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
    modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
    modeval[6] = (perm & S_IROTH) ? 'r' : '-';
    modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
    modeval[8] = (perm & S_IXOTH) ? 'x' : '-';
    modeval[9] = '\0';
    return modeval;
}

char* getDT(time_t rawtime)
{
    struct tm *info;
    char buffer[80];
    static const char format[] = "%c";//"%d %b";
    
    info = localtime( &rawtime );
    
    strftime(buffer, 80, format, info);
    
    return strdup(buffer);
}

int main(int argc, char ** argv) {
    struct dirent * d;
    struct stat buff;
    DIR * dp;
    
    if ((dp = opendir(argv[1])) == NULL)
        return (-1);
    
    while ((d = readdir(dp))) {
        if (d->d_ino != 0) {
            ino_t inot = d -> d_ino;
            stat (d->d_name, &buff);
            // inode permissions type group user size date name
            printf("%llu %s %7s %7s %8lld %25s %s\n",
                   inot,   // File inode
                   permissions(buff.st_mode),   // File permissions as text
                   getUser(buff.st_uid),    // User name by id as text
                   getGroup(buff.st_gid),   // User name by id as text
                   buff.st_size,    // File syze in bytes
                   getDT(buff.st_mtime), // Modification time from unix time, text
                   d -> d_name  // File name as text
                   );
            
        }
    }
    exit(0);
    
}
