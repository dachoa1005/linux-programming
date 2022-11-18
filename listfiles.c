#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    printf("\n");
    char *path;
    char full_file_path[1024];
    DIR *d;
    struct dirent *dir;
    struct stat file_stat;
    struct passwd *pw;
    struct group *gr;
    // d = opendir("/home/ubuntu/Workspace/linux-programming");

    if (argc != 2)
    {
        printf("Usage %s <File Path>\n", argv[0]);
        return 0;
    }

    d = opendir(argv[1]);

    if (d != NULL)
    {

        while ((dir = readdir(d)) != 0)
        {
            strcpy(full_file_path, argv[1]);
            strcat(full_file_path, "/");
            strcat(full_file_path, dir->d_name); // get full of filepath

            // print file mode
            stat(full_file_path, &file_stat);
            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

            pw = getpwuid(file_stat.st_uid);
            gr = getgrgid(file_stat.st_gid);
            printf(" %15s %10s %10s ", dir->d_name, pw->pw_name, gr->gr_name);
            printf("\n");
        }
        closedir(d);
    }
    else
    {
        printf("Cannot read directory\n");
        return -1;
    }
    return 0;
}
