#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    // no -n flag
    if (argc == 1)
    {
        char **array = (char **)malloc(sizeof(char *));

        int ch;

        int numWords = 0;
        int curWordLength = 0;
        array[numWords] = (char *)malloc(sizeof(char));
        while ((ch = getchar()) != EOF)
        {
            if (ch == '\n')
            {
                array = (char **)realloc(array, sizeof(char *) * (numWords + 1));
                array[numWords] = (char *)realloc(array[numWords], sizeof(char) * (curWordLength + 1));
                array[numWords][curWordLength] = '\0';

                // printf("%s\n", array[i]);

                numWords++;
                curWordLength = 0;

                array = realloc(array, sizeof(char *) * (numWords + 1));
                array[numWords] = (char *)malloc(sizeof(char));
            }
            else
            {
                // printf("%s\n", array[i]);
                array[numWords] = (char *)realloc(array[numWords], sizeof(char) * (curWordLength + 1));
                array[numWords][curWordLength] = ch;
                curWordLength++;
            }
        }
        // for (int i = 0; i < 4; i++)
        // {
        //     scanf("%s", array[i]);
        // }

        // sort
        char *temp;
        for (int i = 0; i < numWords; ++i)
        {
            for (int j = i + 1; j < numWords; ++j)
            {
                if (strcasecmp(array[i], array[j]) > 0)
                {
                    temp = (char *)malloc(sizeof(char) * (strlen(array[i]) + 1));
                    strcpy(temp, array[i]);
                    array[i] = (char *)realloc(array[i], sizeof(char) * (strlen(array[j]) + 1));
                    strcpy(array[i], array[j]);
                    array[j] = (char *)realloc(array[j], sizeof(char) * (strlen(temp) + 1));
                    strcpy(array[j], temp);
                    free(temp);
                }
            }
        }

        // print final results
        for (int i = 0; i < numWords; i++)
        {
            printf("%s\n", array[i]);
        }

        // free memory
        for (int i = 0; i < numWords + 1; i++)
        {
            free(array[i]);
        }
        free(array);
    }

    // -n flag given
    else
    {
        int *arr = (int *)malloc(sizeof(int));
        int swap;
        // for (int i = 0; i < 4; i++)
        //     scanf("%d", &arr[i]);

        int numbers = 0;
        while (scanf("%d", &swap) != EOF)
        {
            arr = (int *)realloc(arr, sizeof(int) * (numbers + 1));
            arr[numbers] = swap;
            numbers++;
        }

        // print array (for debugging)
        //  for(int i = 0;i < numbers; i++)
        //      printf("%d ", arr[i]);

        // sort
        for (int i = 0; i < numbers - 1; i++)
        {
            for (int j = 0; j < numbers - i - 1; j++)
            {

                if (arr[j] > arr[j + 1])
                {
                    swap = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = swap;
                }
            }
        }

        for (int i = 0; i < numbers; i++)
            printf("%d\n", arr[i]);
    }
}