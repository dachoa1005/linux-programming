#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char const *argv[])
{
    char *path;
    DIR *d;
    char *file_path;
    struct dirent *dir;
    struct stat proc_stat;
    struct passwd *pw;
    struct group *gr;

    d = opendir("/proc");

    if (d == NULL)
    {
        printf("Directory open fail");
        return 1;
    }
    while ((dir = readdir(d)) != 0)
    {
        file_path = (char *)malloc(sizeof("/proc/") + sizeof(dir->d_name) + sizeof("/comm") + 1);
        strcpy(file_path, "/proc/");
        strcat(file_path, dir->d_name);
        char *sub_file_path;
        sub_file_path = (char *)malloc(sizeof("/proc/") + sizeof(dir->d_name) + sizeof("/comm") + 1);

        strcpy(sub_file_path, file_path);
        stat(file_path, &proc_stat);
        pw = getpwuid(proc_stat.st_uid);
        gr = getgrgid(proc_stat.st_gid);
        printf("%10s %10s %10s\t", dir->d_name, pw->pw_name, gr->gr_name);

        strcat(sub_file_path, "/comm");
        FILE *fp;
        fp = fopen(sub_file_path, "r");
        if (fp != NULL)
        {
            char buffer[256];
            fscanf(fp, "%s", buffer);
            printf("%s \n", buffer);
        } else (printf("\n"));
    }
    return 0;
}
