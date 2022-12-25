#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv){
    _Bool ignoreCaseFlag = argc > 1 && argv[1][0] == '-' && argv[1][1] == 'i';
    // printf("%s\n", ignoreCaseFlag ? "true" : "false");
    char *pattern = (argc > 1 && ignoreCaseFlag) ? argv[2] : argv[1];
    if (ignoreCaseFlag)
        for (int i = 0; pattern[i]; i++)
            pattern[i] = tolower(pattern[i]);
    // printf("%s\n", pattern);

    char *line = (char*) malloc(1);
    int ch;
    size_t size = 1, len = 0;

    while ((ch = getchar()) != EOF) {
        if (len + 1 >= size) {
            size = size * 2 + 1;
            line = realloc(line, sizeof(char)*size);
        }

        if (ch == '\n'){
            line[len] = '\0';
            // printf("%s\n", line);
            if (ignoreCaseFlag){
                char* lineLower = (char*) malloc(sizeof(char)*size);

                for (int i = 0; i < len; i++)
                    lineLower[i] = tolower(line[i]);
                
                lineLower[len] = '\0';
                
                if (strstr(lineLower, pattern) != NULL)
                    printf("%s\n", line);
                
                free(lineLower);
            }
            else
                if (strstr(line, pattern) != NULL)
                    printf("%s\n", line);
            
            memset(line, len=0, size);
        }
        
        else
            line[len++] = ch;
    }
    
    free(line);

    return 0;
}