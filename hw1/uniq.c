#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()

{
   
    char *fullCount = (char *)malloc(sizeof(char));
    fullCount[0] = '\0';

    char *curword = (char *)malloc(sizeof(char));
    char *prevWord = NULL;
    int curWordIndex = 0;
    int count = 0;

    int ch;

    while ((ch = getchar()) != EOF)
    {
        if (ch == '\n')
        {
            curword[curWordIndex] = '\0';

            if (prevWord == NULL)
            {
                prevWord = (char *)malloc(sizeof(char) * (strlen(curword) + 1));
                strcpy(prevWord, curword);
                count++;
            }
            else
            {
                if (strcmp(prevWord, curword) == 0)
                {
                    count++;
                }
                else
                {
                    char *sentence = (char *)malloc(sizeof(char) * (strlen(count + " ") + strlen(prevWord) + 4));
                    sprintf(sentence, "%d %s\n", count, prevWord);
                    // printf("%s\n", sentence);
                    fullCount = (char *)realloc(fullCount, sizeof(char) * (strlen(fullCount) + strlen(sentence) + 1));
                    strcat(fullCount, sentence);
                    free(sentence);
                    count = 1;

                    prevWord = (char *)realloc(prevWord, sizeof(char) * (strlen(curword) + 1));
                    strcpy(prevWord, curword);
                }
            }
            free(curword);
            curword = (char *)malloc(sizeof(char));
            curWordIndex = 0;
        }
        else
        {
            curword[curWordIndex++] = ch;
            curword = realloc(curword, sizeof(char) * (curWordIndex + 1));
        }
    }

    char *sentence = (char *)malloc(sizeof(char) * (strlen(count + " ") + strlen(prevWord) + 4));
    sprintf(sentence, "%d %s\n", count, prevWord);
    // printf("%s\n", sentence);
    fullCount = (char *)realloc(fullCount, sizeof(char) * (strlen(fullCount) + strlen(sentence) + 1));
    strcat(fullCount, sentence);
    free(sentence);

    printf("%s", fullCount);

    // free memory
    free(fullCount);
    free(curword);
    free(prevWord);

    return 0;
}
