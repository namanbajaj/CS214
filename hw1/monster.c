#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int cols, rows, plrX, plrY, goalX, goalY, monX, monY;
char **board;

void printBoard()
{
    // printf("rows: %d, cols: %d\n", rows, cols);
    // printf("plrX: %d, plrY: %d\n", plrX, plrY);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            board[i][j] = '.';

    board[plrY][plrX] = 'P';
    board[goalY][goalX] = 'G';
    board[monY][monX] = 'M';

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

bool isMoveValid(char **board, char move)
{
    switch (move)
    {
    case 'N':
        if (plrY - 1 < 0)
        {
            printf("invalid move\n");
            return false;
        }
        else
        {
            plrY--;
            return true;
        }
    case 'E':
        if (plrX + 1 >= cols)
        {
            printf("invalid move\n");
            return false;
        }
        else
        {
            plrX++;
            return true;
        }
    case 'W':
        if (plrX - 1 < 0)
        {
            printf("invalid move\n");
            return false;
        }
        else
        {
            plrX--;
            return true;
        }
    case 'S':
        if (plrY + 1 >= rows)
        {
            printf("invalid move\n");
            return false;
        }
        else
        {
            plrY++;
            return true;
        }
    default:
        return false;
    }

    return false;
}

void monsterMove()
{
    char move;

    // go left or right
    if (plrX != monX && (plrY == monY || abs(plrX - monX) > abs(plrY - monY)))
    {
        if (plrX < monX)
        {
            move = 'W';
            monX--;

            if(monX == goalX && monY == goalY)
            {
                monX++;
                if (plrY < monY) {
                    move = 'N';
                    monY--;
                }
                else {
                    move = 'S';
                    monY++;
                }

            }
        }
        else
        {
            move = 'E';
            monX++;

            if(monX == goalX && monY == goalY)
            {
                monX--;
                if (plrY < monY) {
                    move = 'N';
                    monY--;
                }
                else {
                    move = 'S';
                    monY++;
                }
            }
        }
    }

    // go up or down
    else
    {
        if (plrY < monY)
        {
            move = 'N';
            monY--;

            if(monX == goalX && monY == goalY)
            {
                monY++;
                if (plrX < monX) {
                    move = 'W';
                    monX--;
                }
                else {
                    move = 'E';
                    monX++;
                }
            }
        }
        else
        {
            move = 'S';
            monY++;
            
            if(monX == goalX && monY == goalY)
            {
                monY--;
                if (plrX < monX) {
                    move = 'W';
                    monX--;
                }
                else {
                    move = 'E';
                    monX++;
                }
            }
        }
    }

    printf("monster moves %c\n", move);
}

int main(int argc, char **argv)
{
    cols = atoi(argv[1]);
    rows = atoi(argv[2]);
    plrX = atoi(argv[3]);
    plrY = rows - 1 - atoi(argv[4]);
    goalX = atoi(argv[5]);
    goalY = rows - 1 - atoi(argv[6]);
    monX = atoi(argv[7]);
    monY = rows - 1 - atoi(argv[8]);

    board = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++)
        board[i] = malloc(cols * sizeof(char));

    printBoard();

    // printf("plrX: %d, plrY: %d\n", plrX, plrY);
    // printf("goalX: %d, goalY: %d\n", goalX, goalY);

    char move = ' ';
    while (true)
    {
        move = fgetc(stdin);
        while (!isMoveValid(board, move))
        {
            move = fgetc(stdin);
        }

        if (plrX == goalX && plrY == goalY)
        {
            printf("player wins!\n");
            break;
        }

        if (plrX == monX && plrY == monY)
        {
            printf("monster wins!\n");
            break;
        }

        monsterMove();

        if (plrX == monX && plrY == monY)
        {
            printf("monster wins!\n");
            break;
        }

        printBoard();
    }

    for(int i = 0; i < rows; i++)
        free(board[i]);
    free(board);

    return 0;
}