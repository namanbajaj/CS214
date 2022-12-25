#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>



int isDir(const char *path){
    struct stat statbuf;
    stat(path, &statbuf);
    return S_ISDIR(statbuf.st_mode);
}

void checkDir(char *path, char *pattern){
    // printf("PATH = %s\n", path);

    DIR *dir = opendir(path);
    struct dirent *str1;
    if(dir != NULL){
        while((str1 = readdir(dir)) != NULL){
            if(strcmp(str1->d_name, ".") == 0 || strcmp(str1->d_name, "..") == 0){
                continue;
            }
            char *dirpath = malloc(1000);
            strcpy(dirpath, path);
            // strcat(dirpath, "/");
            strcat(dirpath, str1->d_name);

            // printf("Dir Path: %s\n", dirpath);

            if(isDir(dirpath)){
                if(strstr(str1->d_name, pattern) != NULL){
                    printf("%s%s\n", path,str1->d_name);
                }
                strcat(dirpath, "/");
                checkDir(dirpath, pattern);
            }
            else{
                if(strstr(str1->d_name, pattern) != NULL){
                    printf("%s%s\n", path,str1->d_name);
                }
            }

            free(dirpath);
    }
    closedir(dir);
    }
    else{
        fprintf(stderr, "Error: Directory not found\n");
        exit(1);
    }
}



int main(int argc, char *argv[]){
    // char cwd[1000];
    // getcwd(cwd, sizeof(cwd));
    // printf("Current working dir: %s\n", cwd);
    char *baseDir = "./";
    char *pattern = argv[1];
    // printf("Dir: %s\n", baseDir);
    // printf("Pattern: %s\n", pattern);
    checkDir(baseDir, pattern);
    return 0;
}