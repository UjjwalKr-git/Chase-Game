#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define resX 64
#define resY 18

time_t mytime;
int flag = 0, score = 0;
int foodX, foodY;
int x, y, lenX, lenY;
int life = 4, flagStop = 0, level;

void setup()
{
    do
    {
        foodX = (rand() % (resX - 1)) - 1;
        if (foodX % 2 != 0)
        {
            foodX -= 1;
        }
    } while (foodX == 0);
    do
    {
        foodY = (rand() % (resY - 1)) - 1;
        if (foodY % 2 != 0)
        {
            foodY -= 1;
        }
        
    } while (foodY == 0);
}

void delay(int time)
{
    // Storing start time
    clock_t start_time = clock();
    // looping till required time is not achieved
    while (clock() < start_time + time)
        ;
}

int movement()
{
    if (flag == 1)
        y--;
    else if (flag == 2)
    {
        x = x + 2;
        y++;
    }
    else if (flag == 3)
        x = x + 2;
    else if (flag == 4)
    {
        x = x + 2;
        y++;
    }
    else if (flag == 5)
    {
        x = x - 2;
        y++;
    }
    else if (flag == 6)
        x = x - 2;
    else if (flag == 7)
    {
        x = x - 2;
        y--;
    }
    else if (flag == 8)
        y++;
    else if (flag == 9)
        setup();
    else if (flag == 10)
        x = foodX;
    else if (flag == 11)
        y = foodY;
    if (x == 0 || y == 0 || x == resX || y == resY)
    {
        flag = 0;
        x = resX / 2;
        y = resY / 2;
        //setup();
        life -= 1;
    }
    if (life == 0)
        flagStop = 1;
    delay(level);
    return life;
}

void Menu()
{
    system("cls");
    printf("\n");
    printf("\tScore = %d\t\t\tLife Remaning = %d\t\n", score, (life - 1));
    printf("\n");
}

void UI()
{
    for (int j = 0; j <= resY; j++)
    {
        if (j == 0 || j == resY)
        {
            for (int i = 0; i <= resX / 2; i++)
                printf("* ");
            printf("\n");
        }
        else
        {
            for (int i = 0; i <= resX; i++)
            {
                if (i == 0 || i == resX)
                    printf("*");
                else
                {
                    if (i == x && j == y)
                    {
                        printf("0");
                    }
                    else if (i == foodX && j == foodY)
                        printf("#");
                    else
                        printf(" ");
                }
            }
            printf("\n");
        }
    }
}

int main()
{
    int inp_level, inp;
    char inp_ReStart, inp_name[] = "YOUR NAME";
label_ReStart:
    system("cls");
    printf("Enter Your Name [Max. 6 Letters] : ");
    gets(inp_name);
    fflush(stdin);
    level = 100;
    x = resX / 2;
    y = resY / 2;
    do
    {
        setup();
        do
        {
            Menu();
            //Taking Inputs...
            if (kbhit())
            {
                inp = getch();
                if (inp == 27)
                    flag = 0;
                else if (inp == 'w' || inp == 'W' || inp == 72)
                    flag = 1;
                else if (inp == 'e' || inp == 'E')
                    flag = 2;
                else if (inp == 'd' || inp == 'D' || inp == 77)
                    flag = 3;
                else if (inp == 'x' || inp == 'X')
                    flag = 4;
                else if (inp == 'z' || inp == 'Z')
                    flag = 5;
                else if (inp == 'a' || inp == 'A' || inp == 75)
                    flag = 6;
                else if (inp == 'q' || inp == 'Q')
                    flag = 7;
                else if (inp == 's' || inp == 'S' || inp == 80)
                    flag = 8;
                else if (inp == 'f' || inp == 'F')
                    flag = 9;
                else if (inp == ',')
                    flag = 10;
                else if (inp == '.')
                    flag = 11;
            }
            UI();
            movement(flag);
            if (foodX == x && foodY == y)
            {
                score += 10;
                break;
            }
        } while (flagStop != 1);
    } while (foodX == x && foodY == y);
    printf("\n%s, Your Score is %d.\n\n", inp_name, score);
    mytime = time(NULL);
    printf("\tNAME\t\tLEVEL\t\tSCORE\t\tTIME & DATE\n");
    printf("\t%s\t\t%d\t\t%d\t\t", inp_name, inp_level, score);
    printf(ctime(&mytime));
    printf("\n");
label_ReTry:
    printf("Do You Want To Restart...? ['Y' for Yes OR 'N' for No] : ");
    scanf("%c", &inp_ReStart);
    fflush(stdin);
    printf("\n");
    if (inp_ReStart == 'Y' || inp_ReStart == 'y')
    {
        score = 0;
        x = resX / 2;
        y = resY / 2;
        life = 6;
        flag = 0;
        flagStop = 0;
        goto label_ReStart;
    }
    else if (inp_ReStart == 'N' || inp_ReStart == 'n')
        goto label_Exit;
    else
        goto label_ReTry;
label_Exit:
    printf("\n");
    printf("Press Any Key to EXIT.\n");
    getch();
    return 0;
}
